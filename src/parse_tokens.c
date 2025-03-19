/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:15:54 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/19 11:25:50 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_token_logic(t_cmd **current, t_cmd **cmd_list, char **tokens,
		int *i)
{
	if (!tokens[*i] || tokens[*i][0] == '\0')
		return ;
	if (!*current)
	{
		*current = init_cmd();
		*cmd_list = *current;
	}
	if (strcmp(tokens[*i], "|") == 0 || strcmp(tokens[*i], ";") == 0)
		handle_pipe_or_separator(current, tokens, *i);
	else if (strcmp(tokens[*i], "<") == 0 || strcmp(tokens[*i], ">") == 0
		|| strcmp(tokens[*i], ">>") == 0 || strcmp(tokens[*i], "<<") == 0)
		handle_redirection_tokens(*current, tokens, i);
	else
		add_command_or_argument(*current, tokens[*i]);
}

t_cmd	*parse_tokens(char **tokens, t_env *env, int exit_status)
{
	int		i;
	t_cmd	*cmd_list;
	t_cmd	*current;

	if (!tokens || !*tokens)
		return (NULL);
	cmd_list = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		if (!tokens[i])
			continue ;
		parse_token_logic(&current, &cmd_list, tokens, &i);
		i++;
	}
	expand_cmd_list(cmd_list, env, exit_status);
	return (cmd_list);
}
