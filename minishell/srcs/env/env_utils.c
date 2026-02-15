/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:14:16 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 15:56:46 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	calculate_new_shlvl(t_shell *shell)
{
	t_env	*cur_variable;
	int		current_value;
	int		new_value;

	cur_variable = shell->environment_p;
	new_value = 0;
	current_value = 1;
	while (cur_variable)
	{
		if (ft_strcmp(cur_variable->key, "SHLVL") == 0)
		{
			if (cur_variable->value)
			{
				current_value += ft_atoi(cur_variable->value);
				if (current_value <= 0 || current_value >= 1000)
				{
					new_value = 1;
					return (new_value);
				}
				new_value = current_value;
				return (new_value);
			}
		}
		cur_variable = cur_variable->next;
	}
	return (0);
}

int	update_shlvl_key(t_shell *shell, t_data *data)
{
	int		new_value;
	char	*new_value_string;
	t_env	*cur_variable;

	new_value = calculate_new_shlvl(shell);
	if (new_value == 0)
		return (1);
	data->shlvl = new_value;
	new_value_string = ft_itoa(new_value);
	if (!new_value_string)
		return (data->shlvl = 0, 0);
	cur_variable = shell->environment_p;
	while (cur_variable)
	{
		if (ft_strcmp(cur_variable->key, "SHLVL") == 0)
		{
			free(cur_variable->value);
			cur_variable->value = new_value_string;
			return (1);
		}
		cur_variable = cur_variable->next;
	}
	free(new_value_string);
	return (0);
}
