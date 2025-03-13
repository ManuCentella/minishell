/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:17:18 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/13 15:31:23 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*get_binary_path(t_cmd *cmd, t_data *data)
{
	char	*binary_path;

	binary_path = find_binary_path(cmd->cmd, data->env);
	if (!binary_path)
	{
		command_not_found(cmd->cmd);
		g_exit_status = 127; // ✅ Ahora $? se actualizará correctamente
	}
	return (binary_path);
}

// Espera a que el proceso hijo termine y actualiza el estado de salida.
void	wait_for_child(pid_t pid, t_data *data)
{
	int	status;
	int	signal_num;

	(void)data;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		g_exit_status = 128 + signal_num;
	}
}

void	execute_external(t_cmd *cmd, t_data *data)
{
	char	*binary_path;
	char	**envp;
	pid_t	pid;

	binary_path = get_binary_path(cmd, data);
	if (!binary_path)
		return ;
	envp = convert_env_to_array(data->env);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
		child_process(cmd, binary_path, envp);
	else
		wait_for_child(pid, data);
	free(binary_path);
	ft_free_split(envp);
}
