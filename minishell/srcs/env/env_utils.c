/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:14:16 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 22:40:18 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	calculate_new_shlvl(t_shell *shell)
{
	t_env	*cur_variable;
	int		current_value;
	int		new_value;

	cur_variable = shell->environment_p;
	current_value = 1;
	while (cur_variable)
	{
		if (ft_strcmp(cur_variable->key, "SHLVL") == 0)
		{
			if (cur_variable->value)
			{
				current_value += ft_atoi(cur_variable->value);
				if (current_value <= 0 || current_value >= 1000)
					return (1);
				new_value = current_value;
				return (new_value);
			}
		}
		cur_variable = cur_variable->next;
	}
	return (0);
}

static int	update_env_value(t_env *variable, char *new_value_string)
{
	free(variable->value);
	variable->value = NULL;
	variable->value = ft_strdup(new_value_string);
	if (!variable->value)
		return (0);
	return (1);
}

int	update_shlvl_key(t_shell *shell, t_data *data)
{
	int		new_value;
	char	*new_value_string;
	t_env	*cur_variable;
	int		result;

	new_value = calculate_new_shlvl(shell);
	if (new_value == 0)
		return (0);
	data->shlvl = new_value;
	new_value_string = ft_itoa(new_value);
	if (!new_value_string)
		return (data->shlvl = 0, 0);
	cur_variable = shell->environment_p;
	while (cur_variable)
	{
		if (ft_strcmp(cur_variable->key, "SHLVL") == 0)
		{
			result = update_env_value(cur_variable, new_value_string);
			return (free(new_value_string), result);
		}
		cur_variable = cur_variable->next;
	}
	free(new_value_string);
	return (0);
}

int	env_print_exported(t_shell *shell)
{
	t_env	*cur;

	cur = shell->environment_p;
	while (cur)
	{
		if (cur->exported)
		{
			ft_putstr_fd(cur->key, 1);
			write(1, "=", 1);
			if (cur->value)
				ft_putstr_fd(cur->value, 1);
			write(1, "\n", 1);
		}
		cur = cur->next;
	}
	return (0);
}

void	print_escaped_value(char *value)
{
	write(1, "\"", 1);
	while (*value)
	{
		if (*value == '\\' || *value == '"')
			write(1, "\\", 1);
		write(1, value, 1);
		value++;
	}
	write(1, "\"", 1);
}
