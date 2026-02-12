/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:41:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/12 13:42:08 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_env(t_shell *shell)
{
	int		i;
	char	**envp;

	envp = list_to_envp(shell);
	if (!envp)
		return (1);
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		++i;
	}
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}
