/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary_path_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:18 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/18 12:23:52 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_command_in_path(const char *base_path, const char *cmd)
{
	char	*binary_path;

	binary_path = ft_strjoin(base_path, "/");
	binary_path = ft_strjoin_free(binary_path, cmd, 1);
	if (access(binary_path, X_OK) == 0)
		return (binary_path);
	free(binary_path);
	return (NULL);
}

char	*search_paths(char **paths, char *cmd)
{
	int		i;
	char	*res;

	i = 0;
	while (paths[i])
	{
		res = check_command_in_path(paths[i], cmd);
		if (res)
			return (res);
		i++;
	}
	return (NULL);
}

char	*get_path_variable(t_env *env)
{
	t_env	*path_env;

	path_env = get_env_var(env, "PATH");
	if (path_env)
		return (path_env->value);
	else
		return (NULL);
}

char	*handle_absolute_or_relative_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) != 0)
		{
			errno = ENOENT;
			return (NULL);
		}
		if (access(cmd, X_OK) != 0)
		{
			errno = EACCES;
			return (ft_strdup(cmd));
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	**handle_empty_path(char *cmd, char *path_var)
{
	if (!path_var || ft_strlen(path_var) == 0)
	{
		printf("minishell: %s: command not found\n", cmd);
		return (NULL);
	}
	return (ft_split(path_var, ':'));
}
