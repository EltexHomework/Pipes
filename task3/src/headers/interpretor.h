#ifndef INTERPRETOR_H
#define INTERPRETOR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH_LENGTH 128
#define INPUT_LENGTH 256
#define FILENAME_LENGTH 128
#define ARGS_SIZE 16

struct command {
  char* command;
  char** args;
};

struct interpretor {
  char* username;  
  char current_dir[PATH_LENGTH];
};

struct interpretor* create_interpretor();

void run_interpretor(struct interpretor* interpretor);

void execute(struct interpretor* interpretor, struct command** commands, int size);

void change_dir(struct interpretor* interpretor, char* path);

void print_user_info(struct interpretor* interpretor);

void parse(char input[INPUT_LENGTH], struct command** commands, int* size);

void update_username(struct interpretor* interpretor);

void update_dir(struct interpretor* interpretor);

struct command** init_commands();

void dispose(struct interpretor* interpretor);

void clear_commands(struct command** commands);

#endif /* INTERPRETOR_H */
