/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:34:49 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/12 22:35:16 by milija-h         ###   ########.fr       */
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

static size_t	list_size(t_cmd *words)
{
	size_t	count;

	count = 0;
	while (words)
	{
		words = words->next;
		count += 1;
	}
	return (count);
}

char	**argument_array(t_cmd *cmd)
{
	char	**array;
	int		i;

	array = ft_calloc(list_size(cmd) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (cmd)
	{
		array[i] = ft_strdup(cmd->args->value);
		if (!array[i])
		{
			while (i > 0)
				free(array[--i]);
			return (free(array), NULL);
		}
		i++;
		cmd = cmd->next;
	}
	array[i] = NULL;
	return (array);
}
