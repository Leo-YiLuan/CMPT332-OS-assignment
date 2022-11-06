/* Physical memory allocator, for user processes, */
/* kernel stacks, page-table pages, */
/* and pipe buffers. Allocates whole 4096-byte pages. */

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);
/* CMPT 332 GROUP 22 Change, Fall 2022 */
/* Reserves physical memory to track references 
   for every physical page frame. Returns
   the new "first address" that the page frame
   allocator is allowed to use. 
*/
uint64 init_ref_map();

extern char end[]; /* first address after kernel. */
                   /* defined by kernel.ld. */

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
  /* CMPT 332 GROUP 22 Change, Fall 2022 */
  uint64 freecount;
  uint64 refmap_pagesize;
  char *ref_map;
} kmem;

void
kinit()
{
  uint64 newEnd = 0;
  initlock(&kmem.lock, "kmem");
  newEnd = init_ref_map();
  freerange((void*)newEnd, (void*)PHYSTOP);
}

uint64
init_ref_map() {
  /* Reserve a chunk of contiguous free pages for the ref map */
  uint64 refMapSize = (PHYSTOP - (uint64)end) / PGSIZE;
  uint64 pagesNeeded = (refMapSize / PGSIZE) + 1;
  
  acquire(&kmem.lock);
  kmem.ref_map = end;
  kmem.refmap_pagesize = pagesNeeded;
  release(&kmem.lock);

  /* Return a new starting point for free physical memory */
  return ((uint64)&end) + (pagesNeeded * PGSIZE);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

/* Free the page of physical memory pointed at by pa, */
/* which normally should have been returned by a */
/* call to kalloc().  (The exception is when */
/* initializing the allocator; see kinit above.) */
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  /* Fill with junk to catch dangling refs. */
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  /* CMPT 332 GROUP 22 Change, Fall 2022 */
  kmem.freecount++;
  release(&kmem.lock);
}

/* Allocate one 4096-byte page of physical memory. */
/* Returns a pointer that the kernel can use. */
/* Returns 0 if the memory cannot be allocated. */
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r) {
    kmem.freelist = r->next;
    /* CMPT 332 GROUP 22 Change, Fall 2022 */
    kmem.freecount--;
  }
  release(&kmem.lock);

  if(r)
    memset((char*)r, 5, PGSIZE); /* fill with junk */
  return (void*)r;
}

/* CMPT 332 GROUP 22 Change, Fall 2022 */
uint64
sys_getNumPages(void) {
  uint64 res = 0;
  acquire(&kmem.lock);
  res = kmem.freecount;
  release(&kmem.lock);

  return res;
}