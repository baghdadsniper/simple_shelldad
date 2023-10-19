#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number2() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ2;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg2: a string generated from getline containing arguements
 *@argv2: an array of strings generated from arg2
 *@path2: a string path2 for the current command
 *@argc2: the argument count
 *@line_count2: the error count
 *@err_num2: the error code for exit()s
 *@linecount_flag2: if on count this line of input
 *@fname2: the program filename
 *@env2: linked list local copy of environ2
 *@environ2: custom modified copy of environ2 from LL env2
 *@history2: the history2 node
 *@alias2: the alias2 node
 *@env_changed2: on if environ2 was changed
 *@status2: the return status2 of the last exec'd command
 *@cmd_buf2: address of pointer to cmd_buf2, on if chaining
 *@cmd_buf_type2: CMD_type ||, &&, ;
 *@readfd2: the fd from which to read line input
 *@histcount2: the history2 line number count
 */
typedef struct passinfo
{
	char *arg2;
	char **argv2;
	char *path2;
	int argc2;
	unsigned int line_count2;
	int err_num2;
	int linecount_flag2;
	char *fname2;
	list_t *env2;
	list_t *history2;
	list_t *alias2;
	char **environ2;
	int env_changed2;
	int status2;

	char **cmd_buf2;   /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type2; /* CMD_type ||, &&, ; */
	int readfd2;
	int histcount2;
} info_t;

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* hsh2.c */
int hsh2(info_t *, char **);
int find_builtin2(info_t *);
void find_cmd2(info_t *);
void fork_cmd2(info_t *);

/* path2.c */
int is_cmd2(info_t *, char *);
char *dup_chars2(char *, int, int);
char *find_path2(info_t *, char *, char *);

/* loophsh2.c */
int loophsh2(char **);

/* err_string_functions.c */
void _eputs2(char *);
int _eputchar2(char);
int _putfd2(char c, int fd);
int _putsfd2(char *str, int fd);

/* string_functions.c */
int _strlen2(char *);
int _strcmp2(char *, char *);
char *starts_with2(const char *, const char *);
char *_strcat2(char *, char *);

/* string_functions2.c */
char *_strcpy2(char *, char *);
char *_strdup2(const char *);
void _puts2(char *);
int _putchar2(char);

/* string_functions3.c */
char *_strncpy2(char *, char *, int);
char *_strncat2(char *, char *, int);
char *_strchr2(char *, char);

/* string_functions4.c */
char **strtow2(char *, char *);
char **strtow2(char *, char);

/* memory_functions */
char *_memset2(char *, char, unsigned int);
void ffree2(char **);
void *_realloc2(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfree2(void **);

/* more_functions.c */
int interactive2(info_t *);
int is_delim2(char, char *);
int _isalpha2(int);
int _atoi2(char *);

/* more_functions2.c */
int _erratoi2(char *);
void print_error2(info_t *, char *);
int print_d2(int, int);
char *convert_number2(long int, int, int);
void remove_comments2(char *);

/* builtin_emulators.c */
int _myexit(info_t *);
int _mycd2(info_t *);
int _myhelp2(info_t *);

/* builtin_emulators2.c */
int _myhistory2(info_t *);
int _myalias2(info_t *);

/* getline.c module */
ssize_t get_input2(info_t *);
int _getline2(info_t *, char **, size_t *);
void sigintHandler2(int);

/* info.c module */
void clear_info2(info_t *);
void set_info2(info_t *, char **);
void free_info2(info_t *, int);

/* env2.c module */
char *_getenv2(info_t *, const char *);
int _myenv2(info_t *);
int _mysetenv2(info_t *);
int _myunsetenv2(info_t *);
int populate_env_list2(info_t *);

/* env2.c module */
char **get_environ2(info_t *);
int _unsetenv2(info_t *, char *);
int _setenv2(info_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file2(info_t *info);
int write_history2(info_t *info);
int read_history2(info_t *info);
int build_history_list2(info_t *info, char *buf, int linecount);
int renumber_history2(info_t *info);

/* liststr.c module */
list_t *add_node2(list_t **, const char *, int);
list_t *add_node_end2(list_t **, const char *, int);
size_t print_list_str2(const list_t *);
int delete_node_at_index2(list_t **, unsigned int);
void free_list2(list_t **);

/* liststr2.c module */
size_t list_len2(const list_t *);
char **list_to_strings2(list_t *);
size_t print_list2(const list_t *);
list_t *node_starts_with2(list_t *, char *, char);
ssize_t get_node_index2(list_t *, list_t *);

/* chain.c */
int is_chain2(info_t *, char *, size_t *);
void check_chain2(info_t *, char *, size_t *, size_t, size_t);
int replace_alias2(info_t *);
int replace_vars2(info_t *);
int replace_string2(char **, char *);

#endif
