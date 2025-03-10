/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:23 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/10 21:13:26 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*      handle_export_value: Procesa la asignación de valor en export        */
/* ************************************************************************** */
// Separamos la variable del valor
// Tomar solo el siguiente argumento válido
// 🔥 Evita que se procese nuevamente como argumento
static int	handle_export_value(t_export_content *context, char *arg_copy,
		char *equal)
{
	char	*value;
	int		has_error;

	has_error = 0;
	*equal = '\0';
	value = ft_strdup(equal + 1);
	if (*value == '\0' && context->cmd->args[context->index + 1])
	{
		value = ft_strdup(context->cmd->args[context->index + 1]);
		context->cmd->args[context->index + 1] = NULL;
	}
	if (!is_valid_var_name(arg_copy))
		has_error = (print_msg(context->data,
					"export: not a valid identifier", -1), 1);
	else
		set_env_var(&(context->data->env), arg_copy, value);
	free(value);
	return (has_error);
}

/* ************************************************************************** */
/*  process_export_arg: Procesa cada argumento de export                     */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*  export_builtin: Implementación del comando export                        */
/* ************************************************************************** */
// Si no hay argumentos, imprimimos variables de entorno
// Recorremos los argumentos correctamente
// Solo avanza si no hay error
// Evitamos procesar el valor como si fuera otro argumento
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
