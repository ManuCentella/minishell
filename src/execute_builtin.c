/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:27:21 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 12:30:07 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0);
}

void execute_builtin(t_cmd *cmd, t_data *data)
{
    if (ft_strcmp(cmd->cmd, "echo") == 0)
        execute_builtin_echo(cmd);
    else if (ft_strcmp(cmd->cmd, "pwd") == 0)
        pwd_builtin(data);
    else if (ft_strcmp(cmd->cmd, "cd") == 0)
        cd_builtin(data, cmd);
    else if (ft_strcmp(cmd->cmd, "export") == 0)
        export_builtin(data, cmd);
    else if (ft_strcmp(cmd->cmd, "unset") == 0)
        unset_builtin(data, cmd);
    else if (ft_strcmp(cmd->cmd, "env") == 0)
        env_builtin(data);
    else if (ft_strcmp(cmd->cmd, "exit") == 0)
        exit_builtin(cmd);
}
