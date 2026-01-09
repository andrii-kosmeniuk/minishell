/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:25:46 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/08 22:27:55 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_valid(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	return (false);
}

char *get_value(t_env *env, char *variable_name)
{
	t_env	*cur;
	char	*value;

	cur = env;
	value = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, variable_name) == 0)
		{
			value = ft_strdup(cur->value);
			if (!value)
			{
				value = ft_strdup("");
				if (!value)
					return (NULL);
			}
			return (value);
		}
		cur = cur->next;
	}
	return (ft_strdup(""));
}
