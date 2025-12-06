/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:20:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/27 18:20:28 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env_list(t_env *head)
{
	while (head)
	{
		if (head->value)
		{
			printf("KEY=\"%s\" VALUE=\"%s\"\n", head->key,
				head->value);
		}
		else
		{
			printf("KEY=\"%s\" VALUE=\"%s\"\n", head->key,
				"NULL");
		}
		head = head->next;
	}
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		if (token->content)
		{
			printf("the token is: %s\nits state is: %d\nits type is: %d\n",
				token->content, token->state, token->type);
		}
		else
			printf("Error building token\n");
		token = token->next;
	}
}

void	print_num_of_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		tokens = tokens->next;
		i++;
	}
	printf("The number of tokens is: %d\n", i);
}
