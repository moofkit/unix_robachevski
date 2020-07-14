#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  int *brake_address;
  int *new_brake_address;
  char *address_pointer;

  brake_address = sbrk(0);
  printf("current brake address 0x%x\n", brake_address);

  address_pointer = malloc(64);
  printf("allocating 64 bytes from heap...\n");

  new_brake_address = sbrk(0);
  printf("Allocated memory address pointer: 0x%x,\
    current brake address: 0x%x (extend by %ld bytes)\n",
    address_pointer, new_brake_address, new_brake_address - brake_address);

  free(address_pointer);
  printf("free allocated memory (0x%x)\n", address_pointer);
  brake_address = sbrk(0);
  printf("New brake address: 0x%x (extended by %ld bytes)\n", brake_address, brake_address - new_brake_address);
}
