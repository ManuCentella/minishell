/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:27:40 by szaghdad          #+#    #+#             */
/*   Updated: 2025/03/10 22:27:40 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_piped_commands(t_cmd *cmd_list, t_data *data)
{
	t_pipe_data		pipe_data;
	t_cmd			*current_cmd;
	int				status;

	pipe_data.pipe_fd[2] = -1;
	pipe_data.prev_fd = -1;
	pipe_data.last_pid = -1;
	current_cmd = cmd_list;
	while (current_cmd)
	{
		process_command(current_cmd, &pipe_data);
		current_cmd = current_cmd->next;
	}
	if (pipe_data.prev_fd != -1)
		close(pipe_data.prev_fd);
	if (pipe_data.last_pid != -1)
	{
		waitpid(pipe_data.last_pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}
