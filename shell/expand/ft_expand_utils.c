/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:52:10 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:52:14 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*ft_handle_normal_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*ft_handle_dquote_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
	{
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_squotes(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dquotes(t_minishell *minishell, char *str, size_t *i)
{
	char	*ret;

	ret = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			ret = ft_strjoin_f(ret, ft_handle_dollar(minishell, str, i));
		else
			ret = ft_strjoin_f(ret, ft_handle_dquote_str(str, i));
	}
	(*i)++;
	return (ft_strjoin_f(ret, ft_strdup("\"")));
}
