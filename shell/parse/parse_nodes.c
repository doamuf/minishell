/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:55:28 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:55:30 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io_type	ft_get_io_type(t_token_type type)
{
	if (type == T_LESS)
		return (IO_IN);
	if (type == T_GREAT)
		return (IO_OUT);
	if (type == T_DLESS)
		return (IO_HEREDOC);
	return (IO_APPEND);
}

t_node	*ft_new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

t_io_node	*ft_new_io_node(t_token_type type, char *value)
{
	t_io_node	*new_node;

	new_node = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
	if (!new_node)
		return (NULL);
	new_node->type = ft_get_io_type(type);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node), NULL);
	return (new_node);
}

void	ft_append_io_node(t_io_node **lst, t_io_node *new)
{
	t_io_node	*curr_node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new;
}
