#include <cheriintrin.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *c1 = malloc(4);
  char *c2 = malloc(4);
  printf("c1 address 0x%lx lower 0x%lx length 0x%lx\n",
    cheri_address_get(c1), cheri_base_get(c1),
    cheri_length_get(c1));
  printf("c2 address 0x%lx lower 0x%lx length 0x%lx\n",
    cheri_address_get(c2), cheri_base_get(c2),
    cheri_length_get(c2));
  c1[0] = 'a';
  printf("c1[0] %c\n", c1[0]);
  printf("(c2 - 0x10)[0] %c\n", (c2 - 0x10)[0]);
}
