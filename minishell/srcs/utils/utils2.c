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

char	*substring(char *start_of_word, size_t len)
{
	char	*substr;

	if (!start_of_word)
		return (NULL);
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, start_of_word, len);
	substr[len] = '\0';
	return (substr);
}
