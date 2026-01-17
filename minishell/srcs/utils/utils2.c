/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:34:49 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/16 21:30:13 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_argument(t_token *token)
{
	if (token->type == WORD || token->type == EXPAND || token->type == S_QUOTE
		|| token->type == D_QUOTE)
		return (true);
	return (false);
}

bool	is_redirection(t_token *token)
{
	if (token->type == R_INPUT || token->type == R_OUTPUT
		|| token->type == R_APPEND || token->type == HERE_DOC)
		return (true);
	return (false);
}

static size_t	list_size(t_arg *arg)
{
	size_t	count;
	t_arg	*tmp;

	count = 0;
	tmp = arg;
	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		if (arg->type == R_INPUT || arg->type == R_OUTPUT
			|| arg->type == HERE_DOC || arg->type == R_APPEND)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (count);
}

char	**argument_array(t_arg *arg)
{
	char	**array;
	int		i;

	array = ft_calloc(list_size(arg) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (arg)
	{
		if (arg->type == R_INPUT || arg->type == R_OUTPUT
			|| arg->type == HERE_DOC || arg->type == R_APPEND)
		{
			arg = arg->next;
			if (arg)
				arg = arg->next;
			continue ;
		}
		if (arg->type == WORD)
			array[i++] = arg->value;
		arg = arg->next;
	}
	array[i] = NULL;
	return (array);
}

char	*substring(char *input, char *start_of_word, size_t len)
{
	char	*substr;

	if (!input || !start_of_word)
		return (NULL);
	if (len > ft_strlen(input))
		len = ft_strlen(start_of_word);
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, start_of_word, len);
	substr[len] = '\0';
	return (substr);
}
