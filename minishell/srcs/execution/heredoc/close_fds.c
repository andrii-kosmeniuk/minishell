/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:15:43 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/10 14:20:17 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	close_heredoc_fds(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == HERE_DOC && redir->heredoc_fd >= 0)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}

void	unlink_files(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == HERE_DOC && redir->target != NULL)
		{
			unlink(redir->target);
			free(redir->target);
			redir->target = NULL;
		}
		redir = redir->next;
	}
}

void	command_cleanup(t_cmd *cmd)
{
	close_heredoc_fds(cmd);
	unlink_files(cmd);
}
