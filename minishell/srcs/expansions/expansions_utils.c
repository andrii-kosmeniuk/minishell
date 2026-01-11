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

char	*get_value(t_env *env, char *variable_name)
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

static int	alpha_numeric_underscore(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || (c == '_'))
		return (1);
	else
		return (0);
}

void	append_char(char *dest, char c)
{
	size_t	len;

	len = ft_strlen(dest);
	dest[len] = c;
	dest[len + 1] = '\0';
}

char	*read_variable_name(char *input, char *start_of_variable)
{
	int		length;
	char	*variable_name;

	input = start_of_variable;
	if (!is_valid(*input))
		return (NULL);
	while (alpha_numeric_underscore(*input)
		input++;
	length = input - start_of_variable;
	variable_name = ft_substr(input, start_of_variable, length);
	if (!variable_name)
		return (NULL);
	return (variable_name);
}
