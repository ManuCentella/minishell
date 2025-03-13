/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:31:08 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/12 12:41:56 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_cmd *cmd_list, t_data *data)
{
	if (cmd_list && cmd_list->next)
		execute_piped_commands(cmd_list, data);
	else if (cmd_list)
		execute_command(cmd_list, data);
}

void	execute_command(t_cmd *cmd, t_data *data)
{
	int	i;

	if (handle_redirections(cmd) == -1)
		return ;
	if (cmd->args && cmd->args[0])
	{
		i = 0;
		while (cmd->args[i + 1])
			i++;
		set_env_var(&(data->env), "_", cmd->args[i]);
	}
	if (is_builtin(cmd->cmd))
		execute_builtin(cmd, data);
	else
		execute_external(cmd, data);
}

void	executor(t_cmd *cmd_list, t_data *data)
{
	int	stdin_backup;
	int	stdout_backup;
	int	stderr_backup;

	backup_stdio(&stdin_backup, &stdout_backup, &stderr_backup);
	if (handle_all_heredocs(cmd_list) == -1)
	{
		restore_and_close_stdio(stdin_backup, stdout_backup, stderr_backup);
		return ;
	}
	execute_commands(cmd_list, data);
	restore_and_close_stdio(stdin_backup, stdout_backup, stderr_backup);
}
