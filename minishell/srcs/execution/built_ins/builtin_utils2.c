/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:41:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 13:57:21 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_env(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	**envp;

	if (cmd->args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("' : No such file or directory\n", 2);
		return (127);
	}
	envp = list_to_envp(shell);
	if (!envp)
		return (1);
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		++i;
	}
	free_array(envp);
	return (0);
}
