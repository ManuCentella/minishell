/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:40:09 by szaghdad          #+#    #+#             */
/*   Updated: 2025/03/10 22:40:09 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 🔹 init_env - Inicializa la lista de variables de entorno a partir de `envp`.
 */
t_env	*init_env(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*equal_sign;
	char	*name;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			name = ft_strndup(envp[i], equal_sign - envp[i]);
			value = ft_strdup(equal_sign + 1);
			set_env_var(&env_list, name, value);
			free(name);
			free(value);
		}
		i++;
	}
	return (env_list);
}

/**
 * 🔹 get_env_var - Busca y retorna una variable de entorno desde la lista.
 */
t_env	*get_env_var(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->variable, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
