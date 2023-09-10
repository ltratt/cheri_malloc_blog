#include "cheriintrin.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

static char *heap_start;
static char *heap;
static size_t HEAP_SIZE = 1024 * 1024 * 64;

__attribute__((destructor))
static void malloc_exit() {
  fprintf(stderr, "heap used %lu\n", heap - heap_start);
}

void *malloc(size_t sz) {
  if (!heap) heap = heap_start = mmap(NULL, HEAP_SIZE,
    PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON,-1,0);

  char *new_ptr = __builtin_align_up(
    heap, -cheri_representable_alignment_mask(sz));
  size_t bounds = cheri_representable_length(sz);
  sz = __builtin_align_up(sz, _Alignof(max_align_t));

  if (new_ptr + sz > heap_start + HEAP_SIZE) return NULL;
  heap = new_ptr + sz;
  return cheri_bounds_set_exact(new_ptr, bounds);
}

void free(void *ptr) { }

void *realloc(void *ptr, size_t sz) {
  void *new_ptr = malloc(sz);
  if (ptr && new_ptr) memmove(new_ptr, ptr,
    cheri_length_get(ptr) < sz
    ? cheri_length_get(ptr) : sz);
  return new_ptr;
}
