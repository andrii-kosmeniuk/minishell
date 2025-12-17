/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:20:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 23:20:29 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*For each command, for each redirection:

If redirection is HERE_DOC

Read from stdin until delimiter

Expand if delimiter not quoted

Write to temp file

Store fd in redirection struct

there can be here doc in rows
cat eof << eof << eof <<< eof
*/
static char	*here_doc_content(t_data *data, char *delimeter)
{
	int		i;
	char	*line;
	char	*here_doc_buffer;

	i = 0;
	while (i < 3)//data->number_of_heredocs)
	{
		line = readline("heredoc>");
		if (!line)
			return (NULL);
		here_doc_buffer = malloc(strlen(line));
		if (!here_doc_buffer)
			return (free(line), NULL);
		if (line == delimeter)
			break ;
		strcpy(here_doc_buffer, line);
		i++;
	}
	return (here_doc_buffer);
}

int main(void)
{
	t_token cmd; t_data data;

	char *result = here_doc_content(&data, "eof");
	if (!result)
		return (printf("error"), 1);
	printf("%s\n", result);
	return 0;
}
