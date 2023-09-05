#include <errno.h>
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

void *calloc(size_t nmemb, size_t sz) {
  char *ptr = malloc(nmemb * sz);
  bzero(ptr, nmemb * sz);
  return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t sz) {
  return realloc(ptr, nmemb * sz);
}

void *recallocarray(void *ptr, size_t oldnmemb, size_t nmemb, size_t sz) {
  void *new_ptr = malloc(nmemb * sz);
  if (ptr && new_ptr) memmove(new_ptr, ptr, oldnmemb * sz);
  if (new_ptr && nmemb > oldnmemb) bzero(new_ptr + oldnmemb * sz, (nmemb - oldnmemb) * sz);
  return new_ptr;
}

void freezero(void *ptr, size_t sz) { }

void *aligned_alloc(size_t alignment, size_t sz) {
  return malloc(sz);
}

void *malloc_conceal(size_t sz) {
  return malloc(sz);
}

void *calloc_conceal(size_t nmemb, size_t sz) {
  return calloc(nmemb, sz);
}

int posix_memalign(void **ptr, size_t alignment, size_t sz) {
  *ptr = malloc(sz);
  return *ptr == 0 ? 0 : ENOMEM;
}

void *memalign(size_t alignment, size_t sz) {
  return malloc(sz);
}

void *valloc(size_t sz) {
  return malloc(sz);
}
