/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:37:49 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/08 16:37:52 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	del(void *content)
{
	free(content);
}*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*
int	main(void)
{
	t_list	*node1 = ft_lstnew(ft_strdup("node1"));
	t_list	*node2 = ft_lstnew(ft_strdup("node2"));
	t_list	*node3 = ft_lstnew(ft_strdup("node3"));
	t_list	*node4 = ft_lstnew(ft_strdup("node4"));
	node1 -> next = node2;
	node2 -> next = node3;
	node4 -> next = NULL;

	node1 ->next = NULL;

	ft_lstclear(&node2, del);
	printf("remaining node: %s\n", (char *)node1->content);
	return (0);
}*/
