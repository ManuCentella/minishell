/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:15:28 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/24 16:41:07 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_metacharacters(t_tokenizer *t)
{
	int	start;

	start = t->i++;
	if ((t->input[start] == '<' && t->input[t->i] == '<')
		|| (t->input[start] == '>' && t->input[t->i] == '>'))
		t->i++;
	add_token(t, &t->input[start], t->i - start);
}

void	extract_token(t_tokenizer *t, char *buffer)
{
	int	j;

	j = 0;
	while (t->i < t->len && !ft_isspace(t->input[t->i])
		&& !ft_is_metachar(t->input[t->i]) && t->input[t->i] != '\"'
		&& t->input[t->i] != '\'')
	{
		if (t->input[t->i] == '\\')
			handle_escaped_chars(t, buffer, &j);
		else
			buffer[j++] = t->input[t->i++];
	}
	buffer[j] = '\0';
	add_token(t, buffer, j);
}

void	process_next_token(t_tokenizer *t)
{
	char	buffer[256];

	if (t->input[t->i] == '\"' || t->input[t->i] == '\'')
		handle_quotes(t, t->input[t->i]);
	else if (ft_is_metachar(t->input[t->i]))
		handle_metacharacters(t);
	else
		extract_token(t, buffer);
}

char	**tokenize_input(char *input)
{
	t_tokenizer	t;

	t.input = input;
	t.i = 0;
	t.len = (int)ft_strlen(input);
	t.tokens = NULL;
	t.token_count = 0;
	t.inside_double_quotes = 0;
	while (t.i < t.len)
	{
		skip_whitespace(&t);
		if (t.i >= t.len)
			break ;
		process_next_token(&t);
	}
	return (t.tokens);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}
