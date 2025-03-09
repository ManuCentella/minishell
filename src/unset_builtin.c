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

int	remove_env_variable(t_data *data, char *var)
{
	t_env	*prev;
	t_env	*env;

	prev = NULL;
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->variable, var) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				data->env = env->next;
			free(env->variable);
			free(env->value);
			free(env);
			return (0);
		}
		prev = env;
		env = env->next;
	}
	return (1);
}

// ✅ Implementa `unset`
int	unset_builtin(t_data *data, t_cmd *cmd)
{
	int		i;

	i = 1;
	if (!cmd->args[1])
		return (ft_putendl_fd("unset: not enough arguments", 2), 1);
	while (cmd->args[i])
	{
		remove_env_variable(data, cmd->args[i]);
		i++;
	}
	return (0);
}
