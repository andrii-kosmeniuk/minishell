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
