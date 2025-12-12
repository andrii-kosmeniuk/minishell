/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:53:50 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/09 12:54:13 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//maybe remove quotes if target has quotes
void	pipe_handler(t_shell *shell)
{
	t_token	*cur;
	t_token	*next;
	t_redir	*redir;
	int		len;

	cur = shell->head;
	while (cur)
	{
		next = cur->next;
		if (cur->type == R_APPEND || cur->type == R_INPUT
			|| cur->type == R_OUTPUT || cur->type == HERE_DOC)
		{
				if (next->type != WORD)
					return (fprintf(stderr, NO_TARGET));
		}
		add_redir(&redir, cur->type, next->content, &len);

	}
}
