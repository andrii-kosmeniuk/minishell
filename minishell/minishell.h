/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:14:05 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/17 18:25:00 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>

# define CYAN  "\033[0;36m"
# define RESET "\033[0m"

//error messages
# define PIPE_FIRST		"bash: syntax error near unexpected token `|'\n"
# define PIPE_END		"bash: syntax error near unexpected token `|'\n"
# define NO_TARGET		"bash: syntax error near unexpected token `newline'\n"
# define REDIR_PIPE		"bash: syntax error near unexpected token `|'\n"
# define HERE_DOC_ERROR	"bash: syntax error near unexpected token `newline'\n"
# define ERROR_OPENING_FILE "heredoc: error opening heredoc file\n"
# define ERROR_EXPANDING_HEREDOC	"could not expand heredoc\n"
# define HEREDOC_ABORTED	130

# define NORMAL 0x00
# define CTRL_C 0x01
# define INSIDE_HEREDOC 0x02
# define HEREDOC_CTRL  0x03

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int	shlvl;
	int	last_exit_code;
	int	heredoc_number;
}	t_data;

typedef enum s_state
{
	normal = 0,
	single_q = 1,
	double_q = 2
}	t_state;

typedef enum s_type
{
	S_QUOTE = 0,// ''
	D_QUOTE = 1,// "" 
	R_INPUT = 2,// <
	R_OUTPUT = 3,// >
	HERE_DOC = 4,// <<
	R_APPEND = 5,// >>
	PIPE = 6,// |
	EXPAND = 7,// $
	WORD = 8
}	t_type;

typedef struct s_redir
{
	t_type			type;
	char			*target;
	int				heredoc_fd;
	bool			expand_heredoc;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	t_type			type;
	t_state			state;
	t_redir			*redir;
	char			*content;
	bool			should_expand;
	struct s_token	*next;
}	t_token;

typedef struct s_arg
{
	char			*value;
	t_type			type;
	struct s_arg	*next;
}	t_arg;

typedef struct s_cmd
{
	char			**args;
	int				argc;
	t_redir			*redirections; //linked list of redirections
	struct s_cmd	*next; //next command if there is a pipe
}	t_cmd;

typedef struct s_expand
{
	char	*output;
	t_env	*env;
	size_t	len;
	int		exit_code;
}	t_expand;

typedef struct s_shell
{
	t_env	*environment_p; // pointer to copied key-value variables
	t_token	*head; //list of tokens
	t_state	state;
	t_type	type;
	char	**env_array; //copy of envp, passed to execve
	char	*current_line; // gets its input from readline
	char	*prompt; //minishell promt
	int		interactive; // signals representend by ints
	int		signal_received;
	int		redir_error;
}	t_shell;

//main
void	add_process_free(char *line, t_shell *shell);
void	shell_loop(t_shell*shell);
int		process_line(char *line, t_shell *shell);
int		init_minishell(t_shell *shell, t_state *state,
			t_data *data, char **envp);

//initialization
bool	init_shell(t_shell *shell, t_state *state, t_data *data, char **envp);

//memory managment
void	free_array(char **array);
void	allocation_failed(char **array, int last_allocated_string);
void	free_env_list(t_shell *shell, t_env *env);
void	free_key_value(char *key, char *value);
void	free_all(t_token *taokens, t_shell *shell);
void	free_tokens(t_token *tokens);
void	free_on_cmd_failure(t_shell *shell);
void	free_command(t_cmd *cmds);
void	cleanup_shell(t_shell *shell);
void	cleanup_tokens(t_shell *shell);

//utils
t_env	*create_node(char *name, char *value);
size_t	env_size(char **array);
void	add_to_list(t_env **head, t_env *neww);
char	*substring(char *start_of_word, size_t len);
int		alpha_numeric_underscore(int c);
bool	my_isspace(char input);
bool	is_word_quoted(t_token *token);
void	get_state(t_shell *shell, char quote);
//environment
t_env	*list_key_value(t_shell *shell, char **envp, t_data *data);
char	**copy_of_envp(t_shell *shell, char **envp);
int		calculate_new_shlvl(t_shell *shell);
int		update_shlvl_key(t_shell *shell, t_data *data);
//lexer
t_token	*create_token(char *content, t_state state, t_type type,
			bool should_expand);
void	add_token(t_token **head, t_token *new_token);
t_token	*build_token_list(const char *input, t_shell *shell);
t_token	*build_list(t_shell *shell, t_type type, char *value,
			bool should_expand);
bool	tokenize_input_redirect(const char *input, t_shell *shell, int *len);
bool	tokenize_output_redirect(const char *input, t_shell *shell, int *len);
bool	tokenize_pipe(const char *input, t_shell *shell, int *len);
int		tokenize_word(const char *input, t_shell *shell, int *len);
bool	tokenize_double_quotes(t_shell *shell, char *input, int *len);
bool	tokenize_single_quotes(t_shell *shell, char *input, int *len);
//parser
bool	is_argument(t_token *token);
bool	is_redirection(t_token *token);
void	add_cmd_back(t_cmd **head, t_cmd *new_command);
t_cmd	*create_command(void);
t_redir	*add_redir(t_token *tokens, t_redir **head, t_type type, char *target);
bool	syntax_check(t_shell *shell);
t_cmd	*add_args(t_cmd *cmd, t_token *token);
t_cmd	*parse(t_shell *shell, t_token *token);
bool	handle_pipe(t_cmd **current);
char	**argument_array(t_arg *args);

// expansions
bool	append_string(char **buffer, size_t *len, char *str);
bool	append_char(char **buffer, size_t *len, char c);
char	*get_value(t_env *env, char *variable_name);
bool	is_valid(char c);
char	*read_variable_name(char *input, char *start_of_variable);
char	**word_split(char *expanded);
char	**final_args(char *input, t_env *env, bool should_expand, int exit);
char	**expand_final_args(t_token *tokens, t_env *env, int exit);
char	*expand_string(char *input, t_env *env, int exit);
char	*process_tokens(t_token *tokens, t_env *env, int exit);
char	*final_expand(char *input, t_env *env);

//heredoc and append redir
bool	heredoc_append(t_redir *redir, t_env *env, int exit);
bool	handle_append(t_redir *redir);
char	*choose_file_name(void);
int		open_temp_file(char **filename);
void	write_to_file(int fd, char *content);
char	*expand_heredoc(t_redir *redir, t_env *env, char *line, int exit);

//signals
void	restore_interactive_signals(void);
void	sigint_handler(int sig);
int		handle_signal_event(void);
void	heredoc_sigint_handler(int sig);
void	setup_heredoc_signals(void);
void	setup_interactive_signals(void);
//debug
void	print_env_list(t_env *head);
void	print_tokens(t_token *token);
void	print_num_of_tokens(t_token *tokens);
void	print_cmd_structure(t_cmd *cmd);
void	print_array(char **array);

#endif
