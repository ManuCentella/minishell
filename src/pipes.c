/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:15:47 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/10 22:28:06 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔹 Crea un pipe si es necesario
static int	create_pipe_if_needed(t_cmd *cmd_list, int pipe_fd[2])
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
static void	setup_child_process(t_cmd *cmd_list, int prev_fd, int pipe_fd[2])
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

// 🔹 Crea y ejecuta un proceso hijo, almacenando el último PID
// Proceso hijo
// Almacenar el último PID
static pid_t	create_and_execute_child(t_cmd *cmd, t_pipe_data *pipe_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		setup_child_process(cmd, pipe_data->prev_fd, pipe_data->pipe_fd);
		execute_command(cmd, pipe_data->data);
		exit(pipe_data->data->exit_status);
	}
	pipe_data->last_pid = pid;
	return (pid);
}

// 🔹 Limpia descriptores en el proceso padre
static void	clean_parent_fds(int *prev_fd, int pipe_fd[2], t_cmd *cmd)
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
// 🔥 Procesar el resto de la tubería con procesos hijos
// 🔥 Esperar solo al último proceso hijo
void	process_command(t_cmd *cmd, t_pipe_data *pipe_data)
{
	if (create_pipe_if_needed(cmd, pipe_data->pipe_fd) == -1)
		return ;
	create_and_execute_child(cmd, pipe_data);
	clean_parent_fds(&pipe_data->prev_fd, pipe_data->pipe_fd, cmd);
}
