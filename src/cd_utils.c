/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:34:20 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/17 23:17:46 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_value(t_data *data, const char *key, const char *value)
{
	t_env	*var;

	var = get_env_var(data->env, key);
	if (!var)
		return ;
	free(var->value);
	var->value = ft_strdup(value);
}

void	update_var(t_data *data)
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

int	handle_cwd_fail(t_data *data)
{
	if (chdir("/") == -1)
		return (1);
	free(data->cwd);
	data->cwd = ft_strdup("/");
	update_var(data);
	return (0);
}
