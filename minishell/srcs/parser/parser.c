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

t_cmd	*parse(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_redir	*r;
	size_t	len;

	if (!shell || !tokens)
		return (NULL);
	if (!syntax_check(shell))
		return (NULL);
	head = create_command();
	current = head;
	while (tokens)
	{
		if (tokens->type == WORD)
			add_args(current, tokens);
		else if (tokens->type == PIPE)
			handle_pipe(&current);
		else if (tokens->type == R_INPUT || tokens->type == R_OUTPUT
			|| tokens->type == R_APPEND || tokens->type == HERE_DOC)
		{
			add_redir(&r, tokens->type, current->redirections->target, &len);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
