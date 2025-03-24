/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:23 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/20 22:27:03 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_export_value(t_export_content *context, char *equal)
{
	char	*value;
	char	*next_val;

	value = ft_strdup(equal + 1);
	if (!value)
		return (NULL);
	if (*value == '\0' && context->cmd->args[context->index + 1])
	{
		free(value);
		next_val = context->cmd->args[context->index + 1];
		value = ft_strdup(next_val);
		if (!value)
			return (NULL);
		free(next_val);
		context->cmd->args[context->index + 1] = NULL;
	}
	return (value);
}

static int	handle_export_value(t_export_content *context, char *arg_copy,
		char *equal)
{
	char	*name;
	char	*value;
	int		has_error;

	*equal = '\0';
	name = arg_copy;
	value = get_export_value(context, equal);
	if (!value)
	{
		perror("strdup");
		return (1);
	}
	has_error = 0;
	if (!is_valid_var_name(name))
	{
		print_msg(context->data, "export: not a valid identifier", -1);
		has_error = 1;
	}
	else
	{
		set_env_var(&(context->data->env), name, value);
	}
	free(value);
	return (has_error);
}

static int	process_export_arg(t_data *data, t_cmd *cmd, int index)
{
	char				*equal;
	char				*arg_copy;
	int					has_error;
	t_export_content	context;

	has_error = 0;
	arg_copy = ft_strdup(cmd->args[index]);
	if (!arg_copy)
		return (print_msg(data, "export: malloc failed", -1), 1);
	equal = ft_strchr(arg_copy, '=');
	context.data = data;
	context.cmd = cmd;
	context.index = index;
	if (equal)
		has_error = handle_export_value(&context, arg_copy, equal);
	else if (!is_valid_var_name(arg_copy))
		has_error = (print_msg(data, "export: not a valid identifier", -1), 1);
	else
		set_env_var(&(data->env), arg_copy, NULL);
	free(arg_copy);
	return (has_error);
}

int	export_builtin(t_data *data, t_cmd *cmd)
{
	int	i;
	int	has_error;

	i = 1;
	has_error = 0;
	if (!cmd->args[1])
		return (print_env_vars(data->env), 0);
	while (cmd->args[i])
	{
		if (process_export_arg(data, cmd, i) == 0)
			i++;
		else
			break ;
	}
	return (has_error);
}
