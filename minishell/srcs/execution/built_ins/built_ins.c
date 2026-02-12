/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:12:18 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/12 13:38:38 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_builtin(char *cmd)
{
	int			i;
	static char	**builtins;

	builtins = (char *[]){"", "echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	handle_builtin(t_cmd *cmd, t_shell *shell)
{
	if (cmd->type == ECHO)
		ft_echo(cmd);
	else if (cmd->type == CD)
		ft_cd(cmd, shell);
	else if (cmd->type == PWD)
		ft_pwd();
	else if (cmd->type == EXPORT)
		ft_export(cmd);
	else if (cmd->type == UNSET)
		ft_unset(cmd);
	else if (cmd->type == ENV)
		ft_env(shell);
	else if (cmd->type == EXIT)
		ft_exit(cmd);
}
