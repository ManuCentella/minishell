/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:03:20 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/17 23:27:09 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd(t_cmd *cmd, t_env *env, int exit_status)
{
	char	*expanded;

	if (cmd->cmd && strchr(cmd->cmd, '$'))
	{
		expanded = expand_variable(cmd->cmd, env, exit_status);
		free(cmd->cmd);
		cmd->cmd = expanded;
	}
}

void	expand_args(t_cmd *cmd, t_env *env, int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (strchr(cmd->args[i], '$'))
		{
			expanded = expand_variable(cmd->args[i], env, exit_status);
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

void	expand_cmd_list(t_cmd *cmd_list, t_env *env, int exit_status)
{
	while (cmd_list)
	{
		expand_cmd(cmd_list, env, exit_status);
		expand_args(cmd_list, env, exit_status);
		cmd_list = cmd_list->next;
	}
}
