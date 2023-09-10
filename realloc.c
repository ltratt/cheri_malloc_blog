#include <cheriintrin.h>
#include <stdlib.h>

int main() {
  void *c1 = malloc(4);
  c1 = realloc(c1, 8);
  return 0;
}
