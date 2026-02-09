/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:05:30 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 22:28:23 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	if (array)
	{
		free(array);
		array = NULL;
	}
}

void	allocation_failed(char **array, int last_allocated_string)
{
	int	i;

	i = 0;
	while (i < last_allocated_string)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_key_value(char *key, char *value)
{
	free(key);
	free(value);
}

void	free_all(t_token *tokens, t_shell *shell)
{
	t_token	*tmp_token;

	while (tokens)
	{
		tmp_token = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = tmp_token;
	}
	free_env_list(shell->environment_p);
}
