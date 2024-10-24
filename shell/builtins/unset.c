/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:42:20 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:31:27 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_helper(t_minishell *minishell, char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = minishell->envlst;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			if (prev)
				prev->next = current->next;
			else
				minishell->envlst = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_check_unset_key(char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str)
	{
		if (*str == '=' || (!ft_isalnum(*str) && *str != '_'))
			return (0);
		str++;
	}
	return (1);
}

int	ft_unset(t_minishell *minishell, char **args)
{
	int		i;
	bool	err;

	i = 1;
	if (!args[1])
		return (0);
	err = false;
	while (args[i])
	{
		if (!ft_check_unset_key(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = true;
		}
		else
			ft_unset_helper(minishell, ft_garbage_col(ft_extract_key(args[i]),
					false));
		i++;
	}
	return (err);
}
