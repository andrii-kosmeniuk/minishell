/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:40:00 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/24 20:40:01 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../minishell.h"

char	*prompt(const char *input)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = readline(input);
		if (!line || (ft_strlen(line) == 0))
		{
			printf("shell has been killed💀\n");
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
	return (line);
}*/
