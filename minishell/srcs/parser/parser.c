/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:53:50 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 22:03:47 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//maybe remove quotes if target has quotes

t_cmd	*parse(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*t_oken;
	t_redir	*redir;

	if ((!shell || !tokens) || (!syntax_check(shell)))
		return (NULL);
	head = create_command();
	current = head;
	t_oken = tokens;
	while (t_oken)
	{
		if (t_oken->type == WORD)
			add_args(current, t_oken);
		else if (t_oken->type == PIPE)
			handle_pipe(&current);
		else if (t_oken->type == R_INPUT || t_oken->type == R_OUTPUT
			|| t_oken->type == R_APPEND || t_oken->type == HERE_DOC)
		{
			if (!(redir = add_redir(&current->redirections, t_oken->type,
				t_oken->next->content)))
				return (NULL);
			t_oken->redir = redir;
		}
		t_oken = t_oken->next;
	}
	return (head);
}
