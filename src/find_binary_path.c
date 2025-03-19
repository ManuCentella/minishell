/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:55:15 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/17 22:55:48 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
