/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:26:08 by szaghdad          #+#    #+#             */
/*   Updated: 2025/03/10 22:26:08 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdio(int stdin_backup, int stdout_backup, int stderr_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stderr_backup, STDERR_FILENO);
}

int	handle_all_heredocs(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			if (handle_heredoc(tmp) == -1)
				return (-1);
			free(tmp->heredoc);
			tmp->heredoc = NULL;
		}
		tmp = tmp->next;
	}
	return (0);
}
