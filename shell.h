#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"


extern char **environ;


/**
 * struct data -
 * @av: 
 * @input: 
 * @args:
 * @status: 
 * @counter:
 * @_environ: 
 * @pid: 
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s 
 * @separator: ; | &
 * @next: 
 * Description: 
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - 
 * @line: 
 * @next: 
 * Description:  
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - kana zvaka dayi
 * @len_var: 
 * @val: 
 * @len_val: 
 * @next: 
 * Description: 
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - 
 * @name: 
 * @f: 
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* a.c */
sep_list *add_sep_node_ends(sep_list **head, char sep);
void free_sep_lists(sep_list **head);
line_list *add_line_node_ends(line_list **head, char *line);
void free_line_lists(line_list **head);

/* a2.c */
r_var *add_var_node(r_var **head, int lvar, char *var, int lval);
void free_var_list(r_var **head);

/* a */
char *_strdog(char *dest, const char *src);
char *_strcopy(char *dest, char *src);
int _strcomp(char *s1, char *s2);
char *_strchar(char *s, char c);
int _strspin(char *s, char *accept);

/* ac */
void _memcpys(void *newptr, const void *ptr, unsigned int size);
void *_reallocs(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocsdps(char **ptr, unsigned int old_size, unsigned int new_size);

/* a2.c */
char *_strdump(const char *s);
int _strlenth(const char *s);
int cmp_cars(char str[], const char *delim);
char *_strlok(char str[], const char *delim);
int _isdigital(const char *s);

/* a3.c */
void rev_strings(char *s);

/* c.c */
int repeated_chars(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_chars(char *input, int *i);
void print_syntax_errors(data_shell *datash, char *input, int i, int bool);
int check_syntax_errors(data_shell *datash, char *input);

/* s.c */
char *without_comments(char *in);
void shell_loops(data_shell *datash);

/* r.c */
char *read_lines(int *i_eof);

/* s.c */
char *swap_chars(char *input, int bool);
void add_nodels(sep_list **head_s, line_list **head_l, char *input);
void go_nexts(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commandos(data_shell *datash, char *input);
char **split_lines(char *input);

/* r.c */
void check_envs(r_var **h, char *in, data_shell *data);
int check_var(r_var **h, char *in, char *st, data_shell *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_vars(char *input, data_shell *datash);

/* g.c */
void bring_lines(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_lines(char **lineptr, size_t *n, FILE *stream);

/* ee */
int exec_lines(data_shell *datash);

/* c.c */
int is_cdirs(char *path, int *i);
char *_whichs(char *cmd, char **_environ);
int is_executables(data_shell *datash);
int check_error_cmds(char *dir, data_shell *datash);
int cmd_execs(data_shell *datash);

/* e.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* e.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* c.c */
void cd_dots(data_shell *datash);
void cd_tos(data_shell *datash);
void cd_previouse(data_shell *datash);
void cd_tos_home(data_shell *datash);

/* c.c */
int cd_shells(data_shell *datash);

/* gn */
int (*get_builtins(char *cmd))(data_shell *datash);

/* _.c */
int exit_shells(data_shell *datash);

/* a.c */
int get_lens(int n);
char *aux_itoas(int n);
int _atois(char *s);

/* a1.c */
char *strcats_cd(data_shell *, char *, char *, char *);
char *errors_get_cd(data_shell *datash);
char *errors_not_found(data_shell *datash);
char *error_exit_shellss(data_shell *datash);

/* a2.c */
char *error_get_alias(char **args);
char *errors_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_1262(data_shell *datash);


/* g.c */
int get_errors(data_shell *datash, int eval);

/* g.c */
void get_sigints(int sig);

/* a.c */
void aux_helps_env(void);
void aux_helps_setenv(void);
void aux_helps_unsetenv(void);
void aux_helps_general(void);
void aux_helps_exit(void);

/* a2.c */
void aux_helps(void);
void aux_helps_alias(void);
void aux_helps_cd(void);

/* g.c */
int get_helps(data_shell *datash);

#endif
