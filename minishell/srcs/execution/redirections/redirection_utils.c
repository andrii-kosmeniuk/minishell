/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:07:46 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 16:09:14 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	output_redirections(t_redir *redir)
{
	int	fd;
	int	result;

	if (redir->type == R_OUTPUT)
	{
		fd = open_output_file(redir->target, false);
		if (fd < 0)
			return (0);
		result = safe_dup2(fd, STDOUT_FILENO);
		close(fd);
		return (result);
	}
	else if (redir->type == R_APPEND)
	{
		fd = open_output_file(redir->target, true);
		if (fd < 0)
			return (0);
		result = safe_dup2(fd, STDOUT_FILENO);
		close(fd);
		return (result);
	}
	return (0);
}

static int	input_redirections(t_redir *redir)
{
	int	fd;
	int	result;

	if (redir->type == R_INPUT)
	{
		fd = open_input_file(redir->target);
		if (fd < 0)
			return (0);
		result = safe_dup2(fd, STDIN_FILENO);
		close(fd);
		return (result);
	}
	return (0);
}

static bool	apply_single_redirection(t_redir *redir)
{
	int		result;

	while (redir)
	{
		if (redir->type == HERE_DOC)
			return (safe_dup2(redir->heredoc_fd, STDIN_FILENO));
		if (redir->type == R_OUTPUT || redir->type == R_APPEND)
			return (result = output_redirections(redir));
		if (redir->type == R_INPUT)
			return (result = input_redirections(redir));
		redir = redir->next;
	}
	return (false);
}

bool	apply_redirections(t_cmd *cmd)
{
	t_redir *cur;

	cur = cmd->redirections;
	while (cur)
	{
		if (!apply_single_redirection(cur))
			return (false);
		cur = cur->next;
	}
	return (true);
}
