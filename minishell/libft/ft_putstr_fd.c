/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:06:13 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/26 20:06:15 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
/*
int	main(void)
{
	char	*s = "Hellooooooooooooooooooooosphvuhuhsoh8ih\n";
	ft_putstr_fd(s, 1);
	return (0);
}*/
