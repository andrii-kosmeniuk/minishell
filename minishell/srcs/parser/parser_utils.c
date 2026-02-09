/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:31:40 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/07 15:41:17 by milija-h         ###   ########.fr       */
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
	cmd->argc = 0;
	cmd->redirections = NULL;
	cmd->path = 
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

t_cmd	*add_args(t_cmd *cmd, t_token *token)
{
	char	**cmd_args;
	int		i;

	if (!cmd || !token || !token->content)
		return (NULL);
	cmd_args = ft_calloc((cmd->argc + 2), sizeof(char *));
	if (!cmd_args)
		return (NULL);
	i = 0;
	while (i < cmd->argc)
	{
		cmd_args[i] = cmd->args[i];
		i++;
	}
	cmd_args[i] = ft_strdup(token->content);
	if (!cmd_args[i])
		return (free(cmd_args), NULL);
	cmd_args[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = cmd_args;
	cmd->argc += 1;
	return (cmd);
}

bool	handle_pipe(t_cmd **current)
{
	(*current)->next = create_command();
	if (!(*current)->next)
		return (false);
	*current = (*current)->next;
	return (true);
}
