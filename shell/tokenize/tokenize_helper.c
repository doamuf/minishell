/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:55:47 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:42:43 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_identifier(t_minishell *minishell, char **line_ptr,
		t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !ft_is_separator(tmp_line + i))
	{
		if (ft_is_quote(tmp_line[i]))
		{
			if (!ft_skip_quotes(tmp_line, &i))
				return (ft_print_quote_err(minishell, tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = ft_new_token(value, T_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	*line_ptr += i;
	return (ft_token_list_add_back(token_list, token), 1);
}

int	ft_append_separator(t_token_type type, char **line_ptr,
		t_token **token_list)
{
	t_token	*token;

	token = ft_new_token(NULL, type);
	if (!token)
		return (0);
	ft_token_list_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT)
		(*line_ptr)++;
	return (1);
}

int	ft_handle_separator(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (ft_append_separator(T_DLESS, line_ptr, token_list));
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (ft_append_separator(T_DGREAT, line_ptr, token_list));
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (ft_append_separator(T_LESS, line_ptr, token_list));
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (ft_append_separator(T_GREAT, line_ptr, token_list));
	else if (!ft_strncmp(*line_ptr, "(", 1))
		return (ft_append_separator(T_O_PARENT, line_ptr, token_list));
	else if (!ft_strncmp(*line_ptr, ")", 1))
		return (ft_append_separator(T_C_PARENT, line_ptr, token_list));
	else
		return (ft_append_separator(T_PIPE, line_ptr, token_list));
}

t_token	*ft_tokenize_helper(t_minishell *minishell, char *line)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
			return (ft_clear_token_list(&token_list), NULL);
		if (ft_isspace(*line))
			ft_skip_spaces(&line);
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "(", 1)
			|| !ft_strncmp(line, ")", 1))
			error = (!ft_handle_separator(&line, &token_list));
		else
			error = (!ft_append_identifier(minishell, &line, &token_list));
	}
	return (token_list);
}
