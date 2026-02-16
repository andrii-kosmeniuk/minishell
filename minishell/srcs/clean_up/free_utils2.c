/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:13:53 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 18:47:02 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->content);
		tokens->content = NULL;
		free(tokens);
		tokens = NULL;
		tokens = tmp;
	}
}

void	free_on_cmd_failure(t_shell *shell)
{
	free_tokens(shell->head);
	free_env_list(&shell->environment_p);
}

void	cleanup_shell(t_shell *shell)
{
	if (shell->head)
	{
		free_tokens(shell->head);
		shell->head = NULL;
	}
	free_env_list(&shell->environment_p);
	shell->environment_p = NULL;
	rl_clear_history();
}

void	cleanup_tokens(t_shell *shell)
{
	if (shell->head)
	{
		free_tokens(shell->head);
		shell->head = NULL;
	}
}
