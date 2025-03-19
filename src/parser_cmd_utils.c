/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:06:03 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/19 19:19:38 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("malloc");
		return (NULL);
	}
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->builtin = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->appendfile = NULL;
	cmd->errfile = NULL;
	cmd->heredoc = NULL;
	cmd->heredoc_content = NULL;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

static char	**expand_args(char **old_args, char *token)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	while (old_args && old_args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = old_args[i];
		i++;
	}
	new_args[i] = strdup(token);
	if (!new_args[i])
	{
		free(new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	free(old_args);
	return (new_args);
}

void	add_arg(t_cmd *cmd, char *token)
{
	char	**tmp;

	tmp = expand_args(cmd->args, token);
	if (!tmp)
	{
		perror("malloc/strdup");
		return ;
	}
	cmd->args = tmp;
}

void	add_command_or_argument(t_cmd *current, char *token)
{
	if (!current->cmd)
	{
		current->cmd = strdup(token);
		if (!current->cmd)
		{
			perror("strdup");
			return ;
		}
	}
	add_arg(current, token);
}
