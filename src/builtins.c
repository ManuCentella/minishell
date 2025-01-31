#include "minishell.h"

// Verifica si los argumentos contienen "-n"
static int check_option(char **args)
{
    int i = 1;

    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        int j = 1;
        while (args[i][j] == 'n') // Permite múltiples `n`
            j++;
        if (args[i][j] != '\0') // Si hay algo más después de `n`, no es una opción válida
            return (1);
        i++;
    }
    return (i);
}

int execute_builtin_echo(t_cmd *cmd)
{
    char **args;
    int i;
    int newline = 1;

    args = cmd->args;
    if (!args[1])
    {
        ft_putchar_fd('\n', 1);
        return (0);
    }

    i = check_option(args);
    if (i > 1)
        newline = 0;

    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }

    if (newline)
        ft_putchar_fd('\n', 1);

    return (0);
}

int pwd_builtin(t_data *data)
{
    if (!data->cwd)
    {
        ft_putendl_fd("pwd: error retrieving current directory", 2);
        return (1);
    }

    ft_putendl_fd(data->cwd, 1);
    return (0);
}
