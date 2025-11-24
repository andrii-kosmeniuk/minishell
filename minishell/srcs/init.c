/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:23:53 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/20 20:23:54 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(t_shell *shell, char **envp)
{
	shell->env_array = ft_calloc(env_size(envp + 1), sizeof(char *));
	if (!shell->env_array)
		return ;
	shell->environment_p = malloc(sizeof(t_env) * env_size(shell->env_array));
	if (!shell->environment_p)
	{
		free_array(shell->env_array);
		return ;
	}
}
