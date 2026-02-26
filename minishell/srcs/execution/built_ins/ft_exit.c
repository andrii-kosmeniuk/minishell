/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:26:52 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 22:17:23 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	exit_with_cleanup(t_shell *shell, pid_t *pids, long long code)
{
	cleanup_shell(shell);
	if (pids)
		free(pids);
	close_std_fds();
	exit((unsigned char)code);
}

static void	exit_numeric_error(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	ft_putstr_fd("minishell: exit ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[1], STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	shell->exit_status = 2;
	exit_with_cleanup(shell, pids, 2);
}

int	ft_exit(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	long long	code;

	code = 0;
	ft_putstr_fd("exit\n", 2);
	if (!cmd->args[1])
		code = shell->exit_status;
	else if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (!exit_is_numeric(cmd->args[1]))
		exit_numeric_error(cmd, shell, pids);
	else
		code = exit_parse_code(cmd->args[1]);
	exit_with_cleanup(shell, pids, code);
	return (0);
}
