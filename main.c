#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXARGS 3

// to get block size
// - bitwise AND with 0b 1111 1110
// - bitwise shift to remove allocation status (header & 0xFE) >> 1

unsigned char heap[64];


int blockIsFree(int heap_node)
{
  if (heap_node % 2 == 1)
    return 0;
  else
    return 1;
}


int getSize(int header)
{
  return (header / 2)-2;
}


int findFirstFree(int sz)
{
  if (blockIsFree(heap[0]) == 1 && getSize(heap[0]) >= sz){
    return 0;
  }
  else
  {
    int index = 0;
    do{
      index += getSize(heap[index]) + 2;
    }while(blockIsFree(heap[index]) != 1 || getSize(heap[index]) < sz);

    return index;
  }
}





void allocateBlock(int sz){
  //int i = 0; // pointer to beginning of heap
  //int found = 0; // a flag 
  
  // while (!found && i < 64){
  //   if (blockIsFree(heap[i]) && (getSize(heap[i])-2)>= sz) // maybe check if vald bit and length in same function?
  //    // block is free and fits the requested size
  //     found = 1; break; 
  //      i += getSize(heap[i]); // go to header of next block 
  // }

  int start = findFirstFree(sz);
  int len = getSize(heap[start]);

  if (len > sz + 2)
  {
    // need splitting TO DO:
    heap[start] = ((sz+2) << 1) + 1;
    
    int i;
    for (i = 1; i<=sz; i++){
      heap[start+i] = 1;
    }
    heap[start+i] = ((sz+2) << 1) + 1;


    int nl = len - (sz+2);
    heap[start+i+1] = (nl+2) << 1;
    heap[start+i+1+nl+1] = (nl+2) << 1;


  }
  else
  {
    heap[start] = ((len+2) << 1) + 1;
    int i;
    for (i = 1; i<len; i++){
      heap[start+i] = 1;
    }
    heap[start+i] = ((len+2) << 1) + 1;
  }

  printf("%d\n",start+1);

  // '''
  // // Code from slides:
  // p = start; 
  // while ((p < end) && ((*p & 1) || (*p <= len))) 
  //   p = p + (*p & -2);    \\ goto next block (word addressed)

  // int i = 0;
  // int found = 0;

  // while ((i < 63) && (heap[i] & 1 == 1) || (heap[i] & -2 < sz + 2)) // Check to see if there is free room for length + 2 (header/footer)
  //   i++;

  // if (i < 63){
  //   // Allocate block in heap
  //   header = sz | 1;
  //   heap[i] = header
  //   // Set subsequent nodes in heap to 1
  //   int j;
  //   for (j = 0; j < sz; j++)
  //     heap[i + j] = 1;
  //   heap[i + j + 1] = header;
  //   printf (i + 1);
  // }
  // else{
  //   // Return error
  // }
  // '''
}

void p_free(int index){
  // Can assume argument is a pointer to correct address of PAYLOAD (not header)
  int size = getSize(heap[index-1]);
  int i;
  // Set least significant header bit to 0
  heap[index - 1] = (size+2) << 1;
  // Set payload nodes to 0
  for (i = 0; i < size; i++)
  {
    heap[index + i] = 0;
  }
  // Clear allocated flag in footer
  heap[index + i] = (size+2) << 1;

  // Set current variables before checking for forward or backward coalescing
  int currentBlockSize = size;
  int currentHeaderIndex = index - 1;
  int currentFooterIndex = index + size;

  // TODO: Add coalescing functionality
    // Maybe check previous block first before freeing current block
    // Make new variables for current header index and total block size(to account for possible backward coalescing)

  // Check if next block is free (forward coalescing)
  int nextHeaderIndex = currentFooterIndex + 1;
  if (nextHeaderIndex <= 62)
  {
    if (blockIsFree(heap[nextHeaderIndex])){
    // TODO: Implement forward coalescing
    // Get size of free block
      int nextBlockSize = getSize(heap[nextHeaderIndex]);
      currentBlockSize = currentBlockSize + nextBlockSize + 2;
    // Clear currentFooter and nextHeader
      heap[currentFooterIndex] = 0;
      heap[nextHeaderIndex] = 0;
    // Update nextBlockFooter
      currentFooterIndex = currentFooterIndex + nextBlockSize + 2;
      heap[currentFooterIndex] = (currentBlockSize+2) << 1;                 // CHECK IF FOOTER BEING SET CORRECTLY (storing size of block and 0 flag)
    // Update currentHeader
      heap[currentHeaderIndex] = (currentBlockSize+2) << 1;
    }
  }
  
  // Check if previous block is free (backward coalescing)
  int previousFooterIndex = currentHeaderIndex - 1;

  if (previousFooterIndex >= 2)
  {
    if (blockIsFree(heap[previousFooterIndex])){
    // TODO: Implement backward coalescing
    // Get size of prev free block
      int prevBlockSize = getSize(heap[previousFooterIndex]);
      currentBlockSize = currentBlockSize + prevBlockSize + 2;
    // Clear currentHeader and prevFooter
      heap[currentHeaderIndex] = 0;
      heap[previousFooterIndex] = 0;
    // Update prevHeader to currentHeader
      currentHeaderIndex = currentHeaderIndex - prevBlockSize - 2;
      heap[currentHeaderIndex] = (currentBlockSize+2) << 1;
      heap[currentFooterIndex] = (currentBlockSize+2) << 1;
    }

  }

}


void blocklist()
{
  // Print out all info regarding each allocated and free block
  // Format: start index of PAYLOAD (not header), size of block, allocaton status (allocated or free)
  int i;
  i = 0;
  while (i < 63) {
    int currentBlockSize = getSize(heap[i]);
    int currentAllocationStatus = heap[i] % 2;
    printf("%d, %d, ", i + 1, currentBlockSize);
    if (currentAllocationStatus == 0)
      printf("free.\n");
    else
      printf("allocated.\n");
    i = i + currentBlockSize + 2;
  }

}

void writemem(int index, char* str){
  int i = 0;
  while (str[i] != '\0'){
    heap[index + i] = str[i];
    i++;
  }
}



void init(){
  heap[0] = 64 << 1;
  heap[63] = 64 << 1;

  int i;
  for (i = 1; i <63; i++){
    heap[i] = 0;  
  }
  
}

void tokenize(char *input, char *args[MAXARGS])
{
  //char **argv;
  int i = 0;
  char *token = strtok(input, " \n");
  do
  {
    args[i] = token;
    i++;
  }
  while ((token = strtok(NULL, " \n")));

}


void write_m(int index, char* str){
  
}


void print_m(int index, int n){
  
}

void execute(char* argv[MAXARGS])
{
  char *command = argv[0];

  if (strcmp(command, "malloc") == 0)
  {
    allocateBlock(atoi(argv[1]));
    
  }
  else if (strcmp(command, "free") == 0)
  {
    p_free(atoi(argv[1]));
  }
  else if (strcmp(command, "blocklist") == 0)
  {
    blocklist();
  }
  else if (strcmp(command, "writememe") == 0)
  {
    write_m(atoi(argv[1]), argv[2]);
  }
  else if (strcmp(command, "printmeme") == 0)
  {
    print_m(atoi(argv[1]), atoi(argv[2]));
  }
  
}

void loop() {
  char input[100];
  char *args[MAXARGS];
  do {
    printf("> ");
    fgets(input, 80, stdin);
    //args = tokenize((char *) input);
    tokenize((char *)input, args);
    if (strcmp(args[0], "quit") == 0)
      exit(0);
    execute(args);
  } while (1);
}


int main(int argc, char** argv) {
  init();
  loop();
  return 0;
}
