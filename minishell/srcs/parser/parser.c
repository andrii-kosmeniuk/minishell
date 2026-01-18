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
// quoted input not indentified

static bool	redirections(t_token *token)
{
	t_redir	*redir;

	if (token->type == R_INPUT || token->type == R_OUTPUT
		|| token->type == R_APPEND || token->type == HERE_DOC)
	{
		if (!token->next)
			return (false);
		redir = add_redir(&token->redir, token->type,
				token->next->content);
		if (!redir)
			return (false);
		token->redir = redir;
	}
	return (true);
}

t_cmd	*parse(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*t_oken;
	t_cmd	*arg;

	if ((!shell || !tokens) || (!syntax_check(shell)))
		return (NULL);
	head = create_command();
	current = head;
	t_oken = tokens;
	while (t_oken)
	{
		if (!redirections(t_oken))
			return (NULL);
		else if (t_oken->type == WORD)
		{
			arg = add_args(current, t_oken);
			if (!arg)
				return (NULL);
		}
		else if (t_oken->type == PIPE)
			handle_pipe(&current);
		t_oken = t_oken->next;
	}

	return (head);
}
