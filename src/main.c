#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    // Crear una instancia de t_data y configurar las variables de entorno
    t_data data;
    data.env = NULL;
    data.cwd = getcwd(NULL, 0);

    // Convertir envp a t_env y asignarlo a data.env
    for (int i = 0; envp[i]; i++)
    {
        t_env *new_env = malloc(sizeof(t_env));
        char *equal_sign = strchr(envp[i], '=');
        new_env->variable = strndup(envp[i], equal_sign - envp[i]);
        new_env->value = strdup(equal_sign + 1);
        new_env->next = data.env;
        data.env = new_env;
    }

    // Primer comando: `pwd`
    t_cmd cmd1 = {
        .cmd = "pwd",
        .args = (char *[]){"pwd", NULL},
        .builtin = 1,
        .next = NULL
    };

    // Segundo comando: `cd /tmp`
    t_cmd cmd2 = {
        .cmd = "cd",
        .args = (char *[]){"cd", "/tmp", NULL},
        .builtin = 1,
        .next = NULL
    };

    // Tercer comando: `pwd` para verificar el cambio de directorio
    t_cmd cmd3 = {
        .cmd = "pwd",
        .args = (char *[]){"pwd", NULL},
        .builtin = 1,
        .next = NULL
    };

    // Cuarto comando: `echo "Directorio actual:"`
    t_cmd cmd4 = {
        .cmd = "echo",
        .args = (char *[]){"echo", "Directorio actual:", NULL},
        .builtin = 1,
        .next = NULL
    };

    // Quinto comando: `echo` sin argumentos
    t_cmd cmd5 = {
        .cmd = "echo",
        .args = (char *[]){"echo", NULL}, // Comando echo sin argumentos
        .builtin = 1,
        .next = NULL
    };

    // Simulación de Pipe: `pwd | cd /tmp | pwd | echo "Directorio actual:" | echo`
    cmd1.next = &cmd2;
    cmd2.next = &cmd3;
    cmd3.next = &cmd4;
    cmd4.next = &cmd5;

    // Ejecutar la lista de comandos
    executor(&cmd1, &data);

    // Liberar la memoria asignada a data.env
    t_env *tmp;
    while (data.env)
    {
        tmp = data.env;
        data.env = data.env->next;
        free(tmp->variable);
        free(tmp->value);
        free(tmp);
    }
    free(data.cwd);

    return 0;
}
