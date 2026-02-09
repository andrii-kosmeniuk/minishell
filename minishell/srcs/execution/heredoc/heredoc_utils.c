/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:04:19 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/02 20:04:31 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	handle_append(t_redir *redir)
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

char	*choose_file_name(void)
{
	char		*file_name;
	char		*num;
	static int	i = 0;

	num = ft_itoa(i++);
	if (!num)
		return (NULL);
	file_name = ft_strjoin("heredoc_", num);
	if (!file_name)
		return (free(num), NULL);
	free(num);
	return (file_name);
}

int	open_temp_file(char **file_name)
{
	int	fd;

	*file_name = choose_file_name();
	if (!*file_name)
		return (-1);
	fd = open(*file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
	{
		free(*file_name);
		*file_name = NULL;
		return (ERROR_OPENING_FILE, -1);
	}
	return (fd);
}

void	write_to_file(int fd, char *content)
{
	write(fd, content, ft_strlen(content));
	write(fd, "\n", 1);
	free(content);
}

char	*expand_heredoc(t_redir *redir, t_env *env, char *line, int exit)
{
	char	*expanded_heredoc;
	size_t	len;

	len = 0;
	expanded_heredoc = NULL;
	if (redir->expand_heredoc == true)
	{
		expanded_heredoc = expand_string(line, env, exit);
		if (!expanded_heredoc)
			return (ERROR_EXPANDING_HEREDOC, NULL);
		return (expanded_heredoc);
	}
	while (*line)
	{
		if (!append_char(&expanded_heredoc, &len, *line))
			return (ERROR_EXPANDING_HEREDOC, NULL);
		line++;
	}
	return (expanded_heredoc);
}
