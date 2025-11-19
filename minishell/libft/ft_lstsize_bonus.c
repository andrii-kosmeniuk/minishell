/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:34:36 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/07 13:34:37 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
int	main(void)
{
	t_list	*head = NULL;

	ft_lstadd_front(&head, ft_lstnew("node1"));
	ft_lstadd_front(&head, ft_lstnew("node2"));
	ft_lstadd_front(&head, ft_lstnew("node3"));
	ft_lstadd_front(&head, ft_lstnew("node4"));
	ft_lstadd_front(&head, ft_lstnew("node5"));
	ft_lstadd_front(&head, ft_lstnew("node6"));

	printf("length: %d\n", ft_lstsize(head));
	return (0);
}*/
