#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 128

int main(void) {
  char* fifo_path = "/tmp/fifo";
  char buffer[BUFFER_SIZE];
  int file = open(fifo_path, O_RDONLY);
  
  if (read(file, buffer, sizeof(buffer)) < 0) {
    perror("read error");
    exit(EXIT_FAILURE);
  }
  
  printf("Client read: %s\n", buffer);
  close(file); 
  
  return 0;
}
