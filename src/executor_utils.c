/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:33:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/19 19:36:05 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	child_process(t_cmd *cmd, char *binary_path, char **envp)
{
	t_siga	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	ft_memset(&sa.sa_mask, 0, sizeof(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	if (handle_redirections(cmd) == -1)
		exit(EXIT_FAILURE);
	execve(binary_path, cmd->args, envp);
	perror("execve");
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	exit(1);
}

void	backup_stdio(int *stdin_backup, int *stdout_backup, int *stderr_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	*stderr_backup = dup(STDERR_FILENO);
}

void	close_stdio(int stdin_backup, int stdout_backup, int stderr_backup)
{
	close(stdin_backup);
	close(stdout_backup);
	close(stderr_backup);
}

void	restore_and_close_stdio(int stdin_backup, int stdout_backup,
		int stderr_backup)
{
	restore_stdio(stdin_backup, stdout_backup, stderr_backup);
	close_stdio(stdin_backup, stdout_backup, stderr_backup);
}
