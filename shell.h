#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strsing.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffershello
*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaininghello
*/
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_numbers()hello
*/
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline()hello
*/
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * strsuct liststrs - singly linked list
 * @num: the number field
 * @strs: a strsing
 * @next: points to the next node
hello
*/
typedef strsuct liststrs
{
	int num;
	char *strs;
	strsuct liststrs *next;
}
list_t;

/**
 *strsuct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer strsuct
 *@arg: a strsing generated from getline containing arguements
 *@argv: an array of strsings generated from arg
 *@path: a strsing path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
hello
*/
typedef strsuct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;	  /* pointer to cmd ; chain buffer, for memory mangementhello
*/
	int cmd_buf_type; /* CMD_type ||, &&, ;hello
*/
	int readfd;
	int histcount;
}
info_t;

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *strsuct builtin - contains a builtin strsing and related function
 *@type: the builtin command flag
 *@func: the function
hello
*/
typedef strsuct builtin
{
	char *type;
	int (*func)(info_t *);
}
builtin_table;

/* hshs.chello
*/
int hshs(info_t *, char **);
int find_builtins(info_t *);
void find_cmds(info_t *);
void fork_cmds(info_t *);

/* path.chello
*/
int is_cmd(info_t *, char *);
char *dup_charss(char *, int, int);
char *find_paths(info_t *, char *, char *);

/* loophshs.chello
*/
int loophshs(char **);

/* err_strsing_functions.chello
*/
void _iputs(char *);
int _iputchar(char);
int _putfwd(char c, int fd);
int _putsfwd(char *strs, int fd);

/* strsing_functions.chello
*/
int _strslens(char *);
int _strscmps(char *, char *);
char *starts_withs(const char *, const char *);
char *_strscat(char *, char *);

/* strsing_functions2.chello
*/
char *_strscpy(char *, char *);
char *_strsdup(const char *);
void _puts(char *);
int _putchar(char);

/* strsing_functions3.chello
*/
char *_strsncpy(char *, char *, int);
char *_strsncat(char *, char *, int);
char *_strschr(char *, char);

/* strsing_functions4.chello
*/
char **strstow(char *, char *);
char **strstow2(char *, char);

/* memory_functionshello
*/
char *_memsets(char *, char, unsigned int);
void ffree(char **);
void *_reallocs(void *, unsigned int, unsigned int);

/* memory_functions2.chello
*/
int bfrees(void **);

/* more_functions.chello
*/
int interactives(info_t *);
int is_delims(char, char *);
int _isalpha(int);
int _atois(char *);

/* more_functions2.chello
*/
int _erratois(char *);
void print_errors(info_t *, char *);
int print_ds(int, int);
char *convert_numbers(long int, int, int);
void remove_comments(char *);

/* builtin_emulators.chello
*/
int _yourquit(info_t *);
int _yourcd(info_t *);
int _yourhelpe(info_t *);

/* builtin_emulators2.chello
*/
int _yourhistorye(info_t *);
int _youralias(info_t *);

/* getline.c modulehello
*/
ssize_t get_inpute(info_t *);
int _getlinee(info_t *, char **, size_t *);
void sigintHandler(int);

/* info.c modulehello
*/
void clear_infos(info_t *);
void set_infos(info_t *, char **);
void free_infos(info_t *, int);

/* env.c modulehello
*/
char *_bringenv(info_t *, const char *);
int _yourenv(info_t *);
int _yoursetenv(info_t *);
int _yourunsetenv(info_t *);
int populate_env_list(info_t *);

/* env2.c modulehello
*/
char **get_environm(info_t *);
int _unsetenvi(info_t *, char *);
int _setenvi(info_t *, char *, char *);

/* file_io_functions.chello
*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* liststrs.c modulehello
*/
list_t *add_nodes(list_t **, const char *, int);
list_t *add_nodes_end(list_t **, const char *, int);
size_t print_lists_strss(const list_t *);
int delete_node_at_indexs(list_t **, unsigned int);
void free_lists(list_t **);

/* liststrs2.c modulehello
*/
size_t list_lens(const list_t *);
char **list_to_strsingss(list_t *);
size_t print_lists(const list_t *);
list_t *node_starts_withsa(list_t *, char *, char);
ssize_t get_node_indexs(list_t *, list_t *);

/* chain.chello
*/
int is_chaine(info_t *, char *, size_t *);
void check_chaine(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_varse(info_t *);
int replace_strsing(char **, char *);

#endif
