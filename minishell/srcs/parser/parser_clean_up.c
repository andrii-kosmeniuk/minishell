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

	cur = redir;
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

void	free_command(t_cmd *cmds)
{
	t_cmd	*cur;

	if (!cmds)
		return ;
	while (cmds)
	{
		cur = cmds->next;
		if (cmds->args)
			free_array(cmds->args);
		if (cmds->path)
			free(cmds->path);
		if (cmds->redirections)
			free_redir(cmds->redirections);
		free(cmds);
		cmds = cur;
	}
}
