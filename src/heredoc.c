/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:12 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/11 19:06:57 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔹 Crea un pipe para heredoc y devuelve su file descriptor
static int	open_heredoc_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: error creando pipe para heredoc");
		return (-1);
	}
	return (0);
}

// 🔹 Lee la entrada del usuario y la escribe en el pipe
// 🔥 Si el delimitador es encontrado, terminamos
// Cerramos el extremo de escritura del pipe
static void	read_heredoc_input(int pipe_fd[2], char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
}

// 🔹 Redirige STDIN al pipe de heredoc
// Ya no necesitamos el file descriptor
static int	redirect_heredoc_to_stdin(int pipe_fd[2])
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: error en dup2 (heredoc)");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

// 🔥 Función principal que maneja heredoc
int	handle_heredoc(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (!cmd->heredoc)
		return (0);
	if (open_heredoc_pipe(pipe_fd) == -1)
		return (-1);
	read_heredoc_input(pipe_fd, cmd->heredoc);
	return (redirect_heredoc_to_stdin(pipe_fd));
}
