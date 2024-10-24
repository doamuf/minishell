/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:56:14 by mabdelna          #+#    #+#             */
/*   Updated: 2024/10/02 12:59:12 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_minishell(t_minishell *minishell, char **env)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->environ = env;
	ft_init_envlst(minishell);
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell->original_term);
}

static void	ft_start_execution(t_minishell *minishell)
{
	signal(SIGQUIT, ft_sigquit_handler);
	ft_init_tree(minishell, minishell->ast);
	if (g_lock == 2)
	{
		ft_clear_ast(minishell, &minishell->ast);
		g_lock = 1;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &minishell->original_term);
	minishell->exit_s = ft_exec_node(minishell, minishell->ast, false);
	ft_clear_ast(minishell, &minishell->ast);
}

void	no_line(t_minishell *minishell)
{
	ft_clean(minishell);
	ft_putstr_fd("exit\n", 1);
	exit(minishell->exit_s);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	g_lock = 1;
	ft_init_minishell(&minishell, env);
	while (ac && av)
	{
		ft_init_signals(&minishell);
		minishell.line = readline(PROMPT);
		if (!minishell.line)
			no_line(&minishell);
		if (minishell.line[0])
			add_history(minishell.line);
		minishell.tokens = ft_tokenize(&minishell);
		if (!minishell.tokens)
			continue ;
		minishell.ast = ft_parse(&minishell);
		if (minishell.parse_err.type)
		{
			ft_handle_parse_error(&minishell);
			continue ;
		}
		ft_start_execution(&minishell);
	}
	return (ft_garbage_col(NULL, true), ft_clean(&minishell), minishell.exit_s);
}
