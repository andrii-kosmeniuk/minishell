/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:36:00 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/05 15:54:02 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*here_doc_content(t_shell *s, t_redir *redir, t_env *env,
								char *line)
{
	char	*buffer;
	char	*content;
	size_t	len;

	buffer = expand_heredoc(s, redir, env, line);
	if (!buffer)
		return (NULL);
	len = ft_strlen(buffer);
	content = malloc(len + 2);
	if (!content)
		return (free(buffer), NULL);
	ft_memcpy(content, buffer, len);
	content[len] = '\n';
	content[len + 1] = '\0';
	free(buffer);
	return (content);
}

static int	heredoc_tmp(t_shell *s, t_redir *redir, t_env *env,
						char **file_name)
{
	char	*line;
	char	*content;
	int		fd;

	fd = open_temp_file(file_name);
	if (fd < 0)
		return (-1);
	line = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (g_signal == 2)
			return (close(fd), free(line), g_signal = 0,
				unlink(*file_name), free(*file_name), -1);
		if (!line)
			return (close(fd), 0);
		if (ft_strcmp(redir->target, line) == 0)
			return (free(line), close(fd), 0);
		content = here_doc_content(s, redir, env, line);
		if (!content)
			return (free(line), close(fd), free(*file_name), -1);
		free(line);
		write_to_file(fd, content);
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

static bool	here_doc(t_shell *shell, t_redir *redir, t_env *env)
{
	char	*file_name;

	file_name = NULL;
	if (heredoc_tmp(shell, redir, env, &file_name) < 0)
		return (false);
	return (open_heredoc_file(redir, file_name));
}

bool	heredoc_append(t_shell *shell, t_redir *redir, t_env *env)
{
	if (redir->type == HERE_DOC)
	{
		if (!here_doc(shell, redir, env))
			return (false);
	}
	return (true);
}
