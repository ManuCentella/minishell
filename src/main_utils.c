/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:29:17 by szaghdad          #+#    #+#             */
/*   Updated: 2025/03/10 22:29:17 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
extern int g_exit_status;

void	disable_echoctl(void)
{
	// Esta función ya no es necesaria
}

/**
 * 🛠️ free_cmd_list - Libera la memoria de la lista de comandos.
 */
void	free_cmd_args(t_cmd *cmd)
{
	int	i;

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
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->cmd);
		free_cmd_args(cmd);
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
		write(STDOUT_FILENO, "\nminishell> ", 12);
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_exit_status = 131;  // SIGQUIT = 128 + 3
	}
}

// ✅ Configurar señales
// ✅ Desactivar impresión de `^C`
void	process_input(t_data *data)
{
	char	*input;
	char	**tokens;
	t_cmd	*cmd_list;

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
			cmd_list = parse_tokens(tokens, data->env, data->exit_status);
			executor(cmd_list, data);
			free_cmd_list(cmd_list);
		}
		free(input);
	}
}

