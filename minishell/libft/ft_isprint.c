/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:52:41 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 12:52:43 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int e)
{
	if (e >= 32 && e <= 126)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char printable = 'd';
	char not_print = '\n';

	printf("%d\n", ft_isprint(printable));
	printf("%d\n", ft_isprint(not_print));
	return 0;
}*/
