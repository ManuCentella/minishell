/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:29 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/13 13:45:49 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int g_exit_status;

void expand_question_mark(char **expanded, int *i, int exit_status)
{
    (void)exit_status;  // ✅ Evita el warning de "unused parameter"

    char    *value;

    printf("DEBUG: Expandiendo $? con g_exit_status = %d\n", g_exit_status);  // 🚀 Depuración

    value = get_variable_value("?", NULL, g_exit_status); // ✅ Aseguramos que usa la variable global
    if (!value)
        return;

    *expanded = ft_strjoin_free(*expanded, value, 1);
    free(value);
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
	int		start;
	char	*var_name;

	start = *i;
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
		(*i)++;
	if (*i > start)
		var_name = ft_strndup(&arg[start], *i - start);
	else
		var_name = NULL;
	return (var_name);
}

void	append_expanded_value(char **expanded, char *value)
{
	char	*temp;

	if (*expanded && (*expanded)[ft_strlen(*expanded) - 1] == '/'
		&& value[0] == '/')
		temp = ft_strjoin_free(*expanded, value + 1, 1);
	else
		temp = ft_strjoin_free(*expanded, value, 1);
	*expanded = temp;
}

// Saltamos '$'
void expand_dollar(char **expanded, char *arg, int *i, t_expansion_context *context)
{
    char *var_name, *value, *temp;

    (*i)++;
    if (arg[*i] == '?')
        return (expand_question_mark(expanded, i, context->exit_status));
    if (ft_isdigit(arg[*i]))
        return ((void)(*i)++);

    var_name = extract_var_name(arg, i);
    if (!var_name)
        return (append_char(expanded, '$', i));

    value = get_variable_value(var_name, context->env, context->exit_status);
    free(var_name);
    temp = ft_strjoin(*expanded, value ? value : "");
    free(*expanded);
    if (value) free(value);
    *expanded = temp;
}
