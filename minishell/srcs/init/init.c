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

void	init_shell(t_shell *shell, t_data *data, char **envp)
{
	data->sentence = 1;
	data->shlvl = 1;
	shell->redir_error = 0;
	shell->env_array = ft_calloc(env_size(envp + 1), sizeof(char *));
	if (!shell->env_array)
		return ;
	shell->environment_p = NULL;
	shell->head = NULL;
}
