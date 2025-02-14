/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:25:32 by mcentell          #+#    #+#             */
/*   Updated: 2025/02/13 15:46:43 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			return (1);
		i++;
	}
	return (i);
}

int	execute_builtin_echo(t_cmd *cmd)
{
	char	**args;
	int		i;
	int		newline;

	newline = 1;
	args = cmd->args;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	i = check_option(args);
	if (i > 1)
		newline = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	pwd_builtin(t_data *data)
{
	if (!data->cwd)
	{
		ft_putendl_fd("pwd: error retrieving current directory", 2);
		return (1);
	}
	ft_putendl_fd(data->cwd, 1);
	return (0);
}

void	env_builtin(t_data *data)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (env->value) // ✅ Solo muestra variables con valor
		{
			ft_putstr_fd(env->variable, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
}
