/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:55:22 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:41:39 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_parse_error(t_minishell *minishell, t_parse_err_type type)
{
	minishell->parse_err.type = type;
}

void	ft_handle_parse_error(t_minishell *minishell)
{
	t_parse_err_type	type;
	t_token_type		token_type;
	char				**types;

	types = (char *[]){"T_IDENTIFIER", "<", ">", "<<",
		">>", "|", "(", ")", "newline"};
	type = minishell->parse_err.type;
	(void)token_type;
	(void)types;
	if (type)
	{
		if (type == E_SYNTAX)
		{
			if (!minishell->curr_token)
				token_type = T_NL;
			else
				token_type = minishell->curr_token->type;
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(types[token_type], 2);
			ft_putstr_fd("'\n", 2);
			minishell->exit_s = 258;
		}
		ft_clear_ast(minishell, &minishell->ast);
		ft_bzero(&minishell->parse_err, sizeof(t_parse_err));
	}
}
