/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:41:35 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:41:39 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_envlst(t_minishell *minishell)
{
	int		i;
	char	**environ;
	char	*key;
	char	*value;

	environ = minishell->environ;
	if (!environ)
		return ;
	i = 0;
	while (environ[i])
	{
		key = ft_extract_key(environ[i]);
		value = ft_extract_value(environ[i]);
		ft_update_envlst(minishell, key, value, true);
		i++;
	}
}

int	ft_env(t_minishell *minishell)
{
	t_env	*list;

	list = minishell->envlst;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (ENO_SUCCESS);
}

char	*ft_get_envlst_val(t_minishell *minishell, char *key)
{
	t_env	*envlst;

	envlst = minishell->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}
