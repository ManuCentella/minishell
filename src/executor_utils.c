/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:33:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/02/11 14:31:00 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Muestra el mensaje de error "command not found"
void	command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

// Lógica que se ejecuta solo en el proceso hijo
void	child_process(t_cmd *cmd, char *binary_path, char **envp)
{
	if (handle_redirections(cmd) == -1)
		exit(EXIT_FAILURE);

	execve(binary_path, cmd->args, envp);

	// Si execve falla, imprimimos error y liberamos memoria
	perror("execve");
	free(binary_path);
	ft_free_split(envp);
	exit(127); // Código de salida estándar para "command not found"
}


