/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:31:39 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/24 15:31:59 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_redir	*create_here_doc(t_token *tokens, char *delimeter)
{
	t_redir	*redir;
	char	*eof;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (tokens->next->type == D_QUOTE || tokens->next->type == S_QUOTE)
		redir->expand_heredoc = false;
	else
		redir->expand_heredoc = true;
	eof = ft_strdup(delimeter);
	if (!eof)
		return (free(redir), redir = NULL, NULL);
	redir->type = HERE_DOC;
	redir->target = eof;
	redir->heredoc_fd = -1;
	return (redir);
}

static t_redir	*create_redir(t_type type, char *target)
{
	t_redir	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->target = ft_strdup(target);
	if (!new_redir->target)
		return (free(new_redir), NULL);
	new_redir->next = NULL;
	return (new_redir);
}

t_redir	*add_redir(t_token *tokens, t_redir **head, t_type type, char *target)
{
	t_redir	*cur;
	t_redir	*redir;

	if (type == HERE_DOC)
		redir = create_here_doc(tokens, target);
	else
		redir = create_redir(type, target);
	if (!redir)
		return (NULL);
	if (*head == NULL)
	{
		*head = redir;
		return (redir);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = redir;
	return (redir);
}
