/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:21:59 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/10 17:22:00 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	custom_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	print_string(char *s)
{
	int	len;

	if (s == NULL)
		s = "(null)";
	len = custom_strlen(s);
	write(1, s, len);
	return (len);
}
/*
int	main(void)
{
	char	*s = NULL;
	printf("%s\n", s);
	print_string(s);
	return 0;
}*/
