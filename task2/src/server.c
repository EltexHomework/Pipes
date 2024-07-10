#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
  char* string = "Hi!";
  char* fifo_path = "/tmp/fifo";
  int file; 
  
  mkfifo(fifo_path, 0666);
  file = open(fifo_path, O_WRONLY);
  
  if (write(file, string, strlen(string)) == -1) {
    perror("write error");
    exit(EXIT_FAILURE);
  }
  
  close(file);
  
  return 0;
}
