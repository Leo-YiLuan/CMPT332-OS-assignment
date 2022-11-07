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
   for every physical page frame. 
   Sets the value newEnd to the new start of 
   available memory for the page frame allocator.
*/
void init_ref_map();

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
  initlock(&kmem.lock, "kmem");
  freerange((void*)end, (void*)PHYSTOP);
  init_ref_map();
}

void
init_ref_map() {
  /* Reserve a chunk of contiguous free pages for the ref map */
  uint64 refMapSize = (PHYSTOP - (uint64)end) / PGSIZE;
  uint64 pagesNeeded = (refMapSize / PGSIZE) + 1;
  
  uint64 lastPage = 0;
  for (int i = 0; i < pagesNeeded; i++) {
    lastPage = (uint64)kalloc();
    memset((void*)lastPage, 0, PGSIZE);
  }
  acquire(&kmem.lock);
  kmem.ref_map = (char *)((lastPage - (pagesNeeded * PGSIZE)));
  release(&kmem.lock);
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
int
page_ref_inc(uint64 pa) {
  uint64 frameNum = 0;
  if ((uint64)pa < (uint64)end) {
    return -1;
  }
  frameNum = (((pa >> PGSHIFT) << PGSHIFT) - (uint64)end) / PGSIZE;

  acquire(&kmem.lock);
  if (kmem.ref_map[frameNum] >= 64) {
    panic("page_ref_inc");
  }
  kmem.ref_map[frameNum]++;
  release(&kmem.lock);

  return 0;
}

/* CMPT 332 GROUP 22 Change, Fall 2022 */
int
page_ref_dec(uint64 pa) {
  uint64 frameNum = 0;
  if ((uint64)pa < (uint64)end) {
    return -1;
  }
  frameNum = (((pa >> PGSHIFT) << PGSHIFT) - (uint64)end) / PGSIZE;

  acquire(&kmem.lock);
  if (kmem.ref_map[frameNum] <= 0) {
    panic("page_ref_dec");
  }
  kmem.ref_map[frameNum]--;
  release(&kmem.lock);

  return 0;
}

int
page_ref_count(uint64 pa) {
  uint64 frameNum = 0;
  int refCount = 0;

  // Why is this happening? This should never happen.
  if ((uint64)pa < (uint64)end) {
    return -1;
  }
  frameNum = (((pa >> PGSHIFT) << PGSHIFT) - (uint64)end) / PGSIZE;

  acquire(&kmem.lock);
  refCount = kmem.ref_map[frameNum];
  release(&kmem.lock);
  return refCount;
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