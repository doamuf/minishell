/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:51:51 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:51:56 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_lock = 2;
	exit(130);
}

void	ft_heredoc(t_minishell *minishell, t_io_node *io, int p[2])
{
	char	*line;
	char	*quotes;

	signal(SIGINT, ft_heredoc_sigint_handler);
	quotes = io->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(io->value, line))
			break ;
		if (!*quotes)
			ft_heredoc_expander(minishell, line, p[1]);
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
	}
	ft_clean(minishell);
	exit(0);
}

static bool	ft_leave_leaf(int p[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, ft_sigquit_handler);
	g_lock = 1;
	close(p[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}

static void	ft_init_leaf(t_minishell *minishell, t_node *node)
{
	t_io_node	*io;
	int			p[2];
	int			pid;

	if (node->args)
		node->expanded_args = ft_expand(minishell, node->args);
	io = node->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(p);
			g_lock = 0;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (pid == 0)
				ft_heredoc(minishell, io, p);
			if (ft_leave_leaf(p, &pid))
				return ;
			io->here_doc = p[0];
		}
		else
			io->expanded_value = ft_expand(minishell, io->value);
		io = io->next;
	}
}

void	ft_init_tree(t_minishell *minishell, t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_PIPE)
	{
		ft_init_tree(minishell, node->left);
		if (g_lock != 2)
			ft_init_tree(minishell, node->right);
	}
	else
		ft_init_leaf(minishell, node);
}
