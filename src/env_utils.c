/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:27:29 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/18 15:42:52 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_existing_var(t_env *var, const char *value)
{
	char	*new_value;

	if (value)
		new_value = ft_strdup(value);
	else
		new_value = ft_strdup("");
	if (!new_value)
		return ;
	free(var->value);
	var->value = new_value;
}

void	set_env_var(t_env **env, const char *name, const char *value)
{
	t_env	*var;
	t_env	*new_var;
	char	*new_value;

	var = get_env_var(*env, name);
	if (var)
	{
		update_existing_var(var, value);
		return ;
	}
	if (value)
		new_value = ft_strdup(value);
	else
		new_value = ft_strdup("");
	new_var = malloc(sizeof(t_env));
	if (!new_var || !new_value)
	{
		free(new_value);
		return ;
	}
	new_var->variable = ft_strdup(name);
	new_var->value = new_value;
	new_var->next = *env;
	*env = new_var;
}

int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_env_vars(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->variable, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->variable);
		free(env->value);
		free(env);
		env = tmp;
	}
}
