/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:31:39 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/24 15:31:59 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*remove_quotes(char *str)
{
	char	*removed_quotes;
	char	quote;
	size_t	i;
	size_t	j;

	if (str[0] == '\'' || str[0] == '"')
		quote = str[0];
	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	removed_quotes = ft_calloc(i + 1, sizeof(char));
	if (!removed_quotes)
		return (NULL);
	j = 0;
	i = 1;
	while (str[i] && str[i] != quote)
		removed_quotes[j++] = str[i++];
	removed_quotes[j] = '\0';
	return (removed_quotes);
}

static t_redir	*create_here_doc(char *delimeter)
{
	t_redir	*redir;
	char	*eof;
	bool	has_quotes;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	has_quotes = (delimeter[0] == '\'' || delimeter[0] == '"');
	if (has_quotes)
	{
		eof = remove_quotes(delimeter);
		redir->expand_heredoc = false;
	}
	else
	{
		eof = ft_strdup(delimeter);
		redir->expand_heredoc = true;
	}
	if (!eof)
		return (free(redir), redir = NULL, NULL);
	redir->type = HERE_DOC;
	redir->target = eof;
	return (redir);
}

static t_redir	*create_redir(t_type type, char *target)
{
	t_redir	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->target = ft_strdup(target);
	if (!new_redir->target)
		return (free(new_redir), NULL);
	new_redir->next = NULL;
	return (new_redir);
}

t_redir	*add_redir(t_redir **head, t_type type, char *target)
{
	t_redir	*cur;
	t_redir	*redir;

	if (type == HERE_DOC)
		redir = create_here_doc(target);
	else
		redir = create_redir(type, target);
	if (!redir)
		return (NULL);
	if (*head == NULL)
	{
		*head = redir;
		return (redir);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = redir;
	return (redir);
}
