/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:16:19 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/27 17:16:21 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*static void	toupper__(unsigned int ch, char *c)
{
	(void)ch;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
int	main(void)
{
	char	s[100] = "HelloooAnd839!";
	printf("Before: %s\n", s);
	ft_striteri(s, toupper__);
	printf("After: %s\n", s);
	return 0;
}*/
