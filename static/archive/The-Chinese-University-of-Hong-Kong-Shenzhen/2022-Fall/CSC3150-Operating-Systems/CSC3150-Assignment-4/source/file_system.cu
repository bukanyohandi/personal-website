#include "file_system.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

__device__ __managed__ u32 gtime = 0;
__device__ bool from_fs_write = false;
__device__ u32 invert_location[32768];

__device__ void fs_init(FileSystem *fs, uchar *volume, int SUPERBLOCK_SIZE,
							int FCB_SIZE, int FCB_ENTRIES, int VOLUME_SIZE,
							int STORAGE_BLOCK_SIZE, int MAX_FILENAME_SIZE, 
							int MAX_FILE_NUM, int MAX_FILE_SIZE, int FILE_BASE_ADDRESS)
{
  // init variables
  fs->volume = volume;

  // init constants
  fs->SUPERBLOCK_SIZE = SUPERBLOCK_SIZE;
  fs->FCB_SIZE = FCB_SIZE;
  fs->FCB_ENTRIES = FCB_ENTRIES;
  fs->STORAGE_SIZE = VOLUME_SIZE;
  fs->STORAGE_BLOCK_SIZE = STORAGE_BLOCK_SIZE;
  fs->MAX_FILENAME_SIZE = MAX_FILENAME_SIZE;
  fs->MAX_FILE_NUM = MAX_FILE_NUM;
  fs->MAX_FILE_SIZE = MAX_FILE_SIZE;
  fs->FILE_BASE_ADDRESS = FILE_BASE_ADDRESS;

  for(u32 addr = fs -> SUPERBLOCK_SIZE; addr < fs -> FILE_BASE_ADDRESS; addr += fs -> FCB_SIZE){
    for(u32 offset = 0; offset < fs -> MAX_FILENAME_SIZE; ++offset){
      fs -> volume[addr + offset] = '\0';
    }
  }
  for(u32 addr = 0; addr < fs -> SUPERBLOCK_SIZE; ++addr){
    fs -> volume[addr] = 0;
  }
  return;
}

__device__ u32 get_location(FileSystem *fs, u32 addr){
  return
    fs -> volume[addr + 20] * 256 +
    fs -> volume[addr + 21]; // FCB[20..21]
}

__device__ void set_location(FileSystem *fs, u32 addr, u32 value){
  invert_location[value] = addr;

  fs -> volume[addr + 20] = value / 256;
  fs -> volume[addr + 21] = value % 256; // FCB[20..21]
}

__device__ u32 get_size(FileSystem *fs, u32 addr){
  return
    fs -> volume[addr + 22] * 256 +
    fs -> volume[addr + 23]; // FCB[22..23]
}

__device__ void set_size(FileSystem *fs, u32 addr, u32 value){
  fs -> volume[addr + 22] = value / 256;
  fs -> volume[addr + 23] = value % 256; // FCB[22..23]
}

__device__ u32 get_create(FileSystem *fs, u32 addr){
  return
    fs -> volume[addr + 24] * 256 * 256 * 256 +
    fs -> volume[addr + 25] * 256 * 256 +
    fs -> volume[addr + 26] * 256 +
    fs -> volume[addr + 27]; // FCB[24..27]
}

__device__ void set_create(FileSystem *fs, u32 addr, u32 value){
  fs -> volume[addr + 24] = value / (256 * 256 * 256);
  value %= (256 * 256 * 256);

  fs -> volume[addr + 25] = value / (256 * 256);
  value %= (256 * 256);

  fs -> volume[addr + 26] = value / (256);
  value %= (256);

  fs -> volume[addr + 27] = value; // FCB[24..27]
  return;
}

__device__ u32 get_last_modified(FileSystem *fs, u32 addr){
  return
    fs -> volume[addr + 28] * 256 * 256 * 256 +
    fs -> volume[addr + 29] * 256 * 256 +
    fs -> volume[addr + 30] * 256 +
    fs -> volume[addr + 31]; // FCB[28..31]
}

__device__ void set_last_modified(FileSystem *fs, u32 addr, u32 value){
  fs -> volume[addr + 28] = value / (256 * 256 * 256);
  value %= (256 * 256 * 256);

  fs -> volume[addr + 29] = value / (256 * 256);
  value %= (256 * 256);

  fs -> volume[addr + 30] = value / (256);
  value %= (256);

  fs -> volume[addr + 31] = value; // FCB[28..31]
  return;
}

__device__ bool block_is_filled(FileSystem *fs, u32 block){
  return fs -> volume[block / 8] & (1 << (block % 8));
}

__device__ void block_toggle(FileSystem *fs, u32 block){
  fs -> volume[block / 8] ^= (1 << (block % 8));
  return;
}

