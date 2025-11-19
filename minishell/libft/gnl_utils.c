/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:04:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/09 08:59:23 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_stash_if_line_null(char *stash, char *line)
{
	if (!line)
	{
		free(stash);
		stash = NULL;
	}
	return (stash);
}

void	*ft_edge_cases(int fd, char *stash, ssize_t *read_bytes)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	*read_bytes = 1;
	return (stash);
}
