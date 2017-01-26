#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Reimplementation of malloc, realloc, calloc and free following the tutorial at
// http://danluu.com/malloc-tutorial/

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
  #ifdef DEBUG
  int magic; // For debugging only. TODO: remove this in non-debug mode.
  #endif
};

#define META_SIZE sizeof(struct block_meta)
#define ALIGNMENT 16

struct block_meta *global_base;

/**
 *  Finds a the first block of unallocated heap space which is large enough to fit
 *  data of size `size`.
 */
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

/**
 *  Requests more space in the program's segment from the OS.
 */
struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*)block == request); // Not thread safe.
  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  }

  if (last) { // NULL on first request.
    last->next = block;
  }
  
  block->size = size;
  block->next = NULL;
  block->free = 0;
  #ifdef DEBUG
  block->magic = 0x12345678;
  #endif
  return block;
}

/**
 *  Allocates `size` bytes onto the heap.
 */
void *malloc(size_t size) {
  struct block_meta *block;

  if (size <= 0) {
    return NULL;
  }

  int alignmentExcess = size % ALIGNMENT;
  int alignmentPadding = 0;

  if (alignmentExcess != 0) {
    alignmentPadding = ALIGNMENT - alignmentExcess;
  }

  size += alignmentPadding;

  if (!global_base) { // First call.
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block;
  } else {
    struct block_meta *last = global_base;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block) {
        return NULL;
      }
    } else {      // Found free block
      // TODO: consider splitting block here.
      if (block->size > size) {
        struct block_meta block = { .size = block->size, .next = block->next, .free = 1, .magic = 0x12345 };
        
      }
      block->free = 0;
      #ifdef DEBUG
      block->magic = 0x77777777;
      #endif
    }
  }

  return(block+1);
}

/**
 *  Gets the metadata associated with a block in the heap starting at address `ptr`
 */
struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}

/**
 *  Frees the block of heap allocated by `malloc`
 */
void free(void *ptr) {
  if (!ptr) {
    return;
  }

  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta* block_ptr = get_block_ptr(ptr);
  assert(block_ptr->free == 0);
  block_ptr->free = 1;
  #ifdef DEBUG
  assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
  block_ptr->magic = 0x55555555;
  #endif
}

/**
 *  Reallocates space in the heap allocated by `malloc`
 */
void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    // NULL ptr. realloc should act like malloc.
    return malloc(size);
  }

  struct block_meta* block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    // We have enough space. Could free some once we implement split.
    return ptr;
  }

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  void *new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr) {
    return NULL; // TODO: set errno on failure.
  }
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);
  return new_ptr;
}

void *calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize; // TODO: check for overflow.
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}