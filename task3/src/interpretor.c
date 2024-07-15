#include "headers/interpretor.h"

struct interpretor* create_interpretor() {
  struct interpretor* interpretor = (struct interpretor*) 
    malloc(sizeof(struct interpretor));
  
  if (!interpretor) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  
  update_username(interpretor);
  update_dir(interpretor);

  return interpretor;
}

void run_interpretor(struct interpretor* interpretor) {
  char request[INPUT_LENGTH];
  struct command** commands = init_commands();
  
  int size = 0; 
  while (1) {
    print_user_info(interpretor); 
    
    if (fgets(request, sizeof(request), stdin) == NULL) {
      perror("fgets error");
      exit(EXIT_FAILURE);
    }

    parse(request, commands, &size); 
    execute(interpretor, commands, size);
  }
}

void execute(struct interpretor* interpretor, struct command** commands, int size) {
  struct command* cur_command = commands[0];

  if (strcmp(cur_command->command, "cd") == 0) {
    change_dir(interpretor, cur_command->args[1]);
    return;
  } else if (strcmp(cur_command->command, "exit") == 0) {
    clear_commands(commands);
    dispose(interpretor);
    exit(EXIT_SUCCESS);
  }
  
  int fd[2];
  
  if (pipe(fd) != 0) {
    perror("pipe error");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    pid_t child = fork();

    if (child < 0) {
      perror("fork error");
      exit(EXIT_FAILURE);
    } else if (child == 0) {
      // stdout is fd0 now
      dup2(fd[0], 0);
      close(fd[0]);

      if (i + 1 < size) {
        // stdin is fd1 now
        dup2(fd[1], 1);
        close(fd[1]);
      }

      if (execvp(commands[i]->command, commands[i]->args) < 0) {
        perror("exec error");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
    } else {
      int status;
      close(fd[1]);
      if (waitpid(child, &status, 0) == -1) {
        perror("waitpid error");
      }
    }
  }
}

void print_user_info(struct interpretor* interpretor) {
  printf("%s:%s$ ", interpretor->username, interpretor->current_dir);
}

void change_dir(struct interpretor* interpretor, char* path) {
  if (chdir(path) != 0) {
    perror("chdir error");      
  }

  update_dir(interpretor); 
}

void parse(char input[INPUT_LENGTH], struct command** commands, int* size) {
  int command_index = 0;
  int arg_index = 0;
  char* token = strtok(input, " \n");
  
  if (token == NULL) {
    perror("strtok error");
    return;
  }
  
  while (token != NULL) {
    // found pipeline, parse next command
    if (strcmp(token, "|") == 0) {
      commands[command_index]->args[arg_index] = NULL;
      command_index++;      
      arg_index = 0;
    } 
    // found command arg
    else {
      if (arg_index == 0) {
        commands[command_index]->command = token;
      } 
      commands[command_index]->args[arg_index] = token; 
      arg_index++;       
    }
    token = strtok(NULL, " \n");
  }

  commands[command_index]->args[arg_index] = NULL;
  *size = command_index + 1;
}

void update_username(struct interpretor* interpretor) {
  interpretor->username = getlogin();
  if (interpretor->username == NULL) {
    perror("getlogin error");
    exit(EXIT_FAILURE);
  }
}

void update_dir(struct interpretor* interpretor) {
  if (getcwd(interpretor->current_dir, sizeof(interpretor->current_dir)) == NULL) {
    perror("getcwd error");
    exit(EXIT_FAILURE);
  }
}

struct command** init_commands() {
  struct command** commands = (struct command**) malloc(ARGS_SIZE * sizeof(struct command*));
  
  for (int i = 0; i < ARGS_SIZE; ++i) {
    commands[i] = (struct command*) malloc(sizeof(struct command));
    commands[i]->args = (char**) malloc(ARGS_SIZE * sizeof(char*));
  }
  return commands;
}
void dispose(struct interpretor* interpretor) {
  free(interpretor);
}

void clear_commands(struct command** commands) {
  for (int i = 0; i < ARGS_SIZE; ++i) {
    free(commands[i]->args);
    free(commands[i]);
  }
  free(commands);
}
