/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:31:40 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/10 18:31:42 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd_back(t_cmd **head, t_cmd *new_command)
{
	t_cmd	*cur;

	if (!head || !new_command)
		return ;
	if (head == NULL)
	{
		*head = new_command;
		return ;
	}
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_command;
			
	}
}

void	add_redir(t_redir **head, t_type type, char *target, int *len)
{
	t_redir	*new_redir;
	t_redir	*cur;

	if (type == R_INPUT || R_OUTPUT)
		*len = 1;
	else if (type == HERE_DOC || R_APPEND)
		*len = 2;
	new_redir = ft_calloc(len, sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->target = ft_strdup(target);
	if (!new_redir)
		return (free(new_redir));
	new_redir->next = NULL;
	if (*head == NULL)
	{
		*head = new_redir;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new-redir;
}

bool	syntax_check(t_shell *shell, t_cmd *cmd)
{
	t_token	*cur;
	t_token	*next;

	cur = shell->head;
	if (cur->type == PIPE)
		return (fprintf(stderr, PIPE_FIRST), false);
	while (cur)
	{
		next = cur->next;
		if (cur->type == PIPE && next == NULL)
			return (fprintf(2, PIPE_END), false);
		if ((cur->type == R_OUTPUT || cur->type == R_INPUT
				|| cur->type == HERE_DOC || cur_type == R_APPEND)
			&& (next->type == PIPE))
			return (fprintf(stderr, REDIR_PIPE), false);
		if (cur->type == R_INPUT || cur->type == R_OUTPUT
			|| cur->type = R_APPEND || cur->type == HERE_DOC)
		{
			if (next == NULL || next->type != WORD)
				return (fprintf(stderror, NO_TARGET), false);
		}
		cur = next;
	}
	return (true);
}
