/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:08:21 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 20:22:57 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Obtener configuración actual del terminal
// 🔹 Deshabilitar impresión de caracteres de control (como ^C)
// Aplicar configuración inmediatamente
void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * 🛠️ free_cmd_list - Libera la memoria de la lista de comandos.
 */
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->cmd);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd->appendfile);
		free(cmd->errfile);
		free(cmd->heredoc);
		free(cmd->heredoc_content);
		free(cmd);
		cmd = tmp;
	}
}

/**
 * 🛠️ signal_handler - Maneja `Ctrl+C` y `Ctrl+\`
 */
// Ctrl+C
// Nueva línea para evitar caracteres extra
// Resetea readline()
// Borra la línea actual
// Redibuja el prompt sin imprimir ^C
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// ✅ Configurar señales
// ✅ Desactivar impresión de `^C`
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**tokens;
	t_cmd	*cmd_list;
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = init_env(envp);
	data.cwd = getcwd(NULL, 0);
	data.exit_status = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	disable_echoctl();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			tokens = tokenize_input(input);
			cmd_list = parse_tokens(tokens, data.env, data.exit_status);
			executor(cmd_list, &data);
			free_cmd_list(cmd_list);
		}
		free(input);
	}
	free(data.cwd);
	free_env_list(data.env);
	return (0);
}
