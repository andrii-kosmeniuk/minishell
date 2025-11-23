/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:05:30 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/22 16:05:31 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
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
