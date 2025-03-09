/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:40:38 by mcentell          #+#    #+#             */
/*   Updated: 2025/03/09 12:30:14 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función auxiliar para contar cuántas variables de entorno hay.
static int	count_env_nodes(t_env *env)
{
	int count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

// Función auxiliar para crear "VARIABLE=VALOR".
static char	*create_env_str(t_env *node)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(node->variable, "=");
	res = ft_strjoin_free(tmp, node->value, 1);
	return (res);
}

// Convierte la lista de entorno en array de strings tipo "VAR=VAL"
char	**convert_env_to_array(t_env *env)
{
	char	**env_array;
	int		count;
	int		i;

	count = count_env_nodes(env);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		env_array[i] = create_env_str(env);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
