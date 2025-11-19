/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:03:37 by milija-h          #+#    #+#             */
/*   Updated: 2025/10/08 11:31:35 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	to_upper(unsigned int n, char c)
{

	if (n < 5 && c >= 'a' && c <= 'z')
			return('*');
	return (c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	if (s == NULL)
		return (NULL);
	new = (char *)malloc(ft_strlen(s) + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = (*f)(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*int	main(void)
{
	const char	*c = "suhdoiugigb7487hkbfl";
	char	*new = ft_strmapi(c, to_upper);
	printf("%s\n", new);
	free(new);
	return 0;
}*/
