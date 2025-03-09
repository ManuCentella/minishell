/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:33:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/09 12:30:01 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Muestra el mensaje de error "command not found"
void command_not_found(char *cmd)
{
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putendl_fd(": command not found", STDERR_FILENO);
}

// Proceso hijo ejecuta el comando
void child_process(t_cmd *cmd, char *binary_path, char **envp)
{
    if (handle_redirections(cmd) == -1)
        exit(EXIT_FAILURE);

    execve(binary_path, cmd->args, envp);

    perror("execve");
    free(binary_path);
    ft_free_split(envp);
    exit(127);
}

// Manejo de entrada/salida
void backup_stdio(int *stdin_backup, int *stdout_backup, int *stderr_backup)
{
    *stdin_backup = dup(STDIN_FILENO);
    *stdout_backup = dup(STDOUT_FILENO);
    *stderr_backup = dup(STDERR_FILENO);
}

void close_stdio(int stdin_backup, int stdout_backup, int stderr_backup)
{
    close(stdin_backup);
    close(stdout_backup);
    close(stderr_backup);
}

void restore_and_close_stdio(int stdin_backup, int stdout_backup, int stderr_backup)
{
    restore_stdio(stdin_backup, stdout_backup, stderr_backup);
    close_stdio(stdin_backup, stdout_backup, stderr_backup);
}



