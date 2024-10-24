/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:17:39 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:17:44 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*curr;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	next = curr->next;
	while (curr && next)
	{
		del(curr->content);
		free(curr);
		curr = next;
		next = curr->next;
	}
	del(curr->content);
	free(curr);
	*lst = NULL;
}
