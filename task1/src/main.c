#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 128

int main(void) {
  int fd[2];
  pid_t child_pid;
  
  if (pipe(fd) != 0) {
    perror("pipe error");
    exit(EXIT_FAILURE);
  }
  
  if ((child_pid = fork()) == -1) {
    perror("fork error");
    exit(EXIT_FAILURE);
  } else if (child_pid == 0) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    
    close(fd[1]);
    bytes_read = read(fd[0], buffer, sizeof(buffer));
    if (bytes_read <= 0) {
      perror("read error");
      exit(EXIT_FAILURE);
    }

    printf("Child read string: %s\n", buffer);
  } else {
    char* string = "Hi!";
    int status;
    
    close(fd[0]);
    if (write(fd[1], string, strlen(string)) == -1) {
      perror("write error");
      exit(EXIT_FAILURE); 
    }
    
    while (wait(&status) > 0);
  }

  return 0;
}
