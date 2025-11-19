/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:04:20 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/07 02:04:22 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		new ->next = *lst;
		*lst = new;
	}
}
/*
int	main(void)
{
	t_list *head = NULL;

	ft_lstadd_front(&head, ft_lstnew("node1"));
	ft_lstadd_front(&head, ft_lstnew("node2"));


	while (head)
	{
		printf("nodes : %s\n", (char *)head->content);
		head = head->next;
	}
	return (0);
}*/
