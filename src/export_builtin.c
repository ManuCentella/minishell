/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:23 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 12:29:46 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*      handle_export_value: Procesa la asignación de valor en export        */
/* ************************************************************************** */
static int handle_export_value(t_data *data, char *arg_copy, char *equal, t_cmd *cmd, int index)
{
    char *value;
    int has_error = 0;

    *equal = '\0';  // Separamos la variable del valor
    value = ft_strdup(equal + 1);

    if (*value == '\0' && cmd->args[index + 1])
    {
        value = ft_strdup(cmd->args[index + 1]); // Tomar solo el siguiente argumento válido
        cmd->args[index + 1] = NULL; // 🔥 Evita que se procese nuevamente como argumento
    }


    if (!is_valid_var_name(arg_copy))
        has_error = (print_msg(data, "export: not a valid identifier", -1), 1);
    else
        set_env_var(&(data->env), arg_copy, value);

    free(value);
    return has_error;
}

/* ************************************************************************** */
/*  process_export_arg: Procesa cada argumento de export                     */
/* ************************************************************************** */
static int process_export_arg(t_data *data, t_cmd *cmd, int index)
{
    char *equal;
    char *arg_copy;
    int has_error = 0;


    arg_copy = ft_strdup(cmd->args[index]);
    if (!arg_copy)
        return (print_msg(data, "export: malloc failed", -1), 1);

    equal = ft_strchr(arg_copy, '=');
    if (equal)
        has_error = handle_export_value(data, arg_copy, equal, cmd, index);
    else if (!is_valid_var_name(arg_copy))
        has_error = (print_msg(data, "export: not a valid identifier", -1), 1);
    else
    {
        set_env_var(&(data->env), arg_copy, NULL);
    }

    free(arg_copy);
    return has_error;
}

/* ************************************************************************** */
/*  export_builtin: Implementación del comando export                        */
/* ************************************************************************** */
int export_builtin(t_data *data, t_cmd *cmd)
{
    int i;
    int has_error = 0;

    i = 1;
    if (!cmd->args[1]) // Si no hay argumentos, imprimimos variables de entorno
        return (print_env_vars(data->env), 0);

    while (cmd->args[i]) // Recorremos los argumentos correctamente
    {
        if (process_export_arg(data, cmd, i) == 0) // Solo avanza si no hay error
            i++;
        else
            break;  // Evitamos procesar el valor como si fuera otro argumento
    }
    return has_error;
}
