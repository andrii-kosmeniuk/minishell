/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:14:05 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/20 15:14:06 by milija-h         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct t_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*environment_p; // pointer to copied key-value variables
	char	**env_array; //copy of envp, passed to execve

	int		last_exit_code; // $?
	char	*current_line; // gets its input from readline
	char	*prompt; //minishell promt
	int		interactive; // signals representend by ints
	int		signal_received;
}	t_shell;

//initialization
void	init_env(t_shell *shell, char **envp);

//memory managment
void	free_array(char **array);
void	allocation_failed(char **array, int last_allocated_string);

//utils
t_env	*create_node(char *name, char *value);
int		duplicate_variables(t_shell *shell, char **envp, char *previous_var);

//environment
void	build_minimum_env(t_shell *shell, char **envp);
void	create_list_key_value(t_shell *shell, t_env **head, char **envp);
char	**copy_of_envp(t_shell *shell, char **envp);
