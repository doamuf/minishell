/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:51:13 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:36:20 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redirection(t_node *node)
{
	t_io_node	*tmp_io;
	int			tmp_status;

	tmp_io = node->io_list;
	while (tmp_io)
	{
		if (tmp_io->type == IO_OUT && ft_out(tmp_io,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_IN && ft_in(tmp_io,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_APPEND && ft_append(tmp_io,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_HEREDOC)
			(dup2(tmp_io->here_doc, 0), close(tmp_io->here_doc));
		tmp_io = tmp_io->next;
	}
	return (ENO_SUCCESS);
}

void	ft_reset_stds(t_minishell *minishell, bool piped)
{
	if (piped)
		return ;
	dup2(minishell->stdin, 0);
	dup2(minishell->stdout, 1);
}

static int	ft_exec_child(t_minishell *minishell, t_node *node)
{
	t_path	path_status;
	int		tmp_status;
	int		fork_pid;

	g_lock = 0;
	fork_pid = fork();
	if (fork_pid == 0)
	{
		tmp_status = ft_check_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			(ft_clean(minishell), exit(ENO_GENERAL));
		path_status = ft_get_path(minishell, (node->expanded_args)[0]);
		if (path_status.err.no != ENO_SUCCESS)
		{
			tmp_status = ft_err_msg(path_status.err);
			(ft_clean(minishell), exit(tmp_status));
		}
		if ((execve(path_status.path, node->expanded_args, minishell->environ))
			== -1)
			(ft_clean(minishell), exit(1));
	}
	waitpid(fork_pid, &tmp_status, 0);
	g_lock = 1;
	return (ft_get_exit_status(tmp_status));
}

int	ft_exec_simple_cmd(t_minishell *minishell, t_node *node, bool piped)
{
	int	tmp_status;

	if (!node->expanded_args)
	{
		tmp_status = ft_check_redirection(node);
		return (ft_reset_stds(minishell, piped), (tmp_status && ENO_GENERAL));
	}
	else if (ft_is_builtin((node->expanded_args)[0]))
	{
		tmp_status = ft_check_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			return (ft_reset_stds(minishell, piped), ENO_GENERAL);
		tmp_status = ft_exec_builtin(minishell, node->expanded_args);
		return (ft_reset_stds(minishell, piped), tmp_status);
	}
	else
		return (ft_exec_child(minishell, node));
}
