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
	if (fd < 0)
		return (false);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), false);
	close(fd);
	return (true);
}

static void	write_to_pipe(int fd[2], char *line)
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
}

static void	dup_close_pipes(int fd[2])
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		close(fd[0]);
		return ;
	}
	close(fd[0]);
}

static bool	here_doc(t_redir *redir, int pipe_fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			return (printf("\n"), false);
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		write_to_pipe(pipe_fd, line);
		free(line);
	}
	return (true);
}

void	heredoc_append(t_redir	*redir)
{
	int			pipe_fd[2];
	static int	backup = -1;

	if (redir->type == R_APPEND)
	{
		if (!handle_append(redir))
			return ;
		return ;
	}
	if (redir->type == HERE_DOC)
	{
		if (backup == -1)
			backup = dup(STDIN_FILENO);
		if (pipe(pipe_fd) < 0)
			return ;
		if (!here_doc(redir, pipe_fd))
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return ;
		}
		dup_close_pipes(pipe_fd);
	}
}
