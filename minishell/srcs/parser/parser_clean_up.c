/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:37:44 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 22:13:21 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_redir(t_redir *redir)
{
	t_redir	*cur;

	if (!redir)
		return ;
	while (redir)
	{
		cur = redir->next;
		free(redir->target);
		if (redir->type == HERE_DOC && redir->heredoc_fd >= 0)
			close(redir->heredoc_fd);
		free(redir);
		redir = cur;
	}
}

void	free_command(t_cmd **cmds)
{
	t_cmd	*cur;
	t_cmd	*temp;

	if (!*cmds)
		return ;
	temp = NULL;
	cur = *cmds;
	while (cur)
	{
		temp = cur->next;
		if (cur->args)
			free_array(cur->args);
		if (cur->path)
			free(cur->path);
		if (cur->redirections)
			free_redir(cur->redirections);
		free(cur);
		cur = temp;
	}
	*cmds = NULL;
}
