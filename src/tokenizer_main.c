/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:15:28 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 19:58:26 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************
 * tokenizer_main.c
 * - Separa la entrada en tokens
 * - Maneja metacaracteres (|, <, >)
 * - Delega las comillas a tokenizer_quotes.c
 ******************************************************************************/
#include "minishell.h"

/* (3) handle_metacharacters: detecta <, >, <<, >>, | y tokeniza */
void	handle_metacharacters(t_tokenizer *t)
{
	int	start;

	start = t->i++;
	if ((t->input[start] == '<' && t->input[t->i] == '<')
		|| (t->input[start] == '>' && t->input[t->i] == '>'))
		t->i++;
	add_token(t, &t->input[start], t->i - start);
}

/* (4) process_next_token: decide si es comilla, metachar o texto normal */
// Buffer para procesar caracteres escapados
// 🔹 Detectar barra invertida y manejarla correctamente
void	process_next_token(t_tokenizer *t)
{
	char	buffer[256];
	int		j;

	if (t->input[t->i] == '\"' || t->input[t->i] == '\'')
	{
		handle_quotes(t, t->input[t->i]);
	}
	else if (ft_is_metachar(t->input[t->i]))
	{
		handle_metacharacters(t);
	}
	else
	{
		j = 0;
		while (t->i < t->len && !ft_isspace(t->input[t->i])
			&& !ft_is_metachar(t->input[t->i])
			&& t->input[t->i] != '\"'
			&& t->input[t->i] != '\'')
		{
			if (t->input[t->i] == '\\')
			{
				handle_escaped_chars(t, buffer, &j);
			}
			else
			{
				buffer[j++] = t->input[t->i++];
			}
		}
		buffer[j] = '\0';
		add_token(t, buffer, j);
	}
}

/* (5) tokenize_input: bucle principal */
char	**tokenize_input(char *input)
{
	t_tokenizer	t;

	t.input = input;
	t.i = 0;
	t.len = (int)strlen(input);
	t.tokens = NULL;
	t.token_count = 0;
	while (t.i < t.len)
	{
		skip_whitespace(&t);
		if (t.i >= t.len)
			break ;
		process_next_token(&t);
	}
	return (t.tokens);
}
