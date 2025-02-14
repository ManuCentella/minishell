/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:31:08 by mcentell          #+#    #+#             */
/*   Updated: 2025/02/11 18:45:34 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    return (ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}

static void backup_stdio(int *stdin_backup, int *stdout_backup, int *stderr_backup)
{
    *stdin_backup = dup(STDIN_FILENO);
    *stdout_backup = dup(STDOUT_FILENO);
    *stderr_backup = dup(STDERR_FILENO);
}

static void close_stdio(int stdin_backup, int stdout_backup, int stderr_backup)
{
    close(stdin_backup);
    close(stdout_backup);
    close(stderr_backup);
}

// 1) Restaura los descriptores y avanza
void	restore_and_continue(t_cmd **cmd, int stdin_backup, int stdout_backup,
		int stderr_backup)
{
	restore_stdio(stdin_backup, stdout_backup, stderr_backup);
	*cmd = (*cmd)->next;
}

// 2) Ejecuta comandos internos (builtins)
void	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		execute_builtin_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		pwd_builtin(data);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		cd_builtin(data, cmd);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		export_builtin(data, cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		unset_builtin(data, cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		env_builtin(data);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		exit_builtin(cmd);
}

// 3) Ejecuta comandos externos (llama a funciones auxiliares si hace falta)
void	execute_external(t_cmd *cmd, t_data *data)
{
	char	*binary_path = find_binary_path(cmd->cmd, data->env);
	if (!binary_path)
	{
		command_not_found(cmd->cmd);
		exit(127); // 🔧 Código de salida correcto para "command not found"
	}

	char **envp = convert_env_to_array(data->env);
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
		child_process(cmd, binary_path, envp);
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) // Propagar el código de salida del hijo
			data->exit_status = WEXITSTATUS(status);
		else
			data->exit_status = 1; // Error inesperado
		free(binary_path);
		ft_free_split(envp);
	}
}

// 4) Decide si es builtin o externo
void execute_command(t_cmd *cmd, t_data *data)
{
    if (handle_redirections(cmd) == -1)
        return;

    if (cmd->builtin)
        execute_builtin(cmd, data);
    else
        execute_external(cmd, data);
}


// 5) Función principal de ejecución
void executor(t_cmd *cmd_list, t_data *data)
{
    int stdin_backup, stdout_backup, stderr_backup;

    backup_stdio(&stdin_backup, &stdout_backup, &stderr_backup);

    /* Si hay más de un comando en la lista, se interpretan como una tubería */
    if (cmd_list && cmd_list->next)
    {
        if (handle_all_heredocs(cmd_list) == -1)
        {
            restore_stdio(stdin_backup, stdout_backup, stderr_backup);
            close_stdio(stdin_backup, stdout_backup, stderr_backup);
            return;
        }
        execute_piped_commands(cmd_list, data);
    }
    /* Si solo hay un comando, se procesa de forma normal */
    else if (cmd_list)
    {
        if (handle_all_heredocs(cmd_list) == -1)
        {
            restore_stdio(stdin_backup, stdout_backup, stderr_backup);
            close_stdio(stdin_backup, stdout_backup, stderr_backup);
            return;
        }
        cmd_list->builtin = is_builtin(cmd_list->cmd);
        execute_command(cmd_list, data);
    }

    restore_stdio(stdin_backup, stdout_backup, stderr_backup);
    close_stdio(stdin_backup, stdout_backup, stderr_backup);
}
