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

bool	builtin_check(t_cmd *cmd)
{
	int			i;
	static char	**builtins;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);
	builtins = (char *[]){"", "echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
			return (cmd->b_type = i, true);
		i++;
	}
	return (false);
}

bool	is_builtin(t_cmd *cmd, t_shell *shell, t_env *env, pid_t *pids)
{
	int			i;
	static char	**builtins;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);
	builtins = (char *[]){"", "echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
			return (cmd->b_type = i, handle_builtin(cmd, shell, env,
					pids), true);
		i++;
	}
	return (false);
}

void	handle_builtin(t_cmd *cmd, t_shell *shell, t_env *env, pid_t *pids)
{
	if (cmd->b_type == ECHO)
		shell->exit_status = ft_echo(cmd);
	else if (cmd->b_type == CD)
		shell->exit_status = ft_cd(cmd, shell);
	else if (cmd->b_type == PWD)
		shell->exit_status = ft_pwd();
	else if (cmd->b_type == EXPORT)
		shell->exit_status = ft_export(cmd);
	else if (cmd->b_type == UNSET)
		shell->exit_status = ft_unset(cmd, env);
	else if (cmd->b_type == ENV)
		shell->exit_status = ft_env(shell);
	else if (cmd->b_type == EXIT)
		shell->exit_status = ft_exit(cmd, shell, pids);
	free(pids);
}
