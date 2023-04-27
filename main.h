#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
 * struct simple_shell - a data structure for the simple shell
 * @argc: argument count of the shell program
 * @argv: argument vector of the shell program
 * @envp: environment of the shell program
 * @line_buf: line buffer for accepting user input
 * @line_size: size of the line buffer
 * @line_arr: array of lines/user inputs
 * @line_n: the current line number
 * @cmd_argc: argument count of the command given
 * @cmd_argv: argument vector of the command given
 *
 * Description: This data structure is the one we use to hold the data
 *				needed for the shell program.
 */
typedef struct simple_shell
{
	int argc;
	char **argv;
	char **envp;
	char *line_buf;
	size_t line_size;
	char **line_arr;
	int line_n;
	int cmd_argc;
	char **cmd_argv;
} shell_t;

/**
 * struct ss_cmd_handler - a data structure for a simple shell command handler
 * @cmd: command
 * @handle: handler function for the command
 *
 * Description: This data structure is the one we use to match builtin
 *				and executable commands to their appropriate handlers
 */
typedef struct ss_cmd_handler
{
	char *cmd;
	void (*handle)(shell_t *shell);
} cmd_handler_t;

extern char **environ;

/* shell functions */
void initialize_shell(shell_t *shell, int ac, char **av, char **ep);
void execute_cmd(shell_t *shell, int i);
void (*get_cmd_handler(char *cmd))(shell_t *);

/* command handlers */
void handle_empty(shell_t *shell);
void handle_exit(shell_t *shell);
void handle_setenv(shell_t *shell);
void handle_unsetenv(shell_t *shell);
void handle_cd(shell_t *shell);
void handle_executable(shell_t *shell);

/* custom utils 1 */
ssize_t read_input(char **line_ptr, size_t *n, FILE *stream);
char *_which(char *file_name, char *env_var);
int _setenv(const char *name, const char *value);
int _unsetenv(const char *name);

/* custom utils 2 */
char *concat_strings(const char *str1, const char *str2, const char *str3);
char *_getenv_value(const char *name);
char *_getenv_var(const char *name);

/* token utils */
char *_strtok_r(char *str, const char *delim, char **save_ptr);
char **get_tokens(char *str, char *delim);
short count_tokens(char *str, char *delim);
char *malloc_token(char *token);
void change_token(char **old_token, char *new_token);

/* memory utils */
void free_line(shell_t *shell);
void free_string_array(char **str_arr);
void free_shell(shell_t *shell);
void free_environ(shell_t *shell);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* custom library utils */
/* lib 1 */
int _putchar(char c);
int _islower(int c);
int _isalpha(int c);
int _isdigit(int c);
int _abs(int x);
/* lib 2 */
int _atoi(char *s);
int _strlen(const char *s);
char *_strchr(const char *s, char c);
char *_strstr(const char *haystack, const char *needle);
unsigned int _strspn(const char *s, const char *accept);
/* lib 3 */
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, int n);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, int n);
/* lib 4 */
char *_strdup(const char *str);
char *_strpbrk(const char *s, const char *accept);
char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *s, char b, unsigned int n);

#endif
