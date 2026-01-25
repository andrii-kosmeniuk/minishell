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

//static int	choose_file_name();

static char	*here_doc_content(char *delimeter, t_env *env, int exit)
{
	char	*buffer;
	char	*line;
	char	*content;
	size_t	prev_len;

	buffer = NULL;
	content = ft_calloc(1, sizeof(char));
	if (!content)
		return (printf("1\n"), NULL);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			return (free(buffer), free(content), NULL);
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		buffer = expand_string(line, env, exit);
		if (!buffer)
			return (free(buffer), free(line), NULL);
		if (content == NULL)
			prev_len = 0;
		else
			prev_len = ft_strlen(content);
		content = ft_realloc(content, prev_len, ft_strlen(buffer) + prev_len + 2);
		if (!content)
			return (free(line), free(buffer), NULL);
		ft_strcat(content, buffer);
		ft_strcat(content, "\n");
	}
	return (content);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell shell;
	t_data data;

	t_env *env = list_key_value(&shell, envp, &data);
	char	*hd = here_doc_content("eof", env, 0);
	printf("%s\n", hd);
	return 0;
}
