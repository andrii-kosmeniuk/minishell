/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:58:49 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 17:58:50 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
	return ;
}
/*
int	main(void)
{
	char	letters[100] = "cbglzsfkagzfzaflfzd";
	printf("before:%s\n", letters);
	ft_bzero(letters, 10);
	printf("after:%s\n", letters);
	return 0;
}*/
