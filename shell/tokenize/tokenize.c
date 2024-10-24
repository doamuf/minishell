/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:56:08 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:56:10 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenize(t_minishell *minishell)
{
	char	*line;
	t_token	*token_list;

	line = minishell->line;
	token_list = ft_tokenize_helper(minishell, line);
	free(line);
	minishell->line = NULL;
	return (token_list);
}
