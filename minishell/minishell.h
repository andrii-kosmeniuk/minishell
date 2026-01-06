/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:14:05 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 21:22:45 by milija-h         ###   ########.fr       */
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

# define CYAN  "\033[0;36m"
# define RESET "\033[0m"

//errror messages
# define PIPE_FIRST		"bash: syntax error near unexpected token `|'\n"
# define PIPE_END		"bash: syntax error near unexpected token `|'\n"
# define NO_TARGET		"bash: syntax error near unexpected token `newline'\n"
# define REDIR_PIPE		"bash: syntax error near unexpected token `|'\n"
# define HERE_DOC_ERROR	"bash: syntax error near unexpected token `newline'\n"

//extern volatile sig_atomic_t	g_exit_status;

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
	double_q = 2,
}	t_state;

typedef enum s_type
{
	S_QUOTE,// ''
	D_QUOTE,// "" 
	R_INPUT,// <
	R_OUTPUT,// >
	HERE_DOC,// <<
	R_APPEND,// >>
	PIPE,// |
	EXPAND,// $
	WORD
}	t_type;

typedef struct s_redir
{
	t_type			type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	t_type			type;
	t_state			state;
	t_redir			*redir;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}	t_arg;

typedef struct s_cmd
{
	t_arg			*args; //linked list of arguments;
	t_redir			*redirections; //linked list of redirections
	struct s_cmd	*next; //next command if there is a pipe
}	t_cmd;

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

//initialization
void	init_shell(t_shell *shell, t_data *data, char **envp);

//memory managment
void	free_array(char **array);
void	allocation_failed(char **array, int last_allocated_string);
void	free_env_list(t_shell *shell, t_env *env);
void	free_key_value(char *key, char *value);
void	free_all(t_token *tokens, t_shell *shell);
void	free_tokens(t_token *tokens);
void	free_on_cmd_failure(t_shell *shell);
void	free_command(t_cmd *cmds);
//utils
t_env	*create_node(char *name, char *value);
size_t	env_size(char **array);
void	add_to_list(t_env **head, t_env *new);
bool	my_isspace(char c);
//environment
t_env	*list_key_value(t_shell *shell, char **envp, t_data *data);
char	**copy_of_envp(t_shell *shell, char **envp);
int		calculate_new_shlvl(t_shell *shell);
int		update_shlvl_key(t_shell *shell, t_data *data);
//lexer
t_token	*create_token(char *content, t_state state, t_type type);
void	add_token(t_token **head, t_token *new_token);
t_token	*build_token_list(const char *input, t_shell *shell);
t_token	*build_list(t_shell *shell, t_state state, t_type type, char *value);
bool	tokenize_input_redirect(const char *input, t_shell *shell, int *len);
bool	tokenize_output_redirect(const char *input, t_shell *shell, int *len);
bool	tokenize_pipe(const char *input, t_shell *shell, int *len);
bool	tokenize_word(const char *input, t_shell *shell, int *len);
bool	tokenize_double_quotes(t_shell *shell, char *input, int *len);
bool	tokenize_single_quotes(t_shell *shell, char *input, int *len);
//parser
bool	is_argument(t_token *token);
bool	is_redirection(t_token *token);
void	add_cmd_back(t_cmd **head, t_cmd *new_command);
t_cmd	*create_command(void);
t_redir	*add_redir(t_redir **head, t_type type, char *target);
bool	syntax_check(t_shell *shell);
t_arg	*add_args(t_cmd *args, t_token *token);
t_cmd	*parse(t_shell *shell, t_token *token);
void	handle_pipe(t_cmd **current);
char	**argument_array(t_arg *args);

// expansions
char	*expand_string(char *input, t_env *env, int last_exit_status);
//heredoc and append redir
void	heredoc_append(t_redir *redir);
//signals
void	setup_signals(void);

//readline
char	*prompt(const char *prompt);

//debug
void	print_env_list(t_env *head);
void	print_tokens(t_token *token);
void	print_num_of_tokens(t_token *tokens);
void	print_cmd_structure(t_cmd *cmd);

#endif
