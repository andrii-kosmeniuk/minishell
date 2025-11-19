/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:48:10 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/07 18:48:11 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp -> next;
	temp->next = new;
}
/*
int	main(void)
{
	t_list	*head = ft_lstnew("node-1");
	head ->next = ft_lstnew("node0");

	ft_lstadd_back(&head, ft_lstnew("node1"));
	ft_lstadd_back(&head, ft_lstnew("node2"));

	while (head)
	{
		printf("nodes : %s\n", (char *)head->content);
		head = head->next;
	}
	return (0);
}*/
