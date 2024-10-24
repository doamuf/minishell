/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:55:39 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:00 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_next_token(t_minishell *minishell)
{
	minishell->curr_token = minishell->curr_token->next;
}

t_node	*ft_combine(t_minishell *minishell, t_node *left, t_node *right)
{
	t_node	*node;

	if (minishell->parse_err.type)
		return (NULL);
	node = ft_new_node(N_PIPE);
	if (!node)
		return (ft_set_parse_error(minishell, E_MEM), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*ft_term(t_minishell *minishell)
{
	t_node	*node;

	if (minishell->parse_err.type)
		return (NULL);
	if (ft_curr_token_is_binop(minishell)
		|| minishell->curr_token->type == T_C_PARENT)
		return (ft_set_parse_error(minishell, E_SYNTAX), NULL);
	else if (minishell->curr_token->type == T_O_PARENT)
	{
		ft_get_next_token(minishell);
		node = ft_expression(minishell);
		if (!node)
			return (ft_set_parse_error(minishell, E_MEM), NULL);
		if (!minishell->curr_token || minishell->curr_token->type != T_C_PARENT)
			return (ft_set_parse_error(minishell, E_SYNTAX), node);
		ft_get_next_token(minishell);
		return (node);
	}
	else
		return (ft_get_simple_cmd(minishell));
}

t_node	*ft_expression(t_minishell *minishell)
{
	t_node	*left;
	t_node	*right;

	if (minishell->parse_err.type || !minishell->curr_token)
		return (NULL);
	left = ft_term(minishell);
	if (!left)
		return (NULL);
	while (ft_curr_token_is_binop(minishell))
	{
		ft_get_next_token(minishell);
		if (!minishell->curr_token)
			return (ft_set_parse_error(minishell, E_SYNTAX), left);
		right = ft_expression(minishell);
		if (!right)
			return (left);
		left = ft_combine(minishell, left, right);
		if (!left)
			return (ft_clear_ast(minishell, &left),
				ft_clear_ast(minishell, &right), NULL);
	}
	return (left);
}

t_node	*ft_parse(t_minishell *minishell)
{
	t_node	*ast;

	minishell->curr_token = minishell->tokens;
	ast = ft_expression(minishell);
	if (minishell->curr_token)
		return (ft_set_parse_error(minishell, E_SYNTAX), ast);
	return (ast);
}
