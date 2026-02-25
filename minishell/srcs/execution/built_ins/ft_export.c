/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:45:25 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/25 14:45:27 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*export_parse_name(char *arg)
{
	char	*eq;
	char	*name;

	eq = ft_strchr(arg, '=');
	if (eq)
		name = ft_strndup(arg, eq - arg);
	else
		name = ft_strdup(arg);
	return (name);
}

static int	export_one(t_shell *shell, char *arg)
{
	char	*name;
	char	*eq;
	int		ok;

	name = export_parse_name(arg);
	if (!name)
		return (1);
	if (!env_is_valid_identifier(name))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(name);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (eq)
		ok = env_set(&shell->environment_p, name, eq + 1, true);
	else
		ok = env_set(&shell->environment_p, name, NULL, true);
	free(name);
	return (!ok);
}

int	ft_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	status;

	if (!cmd->args[1])
		return (export_print_sorted(shell));
	i = 1;
	status = 0;
	while (cmd->args[i])
	{
		if (export_one(shell, cmd->args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
