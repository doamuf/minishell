/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:41:55 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:41:58 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

static bool	ft_isnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ft_exittoi(t_minishell *minishell, char *s)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_get_sign(s, &i, &sign);
	if (!ft_isnum(s + i))
	{
		exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
		(ft_clean(minishell), exit(exit_s));
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > LONG_MAX)
		{
			exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
			(ft_clean(minishell), exit(exit_s));
		}
		i++;
	}
	return ((result * sign) % 256);
}

void	ft_exit(t_minishell *minishell, char **args)
{
	int	exit_s;

	exit_s = minishell->exit_s;
	if (args[1])
	{
		if (args[2] && ft_isnum(args[1]))
		{
			exit_s = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS,
					NULL});
			return ;
		}
		else
			exit_s = ft_exittoi(minishell, args[1]);
	}
	printf("exit");
	(ft_clean(minishell), exit(exit_s));
}
