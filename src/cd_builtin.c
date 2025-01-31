#include "minishell.h"

void upd_env(t_data *data)
{
    (void)data; // Marca el parámetro como usado para evitar la advertencia
    // Implementación de upd_env
}

// ✅ Corrige `update_var()` para actualizar correctamente `PWD` y `OLDPWD`
static void update_var(t_data *data)
{
    t_env *variable;
    char *new_cwd;

    new_cwd = getcwd(NULL, 0);
    if (!new_cwd)
    {
        ft_putendl_fd("cd: error retrieving current directory", 2);
        return;
    }

    // Actualizar OLDPWD antes de modificar PWD
    variable = get_env_var(data->env, "OLDPWD");
    if (variable)
    {
        free(variable->value);
        variable->value = ft_strdup(data->cwd);
        upd_env(data);
    }

    // Actualizar PWD
    variable = get_env_var(data->env, "PWD");
    if (variable)
    {
        free(variable->value);
        variable->value = ft_strdup(new_cwd);
        upd_env(data);
    }

    // Actualizar cwd en data
    free(data->cwd);
    data->cwd = ft_strdup(new_cwd);
    free(new_cwd);
}

// ✅ `cd_home()` no cambia de directorio si `HOME` no está definido
static int cd_home(t_data *data, char *home)
{
    (void)data;  // Evita la advertencia de parámetro no usado

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
static int handle_cwd_fail(t_data *data)
{
    if (chdir("/") == -1)
        return (1);
    free(data->cwd);
    data->cwd = ft_strdup("/");
    update_var(data);
    return (0);
}

// ✅ `cd_path()` maneja correctamente errores en `getcwd()`
static int cd_path(t_data *data, char *path, char *home)
{
    char *cwd;

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

int cd_builtin(t_data *data, t_cmd *cmd)
{
    t_env *home;
    int exit_;

    exit_ = 0;

    if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
    {
        t_env *oldpwd = get_env_var(data->env, "OLDPWD");
        if (!oldpwd || !oldpwd->value)
        {
            ft_putendl_fd("cd: OLDPWD not set", 2);
            return (1);
        }
        ft_putendl_fd(oldpwd->value, 1);
        return (cd_path(data, oldpwd->value, NULL));
    }

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

// ✅ `get_env_var()` ahora maneja casos donde `env` es `NULL`
t_env *get_env_var(t_env *env, const char *name)
{
    if (!env)
        return (NULL);

    while (env)
    {
        if (ft_strcmp(env->variable, name) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}
