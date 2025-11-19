/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:01:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/05 12:01:39 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t			total_bytes;
	size_t			i;
	void			*arr;
	unsigned char	*ptr;

	i = 0;
	if (num == 0 || size == 0)
		return (malloc(0));
	if (num > SIZE_MAX / size)
		return (NULL);
	total_bytes = num * size;
	arr = malloc(total_bytes);
	if (arr == NULL)
		return (NULL);
	ptr = (unsigned char *)arr;
	while (i < total_bytes)
	{
		ptr[i] = 0;
		i++;
	}
	return (arr);
}
/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	unsigned char *clloc = calloc(6, sizeof(unsigned char));
	if (clloc)
		strcpy((char *)clloc, "Hello");
	printf("%s\n", clloc);
	printf("%p\n", clloc);
	free(clloc);

	unsigned char	*ptr = ft_calloc(6, sizeof(unsigned char));
	if (ptr)
		strcpy((char *)ptr, "Hello");
	printf("%s\n", ptr);
	printf("%p\n", ptr);
	free(ptr);
	return 0;
}*/
