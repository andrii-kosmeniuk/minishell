/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:41:47 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/15 10:56:28 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value(t_env *env, char *variable_name)
{
	t_env	*cur;
	char	*value;

	cur = env;
	value = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, variable_name) == 0)
			return (ft_strdup(cur->value));
		cur = cur->next;
	}
	return (NULL);
}

char	*read_variable_name(char *input, char *start_of_variable)
{
	size_t	length;
	char	*variable_name;

	input = start_of_variable;
	if (!is_valid(*input))
		return (NULL);
	while (alpha_numeric_underscore(*input))
		input++;
	length = input - start_of_variable;
	variable_name = substring(input, start_of_variable, length);
	if (!variable_name)
		return (NULL);
	return (variable_name);
}

bool	append_char(char **buffer, size_t *len, char c)
{
	char	*new_buf;

	new_buf = ft_realloc(*buffer, *len, *len + 2);
	if (!new_buf)
		return (false);
	*buffer = new_buf;
	(*buffer)[*len] = c;
	(*buffer)[*len + 1] = '\0';
	(*len)++;
	return (true);
}

bool	append_string(char **buffer, size_t *len, char *str)
{
	char	*new_buf;
	size_t	str_len;

	if (!str)
		return (true);
	str_len = ft_strlen(str);
	new_buf = ft_realloc(*buffer, *len, *len + str_len + 1);
	if (!new_buf)
		return (false);
	*buffer = new_buf;
	ft_memcpy(*buffer + *len, str, str_len);
	*len += str_len;
	(*buffer)[*len] = '\0';
	return (true);
}
