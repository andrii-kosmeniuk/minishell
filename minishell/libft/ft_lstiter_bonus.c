/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:09 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/08 18:07:11 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	ft_print_content(void *content)
{
	printf("printing: %s\n", (char *)content);
}*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
int	main(void)
{
	t_list *node1 = ft_lstnew(ft_strdup("hello"));
	t_list *node2 = ft_lstnew(ft_strdup("helloo"));
	t_list *node3 = ft_lstnew(ft_strdup("hellooo"));
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	ft_lstiter(node1, ft_print_content);
	return 0;
}*/
