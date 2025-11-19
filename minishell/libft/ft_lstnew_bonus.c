/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:52:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/07 00:52:31 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node ->content = content;
	new_node ->next = NULL;
	return (new_node);
}
/*
int	main(void)
{
	char	*str = "lkycnövno";
	t_list	*new_node;

	new_node = ft_lstnew((void *)str);
	if (new_node)
	{
		printf("Node created!\n");
		printf("%s\n", (char *)new_node->content);
	}
	else
		printf("failed creation");
	free(new_node);
	return (0);
}*/
