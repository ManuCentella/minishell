/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:04:06 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/17 23:27:33 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(t_cmd *cmd, char **tokens, int *i)
{
	if (strcmp(tokens[*i], "<") == 0 && tokens[*i + 1])
		cmd->infile = strdup(tokens[++(*i)]);
	else if (strcmp(tokens[*i], ">") == 0 && tokens[*i + 1])
		cmd->outfile = strdup(tokens[++(*i)]);
	else if (strcmp(tokens[*i], ">>") == 0 && tokens[*i + 1])
		cmd->appendfile = strdup(tokens[++(*i)]);
	else if (strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
		cmd->heredoc = strdup(tokens[++(*i)]);
}

void	handle_pipe_or_separator(t_cmd **current, char **tokens, int i)
{
	if (!(*current)->cmd || strlen((*current)->cmd) == 0)
	{
		fprintf(stderr, "minishell: error de sintaxis token `%s`\n", tokens[i]);
		return ;
	}
	if (strcmp(tokens[i], "|") == 0)
		(*current)->is_piped = 1;
	(*current)->next = init_cmd();
	*current = (*current)->next;
}

void	handle_redirection_tokens(t_cmd *current, char **tokens, int *i)
{
	if (!current->cmd || strlen(current->cmd) == 0)
	{
		fprintf(stderr, "minishell: error de sintaxis cerca del token `%s`\n",
			tokens[*i]);
		return ;
	}
	handle_redirection(current, tokens, i);
}
