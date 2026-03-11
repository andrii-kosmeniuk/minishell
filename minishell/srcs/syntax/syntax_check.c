/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:04:41 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/07 15:40:36 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	validate_pipe(t_token *token)
{
	if (!token)
		return (false);
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next)
				return (printf("%s", PIPE_END), false);
			if (token->next->type == PIPE)
				return (printf("%s", PIPE_END), false);
		}
		token = token->next;
	}
	return (true);
}

bool	syntax_check(t_shell *shell)
{
	t_token	*cur;
	t_token	*next;

	cur = shell->head;
	if (cur->type == PIPE)
		return (printf("%s", PIPE_END), false);
	while (cur)
	{
		next = cur->next;
		if (cur->type == PIPE)
			return (validate_pipe(cur));
		if ((cur->type == R_OUTPUT || cur->type == R_INPUT
				|| cur->type == HERE_DOC || cur->type == R_APPEND)
			&& (next && (next->type != WORD && next->type != D_QUOTE
					&& next->type != S_QUOTE)))
			return (printf("%s", REDIR_PIPE), false);
		if ((cur->type == R_INPUT || cur->type == R_OUTPUT
				|| cur->type == R_APPEND || cur->type == HERE_DOC)
			&& (next == NULL
				|| !(is_word_quoted(cur))))
			return (printf("%s", NO_TARGET), false);
		cur = next;
	}
	return (true);
}

bool	is_valid(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	return (false);
}
