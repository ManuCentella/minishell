/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/18 13:35:37 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/18 13:35:37 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}

void	free_cmd_args(t_cmd *cmd)
{
	free_args(cmd->args);
	cmd->args = NULL;
	free(cmd->infile);
	cmd->infile = NULL;
	free(cmd->outfile);
	cmd->outfile = NULL;
	free(cmd->appendfile);
	cmd->appendfile = NULL;
	free(cmd->errfile);
	cmd->errfile = NULL;
	free(cmd->heredoc);
	cmd->heredoc = NULL;
	free(cmd->heredoc_content);
	cmd->heredoc_content = NULL;
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->cmd);
		cmd->cmd = NULL;
		free_cmd_args(cmd);
		free(cmd);
		cmd = tmp;
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_crlf();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
		signal(SIGINT, signal_handler);
	}
}

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
			free_tokens(tokens);
			executor(cmd_list, data);
			free_cmd_list(cmd_list);
		}
		free(input);
	}
}
