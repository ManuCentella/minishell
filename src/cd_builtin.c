#include "minishell.h"

// Función para actualizar las variables PWD y OLDPWD
static void set_env_value(t_data *data, const char *key, const char *value)
{
    t_env *var;

    var = get_env_var(data->env, key);
    if (!var)
        return ;
    free(var->value);
    var->value = ft_strdup(value);
}

// Función para actualizar el directorio actual (PWD y OLDPWD)
static void update_var(t_data *data)
{
    char *new_cwd;

    new_cwd = getcwd(NULL, 0);
    if (!new_cwd)
    {
        ft_putendl_fd("cd: error retrieving current directory", 2);
        return ;
    }
    // Actualizamos OLDPWD y PWD
    set_env_value(data, "OLDPWD", data->cwd);  // Guardamos el viejo PWD
    set_env_value(data, "PWD", new_cwd);       // Actualizamos el nuevo PWD

    // Actualizamos el directorio en la estructura
    free(data->cwd);
    data->cwd = ft_strdup(new_cwd);  // Guardamos el nuevo directorio

    free(new_cwd);
}

// Cambiar al directorio HOME, si está definido
static int cd_home(t_data *data, char *home)
{
    if (home)
    {
        if (chdir(home) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(home, 2);
            ft_putendl_fd(": No such file or directory", 2);
            return (1);
        }
        update_var(data);  // Llamamos a update_var para actualizar PWD y OLDPWD
        return (0);
    }
    ft_putendl_fd("cd: HOME not set", 2);
    return (1);
}

// Manejo de fallo en la obtención del directorio actual
static int handle_cwd_fail(t_data *data)
{
    if (chdir("/") == -1)
        return (1);
    free(data->cwd);
    data->cwd = ft_strdup("/");
    update_var(data);  // Actualizamos PWD y OLDPWD
    return (0);
}

// Cambiar al directorio especificado en 'path'
static int cd_path(t_data *data, char *path, char *home)
{
    char *cwd;

    if (!path)  // Si el path es NULL, cambiamos al directorio HOME
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
    update_var(data);  // Actualizamos PWD y OLDPWD
    return (0);
}

// Cambiar al directorio anterior (OLD)
// Función para cambiar al directorio anterior
static int cd_oldpwd(t_data *data)
{
    t_env *oldpwd;

    oldpwd = get_env_var(data->env, "OLDPWD");
    if (!oldpwd || !oldpwd->value)
    {
        ft_putendl_fd("cd: OLDPWD not set", 2);
        return (1);
    }
    // Cambia al valor de OLDPWD y actualiza el directorio
    ft_putendl_fd(oldpwd->value, 1);
    return (cd_path(data, oldpwd->value, NULL));
}

// Función principal del comando 'cd'
int cd_builtin(t_data *data, t_cmd *cmd)
{
    t_env *home;
    int exit_;

    // Si el argumento es '-', ir al directorio anterior (OLD)
    if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
        return (cd_oldpwd(data));

    // Si se pasa una opción inválida
    if (cmd->args[1] && cmd->args[1][0] == '-')
    {
        ft_putendl_fd("cd: invalid option", 2);
        return (1);
    }

    // Si hay demasiados argumentos
    if (cmd->args[1] && cmd->args[2])
    {
        ft_putendl_fd("cd: too many arguments", 2);
        return (1);
    }

    // Si el argumento es ~, lo expandimos a HOME
    if (cmd->args[1] && ft_strcmp(cmd->args[1], "~") == 0)
    {
        home = get_env_var(data->env, "HOME");
        if (home)
            return (cd_path(data, home->value, home->value));
        else
        {
            ft_putendl_fd("cd: HOME not set", 2);
            return (1);
        }
    }

    // Intentamos cambiar al directorio HOME
    home = get_env_var(data->env, "HOME");
    if (home)
        exit_ = cd_path(data, cmd->args[1], home->value);
    else
        exit_ = cd_path(data, cmd->args[1], NULL);

    update_var(data);  // Actualizamos las variables PWD y OLDPWD
    return (exit_);
}
