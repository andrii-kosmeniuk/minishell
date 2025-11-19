/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:27:01 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/07 16:27:02 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL && lst -> next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
/*
int	main(void)
{
	t_list *node1 = ft_lstnew("node1");
	t_list *node2 = ft_lstnew("node2");
	t_list *node3 = ft_lstnew("node3");
	t_list *node4 = ft_lstnew("node4");
	t_list *node5 = ft_lstnew("node5");

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;

	t_list *last = ft_lstlast(node1);
	if (last != NULL)
	{
		printf("last node: %s\n", (char *)last->content);
	}
	return (0);
}*/	
