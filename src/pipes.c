/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:27:36 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/13 15:27:41 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static pid_t	create_exec_child(t_cmd *cmd, int prev_fd,
	int pipe_fd[2], t_data *data)
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
		setup_child_process(cmd, prev_fd, pipe_fd);
		execute_command(cmd, data);
		exit(data->exit_status);
	}
	return (pid);
}

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

void	execute_piped_commands(t_cmd *cmd_list, t_data *data)
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*current_cmd;
	pid_t	last_pid;
	int		status;

	prev_fd = -1;
	current_cmd = cmd_list;
	last_pid = -1;
	while (current_cmd)
	{
		if (create_pipe_if_needed(current_cmd, pipe_fd) == -1)
			return ;
		last_pid = create_exec_child(current_cmd, prev_fd, pipe_fd, data);
		clean_parent_fds(&prev_fd, pipe_fd, current_cmd);
		current_cmd = current_cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}
