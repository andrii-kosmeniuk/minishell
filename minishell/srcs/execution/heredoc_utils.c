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

#include "../../minishell.h"

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
		return (-1);
	}
	return (fd);
}

void	write_to_file(int fd, char *content)
{
	write(fd, content, ft_strlen(content));
	write(fd, "\n", 1);
}

char	*here_doc_content(char *line, t_env *env, int exit)
{
	char	*buffer;
	char	*content;
	size_t	len;

	buffer = expand_string(line, env, exit);
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
