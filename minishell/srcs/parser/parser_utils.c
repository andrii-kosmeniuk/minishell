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

void	add_args(t_cmd *cmd, t_token *token)
{
	t_token	*temp;

	token->next = NULL;
	if (!cmd->args)
		cmd->args = token;
	else
	{
		temp = cmd->args;
		while (temp->next)
			temp = temp->next;
		temp->next = token;
	}
}

void	handle_pipe(t_cmd **current)
{
	(*current)->next = create_command();
	*current = (*current)->next;
}

void	add_redir(t_redir **head, t_type type, char *target, size_t *len)
{
	t_redir	*new_redir;
	t_redir	*cur;

	if (type == R_INPUT || type == R_OUTPUT)
		*len = 1;
	else if (type == HERE_DOC || type == R_APPEND)
		*len = 2;
	new_redir = ft_calloc((size_t)len, sizeof(t_redir));
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
	cur->next = new_redir;
}
