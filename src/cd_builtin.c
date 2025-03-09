/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:27:37 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 12:30:19 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_env(t_data *data)
{
	(void)data; // Marca el parámetro como usado para evitar la advertencia
				// Implementación de upd_env
}

// ✅ Corrige `update_var()` para actualizar correctamente `PWD` y `OLDPWD`
static void	set_env_value(t_data *data, const char *key, const char *value)
{
	t_env	*var;

	var = get_env_var(data->env, key);
	if (!var)
		return ;
	free(var->value);
	var->value = ft_strdup(value);
	upd_env(data);
}

static void	update_var(t_data *data)
{
	char	*new_cwd;

	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
	{
		ft_putendl_fd("cd: error retrieving current directory", 2);
		return ;
	}
	set_env_value(data, "OLDPWD", data->cwd);
	set_env_value(data, "PWD", new_cwd);
	free(data->cwd);
	data->cwd = ft_strdup(new_cwd);
	free(new_cwd);
}

// ✅ `cd_home()` no cambia de directorio si `HOME` no está definido
static int	cd_home(t_data *data, char *home)
{
	(void)data; // Evita la advertencia de parámetro no usado
	if (home)
	{
		if (chdir(home) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(home, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		return (0);
	}
	ft_putendl_fd("cd: HOME not set", 2);
	return (1);
}

// ✅ Maneja el fallo de `getcwd()`
static int	handle_cwd_fail(t_data *data)
{
	if (chdir("/") == -1)
		return (1);
	free(data->cwd);
	data->cwd = ft_strdup("/");
	update_var(data);
	return (0);
}

// ✅ `cd_path()` maneja correctamente errores en `getcwd()`
static int	cd_path(t_data *data, char *path, char *home)
{
	char	*cwd;

	if (!path)
		return (cd_home(data, home));
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (handle_cwd_fail(data));
	free(cwd);
	return (0);
}

static int	cd_oldpwd(t_data *data)
{
	t_env	*oldpwd;

	oldpwd = get_env_var(data->env, "OLDPWD");
	if (!oldpwd || !oldpwd->value)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	ft_putendl_fd(oldpwd->value, 1);
	return (cd_path(data, oldpwd->value, NULL));
}

int	cd_builtin(t_data *data, t_cmd *cmd)
{
	t_env	*home;
	int		exit_;

	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
		return (cd_oldpwd(data));
	if (cmd->args[1] && cmd->args[1][0] == '-')
		return (print_msg(data, "cd: invalid option", -1), 1);
	if (cmd->args[1] && cmd->args[2])
		return (print_msg(data, "cd: too many arguments", -1), 1);
	home = get_env_var(data->env, "HOME");
	if (home)
    	exit_ = cd_path(data, cmd->args[1], home->value);
	else
    	exit_ = cd_path(data, cmd->args[1], NULL);
	update_var(data);
	return (exit_);
}

