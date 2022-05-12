#include <stdio.h>

// to get block size
// - bitwise AND with 0b 1111 1110
// - bitwise shift to remove allocation status (header & 0xFE) >> 1


bool blockIsFree(int heap_node)
{
  if (heap_node & 1 == 1)
    return false
  else
    return true
}


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
    if (blockIsFree(heap[i]) && (getSize(heap[i])-2)>= sz) // maybe check if vald bit and length in same function?
     // block is free and fits the requested size
      found = 1; break; 
       i += getSize(heap[i]); // go to header of next block 
  }

  '''
  // Code from slides:
  p = start; 
  while ((p < end) && ((*p & 1) || (*p <= len))) 
    p = p + (*p & -2);    \\ goto next block (word addressed)

  int i = 0;
  int found = 0;

  while ((i < 63) && (heap[i] & 1 == 1) || (heap[i] & -2 < sz + 2)) // Check to see if there is free room for length + 2 (header/footer)
    i++;

  if (i < 63){
    // Allocate block in heap
    header = sz | 1;
    heap[i] = header
    // Set subsequent nodes in heap to 1
    int j;
    for (j = 0; j < sz; j++)
      heap[i + j] = 1;
    heap[i + j + 1] = header;
    printf (i + 1);
  }
  else{
    // Return error
  }
  '''
}

void free(int index){
  int currentHeaderIndex;
  int currentFooterIndex;
  int currentBlockSize;

  // Can assume argument is a pointer to correct address of PAYLOAD (not header)
  int size = heap[index - 1] & -2;
  int i;
  // Set least significant header bit to 0
  heap[index - 1] = size & -2;
  // Set payload nodes to 0
  for (i = 0; i < size; i++)
  {
    heap[index + i] = 0;
  }
  // Clear allocated flag in footer
  heap[index + i + 1] = size & -2;

  currentBlockSize = size;
  currentHeaderIndex = index - 1;
  currentFooterIndex = index + size;

  // TODO: Add coalescing functionality
    // Maybe check previous block first before freeing current block
    // Make new variables for current header index and total block size(to account for possible backward coalescing)

  // Check if next block is free (forward coalescing)
  nextHeaderIndex = currentFooterIndex + 1;
  if (heap[nextHeaderIndex] & 1 == 0){
    // TODO: Implement forward coalescing
    // Get size of free block
    int nextBlockSize = heap[nextHeaderIndex] & -2;
    currentBlockSize = currentBlockSize + nextBlockSize;
    // Clear currentFooter and nextHeader
    heap[currentFooterIndex] = 0;
    heap[nextHeaderIndex] = 0;
    // Update nextBlockFooter
    currentFooterIndex = currentFooterIndex + nextBlockSize + 2;
    heap[currentFooterIndex] = currentBlockSize & -2;                 // CHECK IF FOOTER BEING SET CORRECTLY (storing size of block and 0 flag)
    // Update currentHeader
    heap[currentHeaderIndex] = currentBlockSize & -2;
  }
  
  // Check if previous block is free (backward coalescing)

}

void init(){
  heap[0] = 62
  heap[63] = 62

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

void p_malloc(int size)
{
  
}

void p_free(int index){
  
}


void p_blocklist()
{
  
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
    p_malloc(atoi(argv[1]));
    
  }
  else if (strcmp(command, "free") == 0)
  {
    p_free(atoi(argv[1]);
  }
  else if (strcmp(command, "blocklist") == 0)
  {
    p_blocklist(atoi(argv[1]));
  }
  else if (strcmp(command, "writememe") == 0)
  {
    write_m(atoi(argv[1]), argv[2]);
  }
  else if (strcmp(command, "printmeme") == 0)
  {
    print_m(atoi(argv[1]), atoi(argv[2]);
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
  unsigned char heap[64];
  init();
  loop();
  return 0;
}
