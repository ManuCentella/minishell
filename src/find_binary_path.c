
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
char *find_binary_path(char *cmd, t_env *env)
{
    char **paths;
    char *binary_path;
    char *path_var;
    t_env *path_env;

    // 📌 Si el comando ya contiene `/`, lo probamos directamente
    if (ft_strchr(cmd, '/') != NULL)
    {
        if (access(cmd, X_OK) == 0) // 📌 Verifica si es ejecutable
            return (ft_strdup(cmd));
        return (NULL);
    }

    // 📌 Obtenemos la variable PATH correctamente
    path_env = get_env_var(env, "PATH");  // ✅ Usamos `get_env_var()`
    path_var = (path_env) ? path_env->value : NULL;  // ✅ Extraemos `value` si PATH existe

    // 📌 Debugging para verificar el valor real de PATH
    printf("[DEBUG] PATH actual en find_binary_path: %s\n", path_var);

    // 🔹 Si PATH no existe o está vacío, devolvemos NULL y mostramos error
    if (!path_var || ft_strlen(path_var) == 0)  
    {
        printf("minishell: %s: command not found\n", cmd);
        return (NULL);
    }

    // 📌 Separamos PATH en rutas y verificamos si es válido
    paths = ft_split(path_var, ':');
    if (!paths || !paths[0]) // ✅ Evitar problemas si PATH está vacío
    {
        printf("minishell: %s: command not found\n", cmd);
        return (NULL);
    }

    // 📌 Buscamos el comando en cada ruta
    binary_path = search_paths(paths, cmd);

    ft_free_split(paths);
    return (binary_path);
}

