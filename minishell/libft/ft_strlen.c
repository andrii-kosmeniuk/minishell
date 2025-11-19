/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:27:32 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/28 17:41:44 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	const char *word = "Hello";
	const char *words = "Hello, World!";
	
	printf("%zu\n", ft_strlen(word));
	printf("%zu\n", ft_strlen(words));
	return 0;
}*/
