#include "minishell.h"

// 1️⃣ Crea un pipe si el comando tiene otro después
static int create_pipe_if_needed(t_cmd *cmd_list, int pipe_fd[2])
{
    if (cmd_list->next)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            return (-1);
        }
    }
    return (0);
}

// 2️⃣ Configura la redirección en el proceso hijo
static void setup_child_process(t_cmd *cmd_list, int prev_fd, int pipe_fd[2])
{
    if (prev_fd != -1) // Si hay un pipe anterior, redirigir stdin
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (cmd_list->next) // Si hay un pipe siguiente, redirigir stdout
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
    }
}

// 3️⃣ Cierra los file descriptors en el padre
static void parent_process_cleanup(int *prev_fd, int pipe_fd[2], t_cmd *cmd_list)
{
    if (*prev_fd != -1)
    {
        close(*prev_fd);
        *prev_fd = -1; // Evita accesos a FD cerrados
    }
    if (cmd_list->next)
    {
        close(pipe_fd[1]);
        *prev_fd = pipe_fd[0]; // Guardar la lectura del pipe para el siguiente proceso
    }
}

// 4️⃣ Detecta builtins críticos que NO pueden ejecutarse en pipes
int is_critical_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->cmd)
        return (0);
    return (ft_strcmp(cmd->cmd, "cd") == 0 ||
            ft_strcmp(cmd->cmd, "export") == 0 ||
            ft_strcmp(cmd->cmd, "unset") == 0 ||
            ft_strcmp(cmd->cmd, "exit") == 0);
}

// 5️⃣ Función principal que maneja los pipes
void execute_piped_commands(t_cmd *cmd_list, t_data *data)
{
    int pipe_fd[2];
    int prev_fd = -1;
    pid_t pid;
    int status;
    t_cmd *current_cmd = cmd_list;

    while (current_cmd)
    {
        if (create_pipe_if_needed(current_cmd, pipe_fd) == -1)
            return;

        if (is_critical_builtin(current_cmd)) // Bloquear builtins críticos en pipes
        {
            ft_putendl_fd("minishell: error: built-in no permitido en pipes", STDERR_FILENO);
            return;
        }

        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return;
        }
        else if (pid == 0) // Proceso hijo
        {
            setup_child_process(current_cmd, prev_fd, pipe_fd);
            if (handle_redirections(current_cmd) == -1)
            {
                close(prev_fd);
                exit(EXIT_FAILURE);
            }
            execute_command(current_cmd, data);
            exit(data->exit_status);
        }

        parent_process_cleanup(&prev_fd, pipe_fd, current_cmd);
        current_cmd = current_cmd->next;
    }

    // 🔥 Esperamos a TODOS los procesos hijos para evitar zombies
    while (waitpid(-1, &status, 0) > 0)
    {
        if (WIFEXITED(status))
            data->exit_status = WEXITSTATUS(status);
    }

    // 🔥 Asegurar que no dejamos FD abiertos en el padre
    if (prev_fd != -1)
        close(prev_fd);
}
