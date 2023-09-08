#include <cheriintrin.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  void *c1 = malloc(4);
  void *c2 = malloc(4);
  printf("c1 address 0x%lx lower 0x%lx length 0x%lx\n",
    cheri_address_get(c1), cheri_base_get(c1),
    cheri_length_get(c1));
  printf("c2 address 0x%lx lower 0x%lx length 0x%lx\n",
    cheri_address_get(c2), cheri_base_get(c2),
    cheri_length_get(c2));
}
