/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:23:53 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 22:31:50 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	init_shell(t_shell *shell, t_state *state, t_data *data, char **envp)
{
	data->shlvl = 1;
	*state = normal;
	shell->redir_error = 0;
	data->heredoc_number = 0;
	shell->env_array = ft_calloc(env_size(envp + 1), sizeof(char *));
	if (!shell->env_array)
		return (false);
	shell->environment_p = NULL;
	shell->head = NULL;
	return (true);
}

void	init_readline(void)
{
	rl_signal_event_hook = readline_event;
}
