/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_expander.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:52:44 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:52:46 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_expand_writer(t_minishell *minishell,
									char *str,
									size_t i,
									int fd)
{
	size_t	start;
	char	*tmp;

	start = i;
	if (str[i] == '?')
		return (ft_putnbr_fd(minishell->exit_s, fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = ft_garbage_col(ft_substr(str, start, i), false);
		tmp = ft_get_envlst_val(minishell, tmp);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
	return (i);
}

void	ft_heredoc_expander(t_minishell *minishell, char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			i += ft_heredoc_expand_writer(minishell, str, i, fd);
		}
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}
