/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:26:52 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/21 16:08:10 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_non_numeric(t_cmd *cmd, t_shell *shell, pid_t *pid)
{
	ft_putstr_fd("minishell: exit ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[1], STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	shell->exit_status = 2;
	cleanup_shell(shell);
	if (pid)
		free(pid);
	exit (2);
}

int	ft_exit(t_cmd *cmd, t_shell *shell, pid_t *pid)
{
	long long	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->argc == 1)
	{
		shell->exit_status = 0;
		cleanup_shell(shell);
		exit(0);
	}
	if (!ft_isnumeric(cmd->args[1]))
		exit_non_numeric(cmd, shell, pid);
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	exit_code = ft_atoll(cmd->args[1]);
	exit_code = ((exit_code % 256) + 256) % 256;
	shell->exit_status = (int)exit_code;
	cleanup_shell(shell);
	if (pid)
		free(pid);
	exit((int)exit_code);
}
