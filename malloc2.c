#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

static char *heap_start;
static char *heap;
static size_t HEAP_SIZE = 1024 * 1024 * 1024;

__attribute__((destructor))
static void malloc_exit() {
  fprintf(stderr, "heap used %lu\n", heap - heap_start);
}

void *malloc(size_t sz) {
  if (!heap) heap = heap_start = mmap(NULL, HEAP_SIZE,
    PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON,-1,0);
  sz = __builtin_align_up(sz, _Alignof(max_align_t));
  if (heap + sz > heap_start + HEAP_SIZE) return NULL;
  heap += sz;
  return heap - sz;
}

void free(void *ptr) { }

void *realloc(void *ptr, size_t sz) {
  void *new_ptr = malloc(sz);
  if (ptr && new_ptr) memmove(new_ptr, ptr, sz);
  return new_ptr;
}
