#include "minishell.h"

void executor(t_cmd *cmd_list, t_data *data)
{
    t_cmd *cmd = cmd_list;

    while (cmd)
    {
        if (cmd->builtin)
        {
            if (ft_strcmp(cmd->cmd, "echo") == 0)
                execute_builtin_echo(cmd);
            else if (ft_strcmp(cmd->cmd, "pwd") == 0)
                pwd_builtin(data);
            else if (ft_strcmp(cmd->cmd, "cd") == 0)
                cd_builtin(data, cmd);
        }
        else
        {
            char *binary_path = find_binary_path(cmd->cmd, data->env);
            if (!binary_path)
            {
                ft_putstr_fd(cmd->cmd, 2);
                ft_putendl_fd(": command not found", 2);
                cmd = cmd->next;
                continue;
            }

            char **envp = convert_env_to_array(data->env);
            pid_t pid = fork();
            if (pid == 0)
            {
                execve(binary_path, cmd->args, envp);
                perror("execve");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                int status;
                waitpid(pid, &status, 0);
                free(binary_path);
                ft_free_split(envp);
            }
            else
            {
                perror("fork");
            }
        }

        cmd = cmd->next;
    }
}
