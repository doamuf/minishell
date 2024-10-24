/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:41:44 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:59:59 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_envlst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_garbage_col(ft_strdup(key), false);
	if (value)
		new->value = ft_garbage_col(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

void	ft_envlst_back(t_minishell *minishell, t_env *new)
{
	t_env	*curr;

	if (!minishell->envlst)
	{
		minishell->envlst = new;
		return ;
	}
	curr = minishell->envlst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

void	ft_update_envlst(t_minishell *minishell,
						char *key,
						char *value,
						bool create)
{
	t_env	*envlst;

	envlst = minishell->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = ft_garbage_col(ft_strdup(value), false);
			return ;
		}
		envlst = envlst->next;
	}
	if (create)
		ft_envlst_back(minishell, ft_envlst_new(key, value));
}

char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_garbage_col(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_garbage_col(ft_substr(str, i, ft_strlen(str) - i),
					false));
		}
		i++;
	}
	return (NULL);
}
