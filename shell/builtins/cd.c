/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:14:51 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 14:14:54 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_home(t_minishell *minishell)
{
	char	*home;

	ft_update_envlst(minishell, "OLDPWD",
		ft_get_envlst_val(minishell, "PWD"), false);
	home = ft_get_envlst_val(minishell, "HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (ft_update_envlst(minishell, "PWD", home, false), 0);
	return (1);
}

static int	ft_change_pwd(t_minishell *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	return (ft_update_envlst(minishell, "PWD", cwd, false), 0);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(t_minishell *minishell, char *path)
{
	if (!path)
		return (ft_cd_home(minishell));
	if (chdir(path) != ENO_SUCCESS)
		return (ft_cd_err_msg(path));
	ft_update_envlst(minishell, "OLDPWD",
		ft_get_envlst_val(minishell, "PWD"), false);
	return (ft_change_pwd(minishell));
}
