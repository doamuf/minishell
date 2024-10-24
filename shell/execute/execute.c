/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:51:27 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:32:55 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_pipe_child(t_minishell *minishell,
								t_node *node,
								int pfds[2],
								t_ast_direction direction)
{
	int	status;

	if (direction == TD_LEFT)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (direction == TD_RIGHT)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	status = ft_exec_node(minishell, node, true);
	(ft_clean(minishell), exit(status));
}

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	ft_exec_pipeline(t_minishell *minishell, t_node *tree)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	g_lock = 0;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_child(minishell, tree->left, pfds, TD_LEFT);
	else
	{
		pid_r = fork();
		if (!pid_r)
			ft_exec_pipe_child(minishell, tree->right, pfds, TD_RIGHT);
		else
		{
			(close(pfds[0]), close(pfds[1]), waitpid(pid_l, &status, 0),
				waitpid(pid_r, &status, 0));
			g_lock = 1;
			return (ft_get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

int	ft_exec_node(t_minishell *minishell, t_node *tree, bool piped)
{
	if (!tree)
		return (1);
	if (tree->type == N_PIPE)
		return (ft_exec_pipeline(minishell, tree));
	else
		return (ft_exec_simple_cmd(minishell, tree, piped));
	return (ENO_GENERAL);
}
