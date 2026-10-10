#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

int main(void) {
  void *old_break = sbrk(256);

  printf("old_break: %p\n", old_break);

  struct header *block1 = (struct header *)old_break;
  block1->size = 128;
  block1->next = NULL;

  printf("Block1 address: %p\n", (void *)block1);
  printf("Block1 size:    %lu\n", block1->size);
  printf("Block1 next:    %p\n", (void *)block1->next);

  void *block2_addr = (char *)old_break + 128;
  struct header *block2 = (struct header *)block2_addr;
  block2->size = 128;
  block2->next = block1;

  char *data1 = (char *)block1 + sizeof(struct header);
  for (size_t i = 0; i < 128 - sizeof(struct header); i++)
    data1[i] = 0;

  char *data2 = (char *)block2 + sizeof(struct header);
  for (size_t i = 0; i < 128 - sizeof(struct header); i++)
    data2[i] = 1;

  printf("Block2 address: %p\n", (void *)block2);
  printf("Block2 size:    %lu\n", block2->size);
  printf("Block2 next:    %p\n", (void *)block2->next);

  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    printf("%d\n", data1[i]);
  }
  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    printf("%d\n", data2[i]);
  }
  return 0;
}
