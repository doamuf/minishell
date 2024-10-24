/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:53:34 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:53:36 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean(t_minishell *minishell)
{
	t_env	*envlst;
	t_env	*envlst_tofree;

	envlst = minishell->envlst;
	while (envlst)
	{
		envlst_tofree = envlst;
		envlst = envlst->next;
		free(envlst_tofree);
	}
	minishell->envlst = NULL;
	ft_garbage_col(NULL, true);
	ft_clear_ast(minishell, &minishell->ast);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &minishell->original_term);
}
