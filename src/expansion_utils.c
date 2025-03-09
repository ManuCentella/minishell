/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:29 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 21:10:33 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/******************************************************************************
 * expansion_utils.c
 * 
 * Funciones auxiliares para la expansión de variables:
 *  - append_char: Agrega un solo carácter a una string.
 *  - get_variable_value: Obtiene el valor de una variable de entorno.
 *  - expand_dollar: Maneja la expansión de variables del entorno.
 *  - expand_question_mark: Maneja la expansión de $?.
 ******************************************************************************/

/* ************************************************************************** */
/*        append_char: agrega un solo carácter a la cadena destino            */
/* ************************************************************************** */
void	append_char(char **expanded, char c, int *i)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*expanded = ft_strjoin_free(*expanded, tmp, 1);
	(*i)++;
}

/* ************************************************************************** */
/*    get_variable_value: busca el valor de una variable en el entorno        */
/* ************************************************************************** */
// ✅ Devuelve NULL si la variable no existe
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

/* ************************************************************************** */
/*      expand_question_mark: Maneja el caso especial $?                      */
/* ************************************************************************** */
void	expand_question_mark(char **expanded, int *i, int exit_status)
{
	char	*value;

	value = get_variable_value("?", NULL, exit_status);
	*expanded = ft_strjoin_free(*expanded, value, 3);
	(*i)++;
}

/* ************************************************************************** */
/*  expand_dollar: Maneja expansión de variables normales y $?                */
/* ************************************************************************** */

void	handle_special_dollar(char **expanded, char *arg,
		int *i, int exit_status)
{
	if (arg[*i] == '?')
	{
		expand_question_mark(expanded, i, exit_status);
		return ;
	}
	if (ft_isdigit(arg[*i]))
	{
		append_char(expanded, '$', i);
		while (ft_isdigit(arg[*i]))
			append_char(expanded, arg[*i], i);
	}
}

char	*extract_var_name(char *arg, int *i)
{
	int	start;

	start = *i;
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
		(*i)++;
	return (*i > start) ? ft_strndup(&arg[start], *i - start) : NULL;
}

void	append_expanded_value(char **expanded, char *value)
{
	char	*temp;

	temp = (*expanded && (*expanded)[ft_strlen(*expanded) - 1] == '/'
			&& value[0] == '/') ? ft_strjoin_free(*expanded, value + 1, 1)
		: ft_strjoin_free(*expanded, value, 1);
	*expanded = temp;
}

// Saltamos '$'
void	expand_dollar(char **expanded, char *arg, int *i,
		t_env *env, int exit_status)
{
	char	*var_name;
	char	*value;

	(*i)++;
	handle_special_dollar(expanded, arg, i, exit_status);
	if (arg[*i] == '?' || ft_isdigit(arg[*i]))
		return ;
	var_name = extract_var_name(arg, i);
	if (!var_name)
		return (append_char(expanded, '$', i));
	value = get_variable_value(var_name, env, exit_status);
	free(var_name);
	if (!value)
		value = ft_strdup("");
	append_expanded_value(expanded, value);
	free(value);
}
