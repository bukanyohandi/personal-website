#include "virtual_memory.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>

const u32 MAX_FRAME_ADDRESS = 0x80000000;
const int MAX_BIT = 32;
const int MAX_PAGE_ENTRIES = 262144;

__device__ int new_page_table[MAX_PAGE_ENTRIES];

__device__ void init_invert_page_table(VirtualMemory *vm) {
  for (int i = 0; i < vm->PAGE_ENTRIES; i++) {
    vm->invert_page_table[i] = MAX_FRAME_ADDRESS; // invalid := MSB is 1
    vm->invert_page_table[i + vm->PAGE_ENTRIES] = i;
  }
}

__device__ void vm_init(VirtualMemory *vm, uchar *buffer, uchar *storage,
                        u32 *invert_page_table, int *pagefault_num_ptr,
                        int PAGESIZE, int INVERT_PAGE_TABLE_SIZE,
                        int PHYSICAL_MEM_SIZE, int STORAGE_SIZE,
                        int PAGE_ENTRIES) {
  // init variables
  vm->buffer = buffer;
  vm->storage = storage;
  vm->invert_page_table = invert_page_table;
  vm->pagefault_num_ptr = pagefault_num_ptr;

  // init constants
  vm->PAGESIZE = PAGESIZE;
  vm->INVERT_PAGE_TABLE_SIZE = INVERT_PAGE_TABLE_SIZE;
  vm->PHYSICAL_MEM_SIZE = PHYSICAL_MEM_SIZE;
  vm->STORAGE_SIZE = STORAGE_SIZE;
  vm->PAGE_ENTRIES = PAGE_ENTRIES;

  // before first vm_write or vm_read
  init_invert_page_table(vm);
}

__device__ int findFrame(VirtualMemory *vm, u32 frame_number){
  for(int page = 0; page < vm -> PAGE_ENTRIES; page = page + 1){
    if(vm -> invert_page_table[page + vm -> PAGE_ENTRIES] == frame_number){
      return page;
    }
  }

  return -1;
}

__device__ void leftRotate(VirtualMemory *vm, u32 frame){
  const int PAGE_ENTRIES = vm -> PAGE_ENTRIES;

  int tmp = vm -> invert_page_table[PAGE_ENTRIES + frame];
  for(int page = frame; page < PAGE_ENTRIES - 1; page = page + 1){
    vm -> invert_page_table[page + PAGE_ENTRIES] = vm -> invert_page_table[page + PAGE_ENTRIES + 1];
  }
  vm -> invert_page_table[2 * PAGE_ENTRIES - 1] = tmp;
  return;
  int page = frame;
  while(page + 1 < PAGE_ENTRIES){
    new_page_table[page + PAGE_ENTRIES] =
      vm -> invert_page_table[page + PAGE_ENTRIES + 1];
    page = page + 1;
  }
  new_page_table[2 * PAGE_ENTRIES - 1] = vm -> invert_page_table[frame + PAGE_ENTRIES];
  // Directly copy the values back to vm's invert_page_table
  while(frame < PAGE_ENTRIES){
    vm -> invert_page_table[frame + PAGE_ENTRIES] =
      new_page_table[frame + PAGE_ENTRIES];
    frame = frame + 1;
  }

  return;
}

