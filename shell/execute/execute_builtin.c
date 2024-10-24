/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:42:32 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:42:35 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(t_minishell *minishell, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(minishell, args[1]));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(minishell));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(minishell, args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(minishell, args));
	ft_exit(minishell, args);
	return (ENO_GENERAL);
}

bool	ft_is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd") || !ft_strcmp(arg,
			"exit") || !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env"))
		return (true);
	return (false);
}
