/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:15:39 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/24 16:40:33 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: error in dup2 (input)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_output_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: error opening output file");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: error in dup2 (output)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_append_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->appendfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: error opening append file");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: error in dup2 (append)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_error_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->errfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: error opening error file");
		return (-1);
	}
	if (dup2(fd, STDERR_FILENO) == -1)
	{
		perror("minishell: error in dup2 (stderr)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	if (cmd->infile && handle_input_redirection(cmd) == -1)
		return (-1);
	if (cmd->outfile && handle_output_redirection(cmd) == -1)
		return (-1);
	if (cmd->appendfile && handle_append_redirection(cmd) == -1)
		return (-1);
	if (cmd->errfile && handle_error_redirection(cmd) == -1)
		return (-1);
	if (cmd->heredoc && handle_heredoc(cmd) == -1)
		return (-1);
	return (0);
}
