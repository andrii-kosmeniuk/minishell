/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:14:05 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 15:52:10 by milija-h         ###   ########.fr       */
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

# define CYAN  "\033[0;36m"
# define RESET "\033[0m"

extern int	g_exit_status;

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
}	t_data;

typedef struct s_shell
{
	t_env	*environment_p; // pointer to copied key-value variables
	char	**env_array; //copy of envp, passed to execve
	char	*current_line; // gets its input from readline
	char	*prompt; //minishell promt
	int		interactive; // signals representend by ints
	int		signal_received;
}	t_shell;

//initialization
void	init_env(t_shell *shell, t_data *data, char **envp);

//memory managment
void	free_array(char **array);
void	allocation_failed(char **array, int last_allocated_string);
void	free_env_list(t_shell *shell, t_env *env);
void	free_key_value(char *key, char *value);
//utils
t_env	*create_node(char *name, char *value);
size_t	env_size(char **array);
void	add_to_list(t_env **head, t_env *new);
char	*ft_strndup(const char *str, size_t len);

//environment
t_env	*list_key_value(t_shell *shell, char **envp, t_data *data);
char	**copy_of_envp(t_shell *shell, char **envp);
int		calculate_new_shlvl(t_shell *shell);
int		update_shlvl_key(t_shell *shell, t_data *data);


//signals
void	setup_signals(void);

//readline
char	*prompt(const char *prompt);

//debug
void	print_env_list(t_env *head);

#endif
