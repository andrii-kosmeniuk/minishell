/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:14:16 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/22 22:14:17 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//this build our own envp
//env_array is allocated for total len of envp + NULL terminator at the end
//this stores enough space for the full length of the array from envp[1][i] to
//envp[n][last char]
//
//to build each env variable which by default are strings, we must also allocate
//memory for each of them (remember, env variables follow a KEY=value design)
//
//this will be later passed to execve()
char	**copy_of_envp(t_shell *shell, char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		shell->env_array[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!shell->env_array[i])
			return (allocation_failed(envp, i), NULL);
		ft_strcpy(shell->env_array[i], envp[i]);
		i++;
	}
	shell->env_array[env_size(envp)] = NULL;
	return (shell->env_array);
}
