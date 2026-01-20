/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:53:50 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/17 18:37:34 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// redirections not shown in shell
static bool	handle_redirection(t_cmd *current, t_token **token)
{
	if (!token || !*token || !current)
		return (false);
	if (!(*token)->next || !(*token)->next->content)
		return (false);
	if (!add_redir(&current->redirections, (*token)->type,
			(*token)->next->content))
		return (false);
	*token = (*token)->next;
	return (true);
}
t_cmd	*parse(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*t_oken;

	if ((!shell || !tokens) || (!syntax_check(shell)))
		return (NULL);
	head = create_command();
	if (!head)
		return (NULL);
	current = head;
	t_oken = tokens;
	while (t_oken)
	{
		if (t_oken->type == R_INPUT || t_oken->type == R_OUTPUT
			|| t_oken->type == R_APPEND || t_oken->type == HERE_DOC)
		{
			if (!handle_redirection(current, &t_oken))
				return (free_command(head), NULL);
		}
		else if (t_oken->type == 8 || t_oken->type == 0 || t_oken->type == 1)
		{
			if (!add_args(current, t_oken))
				return (free_command(head), NULL);
		}
		else if (t_oken->type == PIPE)
		{
			if (!handle_pipe(&current))
				return (free_command(head), NULL);
		}
		t_oken = t_oken->next;
	}
	return (head);
}
