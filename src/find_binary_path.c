
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
static char	*search_paths(char **paths, char *cmd)
{
	int		i;
	char	*res;

	i = 0;
	while (paths[i])
	{
		res = check_command_in_path(paths[i], cmd);
		if (res)
			return (res); // Devuelve la ruta válida
		i++;
	}
	return (NULL);
}

// Busca la ruta binaria de 'cmd' en el PATH
char	*find_binary_path(char *cmd, t_env *env)
{
	char	**envp;
	char	*path_var;
	char	**paths;
	char	*binary_path;

	envp = convert_env_to_array(env);
	path_var = getenv("PATH");
	if (!path_var)
	{
		ft_free_split(envp);
		return (NULL);
	}
	paths = ft_split(path_var, ':');
	binary_path = search_paths(paths, cmd);
	if (!binary_path)
	{
		ft_free_split(paths);
		ft_free_split(envp);
		return (NULL);
	}
	ft_free_split(paths);
	ft_free_split(envp);
	return (binary_path);
}
