/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:59:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 12:59:28 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isdigit(int b)
{
	if (b >= '0' && b <= '9')
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
    char digit = 'a';  
    int	result = ft_isdigit(digit);
    printf("%d\n", result);

    digit = '5';  
    result = ft_isdigit(digit);
    printf("%d\n", result);

    return 0;
}*/
