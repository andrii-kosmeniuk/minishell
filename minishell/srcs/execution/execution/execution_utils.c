/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:32:55 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 15:33:08 by milija-h         ###   ########.fr       */
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

int	check_file_access(char *path, int mode)
{
	return (access(path, mode) == 0);
}