__device__ uchar vm_read(VirtualMemory *vm, u32 addr) {
  const int PAGE_ENTRIES = vm -> PAGE_ENTRIES;

  // printf("read: %d\n", addr);

  /* Complete vm_read function to read single element from data buffer */
  u32 page_number, page_offset, frame_number;
  bool fault; 
  int page, frame;

  // Decipher page_address to page_number and page_offset
  page_number = addr / MAX_BIT;
  page_offset = addr % MAX_BIT;
  frame_number = -1;

  // Inspect for page faults
  fault = true;
  page = 0;
  while(page < PAGE_ENTRIES){
    if(page_number == vm -> invert_page_table[page]){
      fault = false;
      // Save page in the frame_number
      frame_number = page;
      break;
    }

    page = page + 1;
  }

  // Fault case:
  if(fault){
    *vm -> pagefault_num_ptr += 1;
    frame_number = vm -> invert_page_table[PAGE_ENTRIES];

    // Move information to main memory
    for(int bit = 0; bit < MAX_BIT; ++bit){
        uchar &str = vm -> storage[(vm -> invert_page_table[frame_number]) * MAX_BIT + bit];
        uchar &buf = vm -> buffer[frame_number * MAX_BIT + bit];
        str = buf;
        buf = vm -> storage[page_number * MAX_BIT + bit];
    }

    vm -> invert_page_table[frame_number] = page_number;
  }
  
  // Find frame_number in the frame table
  page = frame = findFrame(vm, frame_number);

  // Perform a left rotation for invert_page_table[frame + PAGE_ENTRIES .. 2 PAGE_ENTRIES-1]
  leftRotate(vm, frame);

  // Copy the left-rotated values from vm's invert_page_table to new_page_table
  // while(page + 1 < PAGE_ENTRIES){
  //   new_page_table[page + PAGE_ENTRIES] =
  //     vm -> invert_page_table[page + PAGE_ENTRIES + 1];
  //   page = page + 1;
  // }
  // new_page_table[2 * PAGE_ENTRIES - 1] = vm -> invert_page_table[frame];
  // // Directly copy the values back to vm's invert_page_table
  // while(frame < PAGE_ENTRIES){
  //   vm -> invert_page_table[frame + PAGE_ENTRIES] =
  //     new_page_table[frame + PAGE_ENTRIES];

  //   frame = frame + 1;
  // }

  return vm -> buffer[frame_number * MAX_BIT + page_offset];
}

__device__ void vm_write(VirtualMemory *vm, u32 addr, uchar value) {
  const int PAGE_ENTRIES = vm -> PAGE_ENTRIES;
  // printf("write: %c to %d\n", value, addr);

  u32 page_number, page_offset, frame_number;
  bool fault; 
  int page, frame;

  // Decipher page_address to page_number and page_offset
  page_number = addr / MAX_BIT;
  page_offset = addr % MAX_BIT;
  frame_number = -1;

  // Inspect for page faults
  fault = true;
  page = 0;
  while(page < PAGE_ENTRIES){
    if(page_number == vm -> invert_page_table[page]){
      fault = false;
      // Save page in the frame_number
      frame_number = page;
      break;
    }

    page = page + 1;
  }

  // if(addr < 32 * 1023 && addr % 1024 == 992){
  //   printf("%d's fault is %d\n", addr, fault);
  // }

  if(fault){
    *vm -> pagefault_num_ptr += 1;
    // if(addr < 32 * 1023 && addr % 1024 == 992){
    //   printf("counted, now page fault equals to %d\n", *vm -> pagefault_num_ptr);
    // }
    // if(*vm -> pagefault_num_ptr % 1024 == 0)
    //   printf("write: %c to %d\n", value, addr);
    frame_number = vm -> invert_page_table[PAGE_ENTRIES];

    // Send information from buffer to storage if frame is full
    if(vm -> invert_page_table[frame_number] != MAX_FRAME_ADDRESS){
      for(int bit = 0; bit < MAX_BIT; ++bit){
        // printf("Storage Size (%d), accessed: %d\n", vm -> STORAGE_SIZE,
        //   vm -> invert_page_table[frame_number] * MAX_BIT + bit);
        // printf("Buffer Size (%d), accessed: %d\n", vm -> PHYSICAL_MEM_SIZE,
        //   frame_number * MAX_BIT + bit);
        // if(vm -> STORAGE_SIZE <= vm -> invert_page_table[frame_number] * MAX_BIT + bit ||
        //   vm -> PHYSICAL_MEM_SIZE <= frame_number * MAX_BIT + bit){
        //     printf("SKIPPED!\n");
        //     continue;
        // }
        vm -> storage[vm -> invert_page_table[frame_number] * MAX_BIT + bit]
          = vm -> buffer[frame_number * MAX_BIT + bit];
      }
    }

    vm -> invert_page_table[frame_number] = page_number;
  }

  vm -> buffer[frame_number * MAX_BIT + page_offset] = value;

  // Find frame_number in the frame table
  page = frame = findFrame(vm, frame_number);

  // Perform a left rotation for invert_page_table[frame + PAGE_ENTRIES .. 2 PAGE_ENTRIES-1]
  leftRotate(vm, frame);

  // Copy the left-rotated values from vm's invert_page_table to new_page_table
  // while(page + 1 < PAGE_ENTRIES){
  //   new_page_table[page + PAGE_ENTRIES] =
  //     vm -> invert_page_table[page + PAGE_ENTRIES + 1];
  //   page = page + 1;
  // }
  // new_page_table[2 * PAGE_ENTRIES - 1] = vm -> invert_page_table[frame];
  // // Directly copy the values back to vm's invert_page_table
  // while(frame < PAGE_ENTRIES){
  //   vm -> invert_page_table[frame + PAGE_ENTRIES] =
  //     new_page_table[frame + PAGE_ENTRIES];

  //   frame = frame + 1;
  // }

  // if(addr == 131071){
  //   for(int i = 0; i < PAGE_ENTRIES; ++i){
  //     if(i != 0) printf(",");
  //     printf("%d", vm -> invert_page_table[i]);
  //   }
  //   printf("\n");
  // }

  return;
}

