/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:37:44 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/10 18:37:59 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_command(t_cmd *cmds)
{
	t_cmd	*cur;

	while (cmds)
	{
		cur = cmds->next;
		free_array(cmds->args);
		free(cmds->redirections);
		free(cmds);
		cmds = cur;
	}
}

t_cmd	*get_last_command(t_cmd *cmd_list)
{
	t_cmd	*cur;

	cur = cmd_list;
	while (cur)
		cur = cur->next;
	return (cur);
}

