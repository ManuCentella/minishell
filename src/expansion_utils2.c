/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espansio_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:36:15 by szaghdad          #+#    #+#             */
/*   Updated: 2025/03/10 22:36:15 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **expanded, char c, int *i)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*expanded = ft_strjoin_free(*expanded, tmp, 1);
	(*i)++;
}

char	*get_variable_value(const char *var_name, t_env *env, int exit_status)
{
	t_env	*env_var;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(exit_status));
	env_var = get_env_var(env, var_name);
	if (env_var && env_var->value)
		return (ft_strdup(env_var->value));
	return (NULL);
}
