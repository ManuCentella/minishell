/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:18 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 21:09:02 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función auxiliar: une base_path + "/" + cmd y verifica si es ejecutable
static char	*check_command_in_path(const char *base_path, const char *cmd)
{
	char	*binary_path;

	binary_path = ft_strjoin(base_path, "/");
	binary_path = ft_strjoin_free(binary_path, cmd, 1);
	if (access(binary_path, X_OK) == 0)
		return (binary_path);
	free(binary_path);
	return (NULL);
}

// Función auxiliar: recorre cada path y llama a check_command_in_path
// Devuelve la ruta válida
static char	*search_paths(char **paths, char *cmd)
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

// Función auxiliar: obtiene la variable PATH del entorno
static char	*get_path_variable(t_env *env)
{
	t_env	*path_env;

	path_env = get_env_var(env, "PATH");
	return (path_env ? path_env->value : NULL);
}

// Función auxiliar: maneja el caso en el que el comando contiene '/'
static char	*handle_absolute_or_relative_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (access(cmd, X_OK) == 0 ? ft_strdup(cmd) : NULL);
	return (NULL);
}

// Función auxiliar: maneja el caso en el que la
// variable PATH no existe o está vacía
static char	**handle_empty_path(char *cmd, char *path_var)
{
	if (!path_var || ft_strlen(path_var) == 0)
	{
		printf("minishell: %s: command not found\n", cmd);
		return (NULL);
	}
	return (ft_split(path_var, ':'));
}

// Busca la ruta binaria de 'cmd' en el PATH
// Manejo de rutas absolutas o relativas
// Obtiene la variable PATH
// Maneja el caso en el que PATH no existe o está vacío
// Busca el comando en cada ruta
char	*find_binary_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*binary_path;
	char	*path_var;

	binary_path = handle_absolute_or_relative_path(cmd);
	if (binary_path != NULL)
		return (binary_path);
	path_var = get_path_variable(env);
	paths = handle_empty_path(cmd, path_var);
	if (!(paths))
		return (NULL);
	binary_path = search_paths(paths, cmd);
	ft_free_split(paths);
	return (binary_path);
}
