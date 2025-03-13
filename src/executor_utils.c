/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:33:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/13 13:36:03 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Muestra el mensaje de error "command not found"
void	command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

// Proceso hijo ejecuta el comando


void	child_process(t_cmd *cmd, char *binary_path, char **envp)
{
	// ✅ Restauramos SIGQUIT en los hijos para que `Ctrl+\` los mate
	signal(SIGQUIT, SIG_DFL);

	if (handle_redirections(cmd) == -1)
		exit(EXIT_FAILURE);

	execve(binary_path, cmd->args, envp);

	// Si `execve()` falla, capturamos el error específico
	perror("execve");

	if (errno == ENOENT)
		exit(127);  // Comando no encontrado
	if (errno == EACCES)
		exit(126);  // Permiso denegado
	if (errno == EISDIR)
		exit(126);  // Intento de ejecutar un directorio (como Bash)

	// Si no es un error específico, salimos con error genérico
	exit(1);
}


// Manejo de entrada/salida
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
