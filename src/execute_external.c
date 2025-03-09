/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:17:18 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 21:11:20 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_binary_path(t_cmd *cmd, t_data *data)
{
	char	*binary_path;

	binary_path = find_binary_path(cmd->cmd, data->env);
	if (!binary_path)
	{
		command_not_found(cmd->cmd);
		data->exit_status = 127;
	}
	return (binary_path);
}

// Espera a que el proceso hijo termine y actualiza el estado de salida.
void	wait_for_child(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else
		data->exit_status = 1;
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
