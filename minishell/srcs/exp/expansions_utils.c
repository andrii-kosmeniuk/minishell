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

size_t	calculate_expanded_size(char *input, t_env *env)
{
	size_t	size;
	char	*var_key;
	char	*value;

	size = 0;
	while (*input)
	{
		if (*input == '$' && is_valid(*(input + 1)))
		{
			var_key = read_variable_name(input, input + 1);
			if(!var_key)
				return (-1);
			value = get_value(env, var_key);
			if (!value)
			{
				size = 0;
				return (free(var_key), -1);
			}
			size += ft_strlen(value);
			input += 1 + ft_strlen(var_key);
			free(var_key);
		}
		else if (*input == '$' && *(input + 1) == '?')
		{
			size += 10;
			input += 2;
		}
		else
		{
			size++;
			input++;
		}
	}
	return (size + 1);
}
