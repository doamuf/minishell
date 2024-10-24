/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:55:34 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 15:02:46 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_curr_token_is_binop(t_minishell *minishell)
{
	t_token_type	type;

	if (!minishell->curr_token)
		return (false);
	type = minishell->curr_token->type;
	if (type == T_PIPE)
		return (true);
	return (false);
}

bool	ft_is_redir(t_token_type type)
{
	if (type == T_LESS || type == T_GREAT || type == T_DLESS
		|| type == T_DGREAT)
		return (true);
	return (false);
}

bool	ft_get_io_list(t_minishell *minishell, t_io_node **io_list)
{
	t_token_type	redir_type;
	t_io_node		*tmp_io_node;

	if (minishell->parse_err.type)
		return (false);
	while (minishell->curr_token && ft_is_redir(minishell->curr_token->type))
	{
		redir_type = minishell->curr_token->type;
		ft_get_next_token(minishell);
		if (!minishell->curr_token)
			return (ft_set_parse_error(minishell, E_SYNTAX), false);
		if (minishell->curr_token->type != T_IDENTIFIER)
			return (ft_set_parse_error(minishell, E_SYNTAX), false);
		tmp_io_node = ft_new_io_node(redir_type, minishell->curr_token->value);
		if (!tmp_io_node)
			return (ft_set_parse_error(minishell, E_MEM), false);
		ft_append_io_node(io_list, tmp_io_node);
		ft_get_next_token(minishell);
	}
	return (true);
}

bool	ft_join_arguments(t_minishell *minishell, char **args)
{
	char	*to_free;

	if (minishell->parse_err.type)
		return (false);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (minishell->curr_token && minishell->curr_token->type == T_IDENTIFIER)
	{
		to_free = *args;
		*args = ft_strjoin_with(*args, minishell->curr_token->value, ' ');
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		ft_get_next_token(minishell);
	}
	return (true);
}

t_node	*ft_get_simple_cmd(t_minishell *minishell)
{
	t_node	*node;

	if (minishell->parse_err.type)
		return (NULL);
	node = ft_new_node(N_CMD);
	if (!node)
		return (ft_set_parse_error(minishell, E_MEM), NULL);
	while (minishell->curr_token && (minishell->curr_token->type == T_IDENTIFIER
			|| ft_is_redir(minishell->curr_token->type)))
	{
		if (minishell->curr_token->type == T_IDENTIFIER)
		{
			if (!ft_join_arguments(minishell, &(node->args)))
				return (ft_clear_cmd_node(node), ft_set_parse_error(minishell,
						E_MEM), NULL);
		}
		else if (ft_is_redir(minishell->curr_token->type))
		{
			if (!ft_get_io_list(minishell, &(node->io_list)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}
