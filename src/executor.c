/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:31:08 by mcentell          #+#    #+#             */
/*   Updated: 2025/02/06 13:32:25 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*binary_path;
	char	**envp;
	pid_t	pid;
	int		status;

	binary_path = find_binary_path(cmd->cmd, data->env);
	if (!binary_path)
	{
		command_not_found(cmd->cmd);  // <- Proviene de executor_utils.c
		return ;
	}
	envp = convert_env_to_array(data->env);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
		child_process(cmd, binary_path, envp); // <- Proviene de executor_utils.c
	else
	{
		waitpid(pid, &status, 0);
		free(binary_path);
		ft_free_split(envp);
	}
}

// 4) Decide si es builtin o externo
void	execute_command(t_cmd *cmd, t_data *data)
{
	if (handle_redirections(cmd) == -1)
		return ;
	if (cmd->builtin)
		execute_builtin(cmd, data);
	else
		execute_external(cmd, data);
}

// 5) Función principal de ejecución
void	executor(t_cmd *cmd_list, t_data *data)
{
	t_cmd	*cmd;
	int		stdin_backup;
	int		stdout_backup;
	int		stderr_backup;

	cmd = cmd_list;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	stderr_backup = dup(STDERR_FILENO);
	while (cmd)
	{
		execute_command(cmd, data);
		cmd = cmd->next;
	}
	restore_stdio(stdin_backup, stdout_backup, stderr_backup);
	close(stdin_backup);
	close(stdout_backup);
	close(stderr_backup);
}
