/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:20:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/19 02:54:04 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_append(int fd, t_redir *redir)
{
	if (!(fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0664)))
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return ;
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
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(str);
}

void	heredoc_append(t_redir	*redir)
{
	int		pipe_fd[2];
	char	*line;
	int		fd;

	if (!redir)
		return ;
	line = NULL;
	fd = 0;
	if (redir->type == R_APPEND)
		handle_append(fd, redir);
	else if (redir->type == HERE_DOC)
	{
		if (pipe(pipe_fd) < 0)
			return ;
		line = readline("heredoc>");
		if (!line)
			return ;
		while (ft_strcmp(line, redir->target) != 0)
		{
			line = readline("heredoc>");
			if (!line)
				return ;
			write_to_pipe(pipe_fd, line);
		}
		dup_close_pipes_free(pipe_fd, line);
	}
}