__device__ void vm_snapshot(VirtualMemory *vm, uchar *results, int offset,
                            int input_size) {
  const int PAGE_ENTRIES = vm -> PAGE_ENTRIES;

  // printf("after write, the number of page fault is: %d\n", *vm -> pagefault_num_ptr);
  // printf("snapshot: %d\n", input_size);

  /* Complete snapshot function together with vm_read to load elements from data
   * to result buffer */
  int page_address = 0;
  while(page_address < input_size){
    u32 actual_page_number, page_number, page_offset, frame_number;
    bool fault; 
    int page, frame;

    // Decipher page_address to page_number and page_offset
    actual_page_number = page_address / MAX_BIT;
    page_number = (page_address + offset) / MAX_BIT;
    page_offset = (page_address + offset) % MAX_BIT;
    frame_number = -1;

    // Inspect for page faults
    fault = true;
    page = 0;
    while(page < PAGE_ENTRIES){
      if(page_number == vm -> invert_page_table[page]){
        fault = false;
        // Save page in the frame_number
        frame_number = page;
        break;
      }

      page = page + 1;
    }

    // Fault case:
    if(fault){
      *vm -> pagefault_num_ptr += 1;
      frame_number = vm -> invert_page_table[PAGE_ENTRIES];

      // Move information to main memory
      for(int bit = 0; bit < MAX_BIT; ++bit){
        uchar &str = vm -> storage[(vm -> invert_page_table[frame_number]) * MAX_BIT + bit];
        uchar &buf = vm -> buffer[frame_number * MAX_BIT + bit];
        str = buf;
        buf = vm -> storage[page_number * MAX_BIT + bit];
      }

      vm -> invert_page_table[frame_number] = page_number;
    }
    
    // Print results from buffer
    for(int bit = 0; bit < MAX_BIT; ++bit){
      results[actual_page_number * MAX_BIT + bit] =
        (uchar) vm -> buffer[frame_number * MAX_BIT + bit];
      // results[page_number * MAX_BIT + bit] = 'W';
    }

    // Find frame_number in the frame table
    page = frame = findFrame(vm, frame_number);

    // Perform a left rotation for invert_page_table[frame + PAGE_ENTRIES .. 2 PAGE_ENTRIES-1]
    leftRotate(vm, frame);

    // Copy the left-rotated values from vm's invert_page_table to new_page_table
    // while(page + 1 < PAGE_ENTRIES){
    //   new_page_table[page + PAGE_ENTRIES] =
    //     vm -> invert_page_table[page + PAGE_ENTRIES + 1];
    //   page = page + 1;
    // }
    // new_page_table[2 * PAGE_ENTRIES - 1] = vm -> invert_page_table[frame];
    // // Directly copy the values back to vm's invert_page_table
    // while(frame < PAGE_ENTRIES){
    //   vm -> invert_page_table[frame + PAGE_ENTRIES] =
    //     new_page_table[frame + PAGE_ENTRIES];

    //   frame = frame + 1;
    // }

    page_address = page_address + 1;
  }
}

