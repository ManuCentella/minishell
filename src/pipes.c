#include "minishell.h"

// Detecta builtins críticos que NO pueden ejecutarse en pipes
int is_critical_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->cmd)
        return (0);
    return (ft_strcmp(cmd->cmd, "cd") == 0 ||
            ft_strcmp(cmd->cmd, "export") == 0 ||
            ft_strcmp(cmd->cmd, "unset") == 0 ||
            ft_strcmp(cmd->cmd, "exit") == 0);
}

// 🔹 Crea un pipe si es necesario
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

// 🔹 Configura la redirección en el proceso hijo
static void setup_child_process(t_cmd *cmd_list, int prev_fd, int pipe_fd[2])
{
    if (prev_fd != -1)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (cmd_list->next)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
    }
    if (handle_redirections(cmd_list) == -1)
        exit(EXIT_FAILURE);
}

// 🔹 Crea y ejecuta un proceso hijo
static pid_t create_and_execute_child(t_cmd *cmd, int prev_fd, int pipe_fd[2], t_data *data)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (-1);
    }
    else if (pid == 0)
    {
        setup_child_process(cmd, prev_fd, pipe_fd);
        execute_command(cmd, data);
        exit(data->exit_status);
    }
    return (pid);
}

// 🔹 Limpia descriptores en el proceso padre
static void clean_parent_fds(int *prev_fd, int pipe_fd[2], t_cmd *cmd)
{
    if (*prev_fd != -1)
        close(*prev_fd);
    if (cmd->next)
    {
        close(pipe_fd[1]);
        *prev_fd = pipe_fd[0];
    }
}

// 🔥 Función principal optimizada
void execute_piped_commands(t_cmd *cmd_list, t_data *data)
{
    int pipe_fd[2], prev_fd = -1;
    t_cmd *current_cmd = cmd_list;

    // 🔥 Ejecutar el primer comando en la shell principal si es un builtin crítico
    if (current_cmd && is_critical_builtin(current_cmd))
    {
        execute_builtin(current_cmd, data);
        current_cmd = current_cmd->next; // Continuar con la tubería
    }

    // 🔥 Procesar el resto de la tubería con procesos hijos
    while (current_cmd)
    {
        if (create_pipe_if_needed(current_cmd, pipe_fd) == -1)
            return;

        create_and_execute_child(current_cmd, prev_fd, pipe_fd, data);
        clean_parent_fds(&prev_fd, pipe_fd, current_cmd);
        current_cmd = current_cmd->next;
    }

    if (prev_fd != -1)
        close(prev_fd);

    // Esperar a todos los procesos hijos
    int status;
    while (waitpid(-1, &status, 0) > 0)
    {
        if (WIFEXITED(status))
            data->exit_status = WEXITSTATUS(status);
    }
}
