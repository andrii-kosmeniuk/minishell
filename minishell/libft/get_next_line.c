/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:10:34 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/09 08:53:23 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*print_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, i);
	line[i] = '\0';
	return (line);
}

char	*clean_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new = (char *)malloc(ft_strlen(stash + i) + 1);
	if (!new)
		return (free(stash), NULL);
	while (stash[i])
		new[j++] = stash[i++];
	new[j] = '\0';
	free(stash);
	return (new);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (free(s1), NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}

void	free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	t_var		p;

	stash = ft_edge_cases(fd, stash, &p.read_bytes);
	if (!stash)
		return (NULL);
	while (!ft_strchr(stash, '\n') && (p.read_bytes > 0))
	{
		p.read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (p.read_bytes > 0)
		{
			buffer[p.read_bytes] = '\0';
			stash = strjoin_free(stash, buffer);
			if (!stash)
				return (NULL);
		}
	}
	if (p.read_bytes == -1)
		return (free(stash), NULL);
	p.lines_returned = print_line(stash);
	stash = clean_stash(stash);
	stash = free_stash_if_line_null(stash, p.lines_returned);
	free_ptr((void **)&stash);
	return (p.lines_returned);
}

/*#include <stdio.h>
int	main(void)
{
	int	fd = 1; //open("test.txt", O_RDONLY);
	char	*result;
	if(fd < 0)
	{
		printf("Error Opening File!!\n");
		return (1);
	}
		else
		printf("File opened sucessfully!\n");
	while ((result = get_next_line(fd)) != NULL)
	{
		printf("%s", result);
		free(result);
	}
	close(fd);
	return (0);
}*/
