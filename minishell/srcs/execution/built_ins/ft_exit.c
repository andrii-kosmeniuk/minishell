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

#include "../../../minishell.h"

static int	exit_is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	exit_parse_code(char *s)
{
	long long	n;
	int			sign;
	int			i;

	n = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (sign * n);
}

int	ft_exit(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	long long	code;

	ft_putstr_fd("exit\n", 2);
	if (!cmd->args[1])
		code = shell->exit_status;
	else if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (!exit_is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		shell->exit_status = 2;
		cleanup_shell(shell);
		if (pids)
			free(pids);
		exit (2);
	}
	else
		code = exit_parse_code(cmd->args[1]);
	cleanup_shell(shell);
	if (pids)
		free(pids);
	exit((unsigned char)code);
}
