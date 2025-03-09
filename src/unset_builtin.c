/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mcentell <mcentell@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:31:08 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/09 12:25:26 by mcentell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ✅ Implementa `unset`
int	unset_builtin(t_data *data, t_cmd *cmd)
{
	int		i;
	t_env	*prev;
	t_env	*env;

	i = 1;
	if (!cmd->args[1])
		return (ft_putendl_fd("unset: not enough arguments", 2), 1);
	while (cmd->args[i])
	{
		prev = NULL;
		env = data->env;
		while (env)
		{
			if (ft_strcmp(env->variable, cmd->args[i]) == 0)
			{
				if (prev)
					prev->next = env->next;
				else
					data->env = env->next;
				free(env->variable);
				free(env->value);
				free(env);
				break ;
			}
			prev = env;
			env = env->next;
		}
		i++;
	}
	return (0);
}
