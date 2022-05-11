#include <stdio.h>

// to get block size
// - bitwise AND with 0b 1111 1110
// - bitwise shift to remove allocation status (header & 0xFE) >> 1



// find next block’s header
int next_header = current_footer + 1 
if (current_footer < 63 && blockIsFree(heap[next_header])){
 // perform forward coalescing
 // (1) change current_header’s block size to account
 // for next_header’s block size 
 // (2) update next_footer’s block size. Current_footer
 // now becomes part of the payload 
 // (3) zero’d out each byte of payload. NOTE: this is an
 // requirement for this assignment. Real malloc will
 // not do this because of speed!

// find previous block’s footer
int previous_footer = current_header - 1 
if (current_header > 0 && blockIsFree(heap[previous_footer])){
 // perform backward coalescing
 // (1) update previous_header’s block size. current_header 
 // now becomes part of the payload
 // go to previous header
  int previous_header = previous_footer + 1 - previous_block_size
 // (2) change current_footer’s block size to account
 // for previous_header’s block size 
 // (3) zero’d out each byte of payload. NOTE: this is an
 // requirement for this assignment. Real malloc will
 // not do this because of speed!
}



void allocateBlock(int sz){
  int i = 0; // pointer to beginning of heap
  int found = 0; // a flag 
  while (!found && i < 64){
    if (blockIsFree(heap[i]) && (getSize(heap[i])-2)>= sz)
     // block is free and fits the requested size
      found = 1; break; 
       i += getSize(heap[i]); // go to header of next block 
  }
}





int main(void) {
  unsigned char heap[64];

  printf("Hello World\n");
  return 0;
}