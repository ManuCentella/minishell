/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:29 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/20 16:07:04 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	expand_question_mark(char **expanded, int *i, int exit_status)
{
	char	*value;

	(void)exit_status;
	value = get_variable_value("?", NULL, g_exit_status);
	if (!value)
		return ;
	*expanded = ft_strjoin_free(*expanded, value, 1);
	free(value);
	(*i)++;
}

void	handle_special_dollar(char **expanded, char *arg, int *i,
		int exit_status)
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

void	expand_dollar(char **expanded, char *arg, int *i,
		t_expansion_context *context)
{
	char	*var_name;
	char	*value;
	char	*temp;

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
	if (value)
		temp = ft_strjoin(*expanded, value);
	else
		temp = ft_strjoin(*expanded, "");
	free(*expanded);
	if (value)
		free(value);
	*expanded = temp;
}
