/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:31:40 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 21:20:40 by milija-h         ###   ########.fr       */
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
	t_arg	*temp;
	t_arg	*new;

	if (!cmd || !token || !token->content)
		return ;
	new = malloc(sizeof(t_arg));
	if (!new)
		return ;
	new->value = ft_strdup(token->content);
	if (!new->value)
		return (free(new));
	new->next = NULL;
	if (!cmd->args)
	{
		cmd->args = new;
	}
	else
	{
		temp = cmd->args;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	handle_pipe(t_cmd **current)
{
	(*current)->next = create_command();
	*current = (*current)->next;
}

t_redir	*add_redir(t_redir **head, t_type type, char *target)
{
	t_redir	*new_redir;
	t_redir	*cur;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->target = ft_strdup(target);
	if (!new_redir)
		return (free(new_redir), NULL);
	new_redir->next = NULL;
	if (*head == NULL)
	{
		*head = new_redir;
		return (new_redir);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_redir;
	return (new_redir);
}
