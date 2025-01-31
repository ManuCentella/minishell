#include "minishell.h"
#include "minishell.h"

char **convert_env_to_array(t_env *env)
{
    int count = 0;
    t_env *tmp = env;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    char **env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;

    int i = 0;
    while (env)
    {
        env_array[i] = ft_strjoin(env->variable, "=");
        env_array[i] = ft_strjoin_free(env_array[i], env->value, 1);
        env = env->next;
        i++;
    }
    env_array[i] = NULL;
    return env_array;
}

char *find_binary_path(char *cmd, t_env *env)
{
    char **envp = convert_env_to_array(env);
    char *path_var = getenv("PATH");
    if (!path_var)
    {
        ft_free_split(envp);
        return NULL;
    }

    char **paths = ft_split(path_var, ':');
    int i = 0;
    while (paths[i])
    {
        char *binary_path = ft_strjoin(paths[i], "/");
        binary_path = ft_strjoin_free(binary_path, cmd, 1);
        if (access(binary_path, X_OK) == 0)
        {
            ft_free_split(paths);
            ft_free_split(envp);
            return binary_path;
        }
        free(binary_path);
        i++;
    }
    ft_free_split(paths);
    ft_free_split(envp);
    return NULL;
}