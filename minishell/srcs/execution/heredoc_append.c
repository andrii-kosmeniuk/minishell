/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:20:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/24 10:59:11 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	handle_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (!fd)
		return (false);
	if (!dup2(fd, STDOUT_FILENO))
		return (close(fd), false);
	close(fd);
	return (true);
}

static void	write_to_pipe(int fd[2], char *line)
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
}

static void	dup_close_pipes_free(int fd[2], char *str)
{
	(void)str;
	close(fd[1]);
	if (!dup2(fd[0], STDIN_FILENO))
		return ;
	close(fd[0]);
	free(str);
}

static bool	here_doc(char *line, t_redir *redir, int pipe[2])
{
	line = readline("heredoc>");
	if (!line)
		return (false);
	while (ft_strcmp(line, redir->target) != 0)
	{
		line = readline("heredoc>");
		if (!line)
			return (false);
		write_to_pipe(pipe, line);
	}
	return (true);
}

void	heredoc_append(t_redir	*redir)
{
	int			pipe_fd[2];
	char		*line;
	static int	backup = -1;

	line = NULL;
	if (redir->type == R_APPEND)
	{
		if (!handle_append(redir))
			return ;
	}
	if (backup == -1)
		backup = dup(STDIN_FILENO);
	else if (redir->type == HERE_DOC)
	{
		if (pipe(pipe_fd) < 0)
			return ;
		if (!dup2(backup, STDIN_FILENO))
			return ;
		if (!here_doc(line, redir, pipe_fd))
			return ;
		dup_close_pipes_free(pipe_fd, line);
	}
}
