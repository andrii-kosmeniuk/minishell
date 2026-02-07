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

static bool	handle_redirection(t_cmd *current, t_token **token)
{
	if (!token || !*token || !current)
		return (false);
	if (!(*token)->next || !(*token)->next->content)
		return (false);
	if (!add_redir(*token, &current->redirections, (*token)->type,
			(*token)->next->content))
		return (false);
	*token = (*token)->next;
	return (true);
}

static bool	handle_token(t_cmd **current, t_token **token)
{
	if ((*token)->type == PIPE)
		return (handle_pipe(current));
	if ((*token)->type == R_INPUT || (*token)->type == R_OUTPUT
		|| (*token)->type == R_APPEND || (*token)->type == HERE_DOC)
		return (handle_redirection(*current, token));
	if ((*token)->type == 0 || (*token)->type == 1 || (*token)->type == 8)
	{
		if (!add_args(*current, *token))
			return (false);
	}
	return (true);
}

t_cmd	*parse(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*t_oken;

	if (!shell || !tokens)
		return (NULL);
	head = create_command();
	if (!head)
		return (NULL);
	current = head;
	t_oken = tokens;
	while (t_oken)
	{
		if (handle_token(&current, &t_oken) == false)
			return (free_command(head), NULL);
		t_oken = t_oken->next;
	}
	return (head);
}
