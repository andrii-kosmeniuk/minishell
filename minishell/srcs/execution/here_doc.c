/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:36:00 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/25 14:36:18 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	heredoc_tmp(char *delimiter, char **file_name, t_env *env, int exit)
{
	char	*line;
	char	*content;
	int		fd;

	fd = open_temp_file(file_name);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			return (close(fd), free(*file_name), -1);
		if (ft_strcmp(delimiter, line) == 0)
			return (free(line), close(fd), 0);
		content = here_doc_content(line, env, exit);
		free(line);
		if (!content)
			return (close(fd), free(*file_name), -1);
		write_to_file(fd, content);
		free(content);
	}
	return (-1);
}

static bool	open_heredoc_file(t_redir *redir, char *file_name)
{
	redir->heredoc_fd = open(file_name, O_RDONLY);
	unlink(file_name);
	free(file_name);
	return (redir->heredoc_fd >= 0);
}

static bool	here_doc(t_redir *redir, t_env *env, int exit)
{
	char	*file_name;

	file_name = NULL;
	if (heredoc_tmp(redir->target, &file_name, env, exit) < 0)
		return (false);
	return (open_heredoc_file(redir, file_name));
}

void	heredoc_append(t_redir *redir, t_env *env, int exit)
{
	if (redir->type == R_APPEND)
	{
		if (!handle_append(redir))
			return ;
	}
	if (redir->type == HERE_DOC)
	{
		if (!here_doc(redir, env, exit))
			return ;
	}
}
