/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:42:38 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 12:42:39 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_tolower(int ab)
{
	if (ab >= 'A' && ab <= 'Z')
	{
		ab += 32;
	}
	return (ab);
}
/*
int	main(void)
{
	char d = 'A';
	char e = 'a';
	char f = '!';

	printf("%c\n", ft_tolower(d));
	printf("%c\n", ft_tolower(e));
	printf("%c\n", ft_tolower(f));
	return 0;
}*/
