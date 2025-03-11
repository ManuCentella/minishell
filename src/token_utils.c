/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:15:33 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/11 12:37:59 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

void	skip_whitespace(t_tokenizer *t)
{
	while (t->i < t->len && ft_isspace(t->input[t->i]))
		t->i++;
}

char	**allocate_new_tokens(t_tokenizer *t)
{
	char	**new_tokens;

	new_tokens = malloc(sizeof(char *) * (t->token_count + 2));
	if (!new_tokens)
		perror("malloc");
	return (new_tokens);
}

void	copy_existing_tokens(char **new_tokens, char **old_tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_tokens[i] = old_tokens[i];
		i++;
	}
}
