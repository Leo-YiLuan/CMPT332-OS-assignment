/* Physical memory allocator, for user processes, */
/* kernel stacks, page-table pages, */
/* and pipe buffers. Allocates whole 4096-byte pages. */

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

/* CMPT 332 GROUP 22 Change, Fall 2022 */
void page_ref_inc(uint64 pa);
void page_ref_dec(uint64 pa);
void page_ref_set(uint64 pa, uint8 val);
extern char trampoline[]; /* trampoline.S */

void freerange(void *pa_start, void *pa_end);

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
  uint8 ref_map[PHYSTOP / PGSIZE];
} kmem;

void
kinit()
{
  initlock(&kmem.lock, "kmem");
  freerange((void*)end, (void*)PHYSTOP);
  /* Trampoline page is special, not allocated normally, set manually. */
  page_ref_set((uint64)trampoline, 64);
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

  if (page_ref_count((uint64)pa) > 1) {
    panic("kfree freeing page with ref count > 1");
  }

  /* Fill with junk to catch dangling refs. */
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  /* CMPT 332 GROUP 22 Change, Fall 2022 */
  kmem.freecount++;
  release(&kmem.lock);

  
  page_ref_set((uint64)r, 0);
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

  if(r) {
    /* CMPT 332 GROUP 22 Change, Fall 2022 */
    // Set ref count to 1, someone must have asked for it.
    page_ref_set((uint64)r, 1);
    memset((char*)r, 5, PGSIZE); /* fill with junk */
  }
  return (void*)r;
}

/* CMPT 332 GROUP 22 Change, Fall 2022 */
void
page_ref_inc(uint64 pa) {
  uint64 frameNum = ((pa >> PGSHIFT) << PGSHIFT) / PGSIZE;

  if (frameNum < 0 || (frameNum > (PHYSTOP / PGSIZE))) {
    panic("page_ref_inc invalid frame number");
  }

  acquire(&kmem.lock);
  if (kmem.ref_map[frameNum] >= 64) {
    panic("page_ref_inc increment past 64");
  }
  kmem.ref_map[frameNum]++;
  release(&kmem.lock);
}

/* CMPT 332 GROUP 22 Change, Fall 2022 */
void
page_ref_dec(uint64 pa) {
  uint64 frameNum = ((pa >> PGSHIFT) << PGSHIFT) / PGSIZE;

  if (frameNum < 0 || (frameNum > (PHYSTOP / PGSIZE))) {
    panic("page_ref_dec invalid frame number");
  }

  acquire(&kmem.lock);
  if ((kmem.ref_map[frameNum] - 1) >= 64) {
    panic("page_ref_dec decrement below 0, underflow");
  }
  kmem.ref_map[frameNum]--;
  release(&kmem.lock);

}

/* CMPT 332 GROUP 22 Change, Fall 2022 */
int
page_ref_count(uint64 pa) {
  int refCount = 0;
  uint64 frameNum = ((pa >> PGSHIFT) << PGSHIFT) / PGSIZE;

  if (frameNum < 0 || (frameNum > (PHYSTOP / PGSIZE))) {
    panic("page_ref_count invalid frame number");
  }

  acquire(&kmem.lock);
  refCount = kmem.ref_map[frameNum];
  release(&kmem.lock);

  return refCount;
}

/* CMPT 332 GROUP 22 Change, Fall 2022 */
void 
page_ref_set(uint64 pa, uint8 val) {
  uint64 frameNum = ((pa >> PGSHIFT) << PGSHIFT) / PGSIZE;

  if (frameNum < 0 || (frameNum > (PHYSTOP / PGSIZE))) {
    panic("page_ref_set invalid frame number");
  }
  if (val < 0 || val > 64) {
    panic("page_ref_set val out of range");
  }

  acquire(&kmem.lock);
  kmem.ref_map[frameNum] = val;
  release(&kmem.lock);
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