__device__ u32 compact(FileSystem *fs){
  u32 last = -1;
  for(u32 block = 0; block < (1 << 15); ++block){
    if(!block_is_filled(fs, block) && last == -1){
      last = block;
    } else if(block_is_filled(fs, block) && last != -1){
      u32 addr = invert_location[block];
      u32 size = get_size(fs, addr);

      for(u32 i = 0; i < size / 32; ++i){
        block_toggle(fs, last + i);
        block_toggle(fs, block + i); // shift indicators to the left

        for(u32 j = 0; j < 32; ++j){
          fs -> volume[fs -> FILE_BASE_ADDRESS + (last + i) * 32 + j] = fs -> volume[fs -> FILE_BASE_ADDRESS + (block + i) * 32 + j];
          fs -> volume[fs -> FILE_BASE_ADDRESS + (block + i) * 32 + j] = 0;
        } // shift contents to the left
      } 

      set_location(fs, addr, last); // set location back

      last = -1;
    }
  }

  for(u32 block = 0; block < (1 << 15); ++block){
    if(!block_is_filled(fs, block)){
      return block;
    }
  }

  printf("[Error] no available blocks left.\n");
  
  return -1;
}

__device__ void block_check(FileSystem *fs, u32 le, u32 ri){
  for(u32 i = le; i < ri; ++i){
    if(block_is_filled(fs, i)){
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}

__device__ u32 strlen(char *s){
  int len = 0;
  while(s[len] != '\0'){
    len++;
  }

  return len;
}

__device__ void strcpy(char *s, char *t){
  for(u32 k = 0; k < strlen(t); ++k){
    s[k] = t[k];
  }

  return;
}

__device__ u32 fs_open(FileSystem *fs, char *s, int op){
  /* Implement open operation here */
  gtime++;
	
  // Search FCB from volume[2^12 .. 2^12 + 2^15)
  for(u32 addr = fs -> SUPERBLOCK_SIZE; addr < fs -> FILE_BASE_ADDRESS; addr += fs -> FCB_SIZE){
    if(fs -> volume[addr] == '\0') continue;

    int k = 0;
    s += '\0';
    while(k < strlen(s) && k < fs -> MAX_FILENAME_SIZE){
      if(fs -> volume[addr + k] != s[k]) break;
      k++;
    } // FCB[0 .. 19]

    // Case for file exists
    if(k == strlen(s)){
      u32 start_block = get_location(fs, addr);

      // Case for file exists and operation mode is write
      if(op == G_WRITE && from_fs_write){
        for(u32 i = 0; i < get_size(fs, addr) / 32; ++i){
          block_toggle(fs, get_location(fs, addr) + i);
        } // set bitmap from 1 to 0 (assume the implementation is correct)
        
        set_size(fs, addr, 0); // set size to 0
        
        start_block = compact(fs);
        
        set_location(fs, addr, start_block); // set location to a new starting block

        set_last_modified(fs, addr, gtime); // set last modified time
      }

      return start_block;
    }
  }

  // Case for file does not exist and operation mode is read
  if(op == G_READ){
    printf("[Error] trying to read a file that does not exist.\n");

    return -1;
  }
  // Case for file does not exist and operation mode is write
  else if(op == G_WRITE){
    for(u32 addr = fs -> SUPERBLOCK_SIZE; addr < fs -> FILE_BASE_ADDRESS; addr += fs -> FCB_SIZE){
      if(fs -> volume[addr] == '\0'){
        s += '\0';
        for(int k = 0; k < strlen(s) && k < fs -> MAX_FILENAME_SIZE; ++k){
          fs -> volume[addr + k] = s[k];
        }

        // printf("%d is now filled by: ", (addr - fs -> SUPERBLOCK_SIZE) / fs -> FCB_SIZE);
        // for(int k = 0; k < strlen(s); ++k){
        //   printf("%c", fs -> volume[addr + k]);
        // }
        // printf("\n");

        set_size(fs, addr, 0); // set size to 0

        u32 start_block = compact(fs);

        set_location(fs, addr, start_block); // set location to a new starting block

        set_create(fs, addr, gtime);

        set_last_modified(fs, addr, gtime); // set last modified time

        return start_block;
      }
    } // search for an empty location;

    printf("[Error] 1024 files already created.\n");

    return -1;
  }
  // Case for unknown operation mode
  else {
    printf("[Error] operation mode is unknown.\n");

    return -1;
  }
}

__device__ void fs_read(FileSystem *fs, uchar *output, u32 size, u32 fp){
	/* Implement read operation here */
  gtime++;

  if(fp == -1){
    printf("The current fs_read process is now stopped due to an error.\n");

    return;
  }

  for(u32 i = 0; i < size; ++i){
    if(!block_is_filled(fs, fp + (i / 32))) continue;
    output[i] = fs -> volume[fs -> FILE_BASE_ADDRESS + fp * 32 + i];
  } // read contents

  return;
}

__device__ u32 fs_write(FileSystem *fs, uchar* input, u32 size, u32 fp){
	/* Implement write operation here */
  gtime++;

  if(fp == -1){
    printf("The current fs_write process is now stopped due to an error.\n");

    return;
  }

  u32 addr = invert_location[fp];
	char s[20];
  for(int k = 0; k < fs -> MAX_FILENAME_SIZE; ++k){
    s[k] = fs -> volume[addr + k];
  }
  
  from_fs_write = true;
  fp = fs_open(fs, s, G_WRITE); // call fs_open (in case fs_write is called without fs_open)
  from_fs_write = false;

  if(fp == -1){
    printf("The current fs_write process is now stopped due to an error.\n");

    return;
  }

  addr = invert_location[fp];
  set_size(fs, addr, size);

  // printf("Try to toggle [%u, %u) from 0 to 1\n", fp, fp + size / 32);
  for(u32 i = 0; i < size / 32; ++i){
    // printf("Toggling %u...\n", fp + i);
    block_toggle(fs, fp + i);
  } // set bitmap from 0 to 1 (assume the implementation is correct)

  for(u32 i = 0; i < size; ++i){
    fs -> volume[fs -> FILE_BASE_ADDRESS + fp * 32 + i] = input[i];
  } // write contents

  set_last_modified(fs, addr, gtime); // set last modified time

  return 0;
}

__device__ void fs_gsys(FileSystem *fs, int op){
	/* Implement LS_D and LS_S operation here */
  gtime++;
	
  u32 n = 0;
  u32 rank[1024];
  u32 size[1024];
  u32 create[1024];
  u32 last_modified[1024];

  for(u32 addr = fs -> SUPERBLOCK_SIZE; addr < fs -> FILE_BASE_ADDRESS; addr += fs -> FCB_SIZE){
    if(fs -> volume[addr] == '\0') continue;

    // printf("%d is found as ", (addr - fs -> SUPERBLOCK_SIZE) / fs -> FCB_SIZE);
    // for(u32 offset = 0; offset < fs -> MAX_FILENAME_SIZE; ++offset){
    //   if(offset == 20) break;
    //   printf("%c", fs -> volume[addr + offset]);
    // }
    // printf("\n");

    rank[n] = (addr - fs -> SUPERBLOCK_SIZE) / fs -> FCB_SIZE;
    size[n] = get_size(fs, addr);
    create[n] = get_create(fs, addr);
    last_modified[n] = get_last_modified(fs, addr);
    n++;
  }

  if(n == 0){
    printf("[Error] no file found.\n");

    return;
  }
  
  // Sort use bubble sort algorithm
  for(u32 i = 0; i < n; ++i){
    for(u32 j = i + 1; j < n; ++j){
      if( (op == LS_D && last_modified[i] < last_modified[j]) ||
          (op == LS_S && (size[i] < size[j] || (size[i] == size[j] && create[i] > create[j])))
        ){
        u32 rank_tmp;
        rank_tmp = rank[i];
        rank[i] = rank[j];
        rank[j] = rank_tmp;

        u32 size_tmp;
        size_tmp = size[i];
        size[i] = size[j];
        size[j] = size_tmp;

        u32 create_tmp;
        create_tmp = create[i];
        create[i] = create[j];
        create[j] = create_tmp;

        u32 last_modified_tmp;
        last_modified_tmp = last_modified[i];
        last_modified[i] = last_modified[j];
        last_modified[j] = last_modified_tmp;
      }
    }
  }

  if(op == LS_D){
    printf("===sort by modified time===\n");
  } else if(op == LS_S){
    printf("===sort by file size===\n");
  } else {
    printf("[Error] operation mode is unknown.\n");

    return;
  }

  for(u32 i = 0; i < n; ++i){

    u32 file_location = rank[i];
    
    // printf("%u. ", file_location);

    char s[20];
    for(u32 j = 0; j < fs -> MAX_FILENAME_SIZE; ++j){
      s[j] = '\0';
    }

    for(u32 j = 0; j < fs -> MAX_FILENAME_SIZE; ++j){
      char c = fs -> volume[fs -> SUPERBLOCK_SIZE + file_location * fs -> FCB_SIZE + j];
      if(c == '\0') break;
      s[j] = c;
      // printf("%c", c);
    }
    printf("%s", s);

    if(op == LS_S) printf(" %u", size[i]);

    printf("\n");
  }

  // printf("Total files: %u\n", n);

  return;
}

__device__ void fs_gsys(FileSystem *fs, int op, char *s){
	/* Implement rm operation here */
  gtime++;

  if(op == RM){
    for(u32 addr = fs -> SUPERBLOCK_SIZE; addr < fs -> FILE_BASE_ADDRESS; addr += fs -> FCB_SIZE){
      if(fs -> volume[addr] == '\0') continue;

      s += '\0';

      int k = 0;
      while(k < strlen(s) && k < fs -> MAX_FILENAME_SIZE){
        if(fs -> volume[addr + k] != s[k]) break;
        k++;
      } // FCB[0 .. 19]

      if(k == strlen(s)){
        for(u32 offset = 0; offset < fs -> MAX_FILENAME_SIZE; ++offset){
          fs -> volume[addr + offset] = '\0';
        }

        for(u32 i = 0; i < get_size(fs, addr) / 32; ++i){
          block_toggle(fs, get_location(fs, addr) + i);
        } // set bitmap from 1 to 0 (assume the implementation is correct)

        return;
      }
    }

    printf("[Error] file does not exist.\n");
  } else {
    printf("[Error] operation mode is unknown.\n");
  }

  return;
}
