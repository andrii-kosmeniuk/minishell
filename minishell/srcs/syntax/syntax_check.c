/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:04:41 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/20 15:18:13 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	syntax_check(t_shell *shell)
{
	t_token	*cur;
	t_token	*next;

	cur = shell->head;
	if (cur->type == PIPE)
		return (fprintf(stderr, PIPE_FIRST), false);
	while (cur)
	{
		next = cur->next;
		if (cur->type == PIPE && next == NULL)
			return (printf(PIPE_END), false);
		if ((cur->type == R_OUTPUT || cur->type == R_INPUT
				|| cur->type == HERE_DOC || cur->type == R_APPEND)
			&& (next && next->type == PIPE))
			return (printf(REDIR_PIPE), false);
		if ((cur->type == R_INPUT || cur->type == R_OUTPUT
				|| cur->type == R_APPEND || cur->type == HERE_DOC)
			&& (next == NULL
				|| !(is_word_quoted(cur))))
			return (printf(NO_TARGET), false);
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
