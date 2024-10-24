/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:52:18 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:38:43 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clean_empty_strings(char *str)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*ret;
	size_t	dstsize;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2]) || (str[0] == '"'
			&& str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'') || (str[i] == '"' && str[i
					+ 1] == '"'))
			i += 2;
		else
			tmp[j++] = str[i++];
	}
	free(str);
	dstsize = ft_strlen(tmp) + 1;
	ret = ft_calloc(dstsize, sizeof(char));
	return (ft_strlcpy(ret, tmp, dstsize), free(tmp), ret);
}

char	*ft_handle_dollar(t_minishell *minishell, char *str, size_t *i)
{
	size_t	start;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(minishell->exit_s));
	}
	else if (!ft_is_valid_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (ft_is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = ft_get_envlst_val(minishell, var);
	if (!env_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}

static char	*ft_cmd_pre_expander(t_minishell *minishell, char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoin_f(ret, ft_handle_squotes(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoin_f(ret, ft_handle_dquotes(minishell, str, &i));
		else if (str[i] == '$')
			ret = ft_strjoin_f(ret, ft_handle_dollar(minishell, str, &i));
		else
			ret = ft_strjoin_f(ret, ft_handle_normal_str(str, &i));
	}
	return (ret);
}

char	**ft_expand(t_minishell *minishell, char *str)
{
	char	**expanded;
	size_t	i;

	str = ft_cmd_pre_expander(minishell, str);
	if (!str)
		return (NULL);
	str = ft_clean_empty_strings(str);
	if (!str)
		return (NULL);
	expanded = ft_expander_split(str);
	free(str);
	if (!expanded)
		return (NULL);
	i = 0;
	while (expanded[i])
	{
		expanded[i] = ft_strip_quotes(expanded[i]);
		i++;
	}
	return (expanded);
}
