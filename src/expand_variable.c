/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:34 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/24 19:29:04 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_expansion(char *arg, char **expanded,
		t_expansion_context *context)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1] == '$')
		{
			append_char(expanded, '$', &i);
			i++;
		}
		else if (arg[i] == '$')
			expand_dollar(expanded, arg, &i, context);
		else
			append_char(expanded, arg[i], &i);
	}
}

char	*expand_variable(char *arg, t_env *env, int exit_status)
{
	char				*expanded;
	t_expansion_context	context;

	context.env = env;
	context.exit_status = exit_status;
	expanded = ft_strdup("");
	if (ft_strchr(arg, '\x01'))
	{
		free(expanded);
		return (ft_strdup(arg));
	}
	process_expansion(arg, &expanded, &context);
	return (expanded);
}
