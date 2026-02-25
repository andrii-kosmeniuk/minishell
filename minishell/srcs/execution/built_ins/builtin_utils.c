/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:40:26 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/12 13:41:43 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static bool	is_echo_n_option(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] == '\0')
		return (false);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->args[i] && is_echo_n_option(cmd->args[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		return (0);
	}
	ft_putstr_fd("minishell: pwd: error retrieving current directory\n", 2);
	return (1);
}

int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd->args[i])
	{
		if (!env_is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			env_unset(&shell->environment_p, cmd->args[i]);
		i++;
	}
	return (status);
}
