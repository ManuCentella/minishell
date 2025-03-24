/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:04:06 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/24 17:13:02 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(t_cmd *cmd, char **tokens, int *i)
{
	if (ft_strcmp(tokens[*i], "<") == 0 && tokens[*i + 1])
		cmd->infile = ft_strdup(tokens[++(*i)]);
	else if (ft_strcmp(tokens[*i], ">") == 0 && tokens[*i + 1])
		cmd->outfile = ft_strdup(tokens[++(*i)]);
	else if (ft_strcmp(tokens[*i], ">>") == 0 && tokens[*i + 1])
		cmd->appendfile = ft_strdup(tokens[++(*i)]);
	else if (ft_strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
		cmd->heredoc = ft_strdup(tokens[++(*i)]);
}

void	handle_pipe_or_separator(t_cmd **current, char **tokens, int i)
{
	if (!(*current)->cmd || ft_strlen((*current)->cmd) == 0)
	{
		ft_putstr_fd("minishell: syntax error near token `", 2);
		ft_putstr_fd(tokens[i], 2);
		ft_putendl_fd("'", 2);
		return ;
	}
	if (ft_strcmp(tokens[i], "|") == 0)
		(*current)->is_piped = 1;
	(*current)->next = init_cmd();
	*current = (*current)->next;
}

void	handle_redirection_tokens(t_cmd *current, char **tokens, int *i)
{
	if (!current->cmd || ft_strlen(current->cmd) == 0)
	{
		ft_putstr_fd("minishell: syntax error near token `", 2);
		ft_putstr_fd(tokens[*i], 2);
		ft_putendl_fd("'", 2);
		return ;
	}
	handle_redirection(current, tokens, i);
}
