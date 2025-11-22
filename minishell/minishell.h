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
