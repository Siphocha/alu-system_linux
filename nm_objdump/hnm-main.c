#include "hnm.h"

/**
 * main - the entry point
 * program made for the ELF file processing program
 * @argc: the count of command-line arguments
 * @argv: the array of command-line arguments,
 *        where argv[1] is expected to be the path to the ELF file
 * Return: 0 on successful execution,
 *         or 0 in case of an error such as missing file argument
 *         or unsupported ELF file type
 * Author: Frank Onyema Orji
 */

int main(int argc, char *argv[])
{
    char *file_path = argv[1];

    if (argc < 2)
    {
        printf("Il faut fournir un fichier ELF !\n");
        return (0);
    }

    FILE *file = fopen(file_path, "rb");

    if (file == NULL)
    {
        printf("Il y a une erreur pour de l'ouverture du fichier\n");
        return (0);
    }

    Elf64_Ehdr elf_header;
    fread(&elf_header, sizeof(Elf64_Ehdr), 1, file);

    if (elf_header.e_ident[EI_CLASS] == ELFCLASS32)
    {
        process_elf_file32(file_path);
    }
    else if (elf_header.e_ident[EI_CLASS] == ELFCLASS64)
    {
        process_elf_file64(file_path);
    }
    else
    {
        printf("Type de fichier ELF non pris en charge...\n");
    }

    fclose(file);

    return (0);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_COMMANDS 16

// Function prototypes
void shell_loop();
char* read_input();
char** parse_input(char* input);
int execute_command(char** args);
int execute_builtin(char** args);
void handle_redirection(char** args);
void handle_pipes(char* input);
void execute_single_command(char** args);

// Built-in command functions
int shell_cd(char** args);
int shell_pwd(char** args);
int shell_echo(char** args);
int shell_exit(char** args);
int shell_help(char** args);

// Built-in command names and functions
char* builtin_commands[] = {
    "cd",
    "pwd", 
    "echo",
    "exit",
    "help"
};

int (*builtin_functions[])(char**) = {
    &shell_cd,
    &shell_pwd,
    &shell_echo,
    &shell_exit,
    &shell_help
};

int num_builtins() {
    return sizeof(builtin_commands) / sizeof(char*);
}

}
