
#include "minishell.h"

static int	handle_input_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n",
			cmd->infile);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: error en dup2 (entrada)");
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
		perror("minishell: error abriendo archivo de salida");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: error en dup2 (salida)");
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
		perror("minishell: error abriendo archivo de append");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: error en dup2 (append)");
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
		perror("minishell: error abriendo archivo de errores");
		return (-1);
	}
	if (dup2(fd, STDERR_FILENO) == -1)
	{
		perror("minishell: error en dup2 (stderr)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_heredoc(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: error creando pipe para heredoc");
		return (-1);
	}
	write(pipe_fd[1], cmd->heredoc_content, ft_strlen(cmd->heredoc_content));
	close(pipe_fd[1]); // Cerramos escritura en el pipe
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: error en dup2 (heredoc)");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	if (cmd->infile && handle_input_redirection(cmd) == -1)
		return (-1);
	if (cmd->outfile && handle_output_redirection(cmd) == -1)
		return -1;
	if (cmd->appendfile && handle_append_redirection(cmd) == -1)
		return -1;
	if (cmd->errfile && handle_error_redirection(cmd) == -1)
		return -1;
	if (cmd->heredoc && handle_heredoc(cmd) == -1)
		return -1;
	return 0;
}

void	restore_stdio(int stdin_backup, int stdout_backup, int stderr_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stderr_backup, STDERR_FILENO);
}
