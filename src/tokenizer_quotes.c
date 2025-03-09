/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:15:11 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 21:46:51 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
 * tokenizer_quotes.c
 * - Maneja comillas simples y dobles
 * - handle_escaped_chars para \ dentro de comillas dobles
 ******************************************************************************/

/* (1) handle_escaped_chars: \" -> ", \\ -> \, \$ -> \x02 */
// 🔹 Comillas dobles o barra invertida escapada
// Salta el `\` y el carácter escapado
// 🔹 Si es `\$`, guardamos `\` y `$` como texto
// Copia la barra invertida
// Copia el `$` normal, sin expansión
// Salta el `\` y el `$`
// Copia la barra invertida
// Avanza una posición
void	handle_escaped_chars(t_tokenizer *t, char *buffer, int *j)
{
	char	next;

	next = t->input[t->i + 1];
	if (next == '\"' || next == '\\')
	{
		buffer[(*j)++] = next;
		t->i += 2;
	}
	else if (next == '$')
	{
		buffer[(*j)++] = '\\';
		buffer[(*j)++] = '$';
		t->i += 2;
	}
	else
	{
		buffer[(*j)++] = '\\';
		t->i++;
	}
}

/* (3) handle_quotes: maneja comillas simples y dobles */
// 🔹 Activamos modo comillas dobles
// 🔹 Desactivamos modo comillas dobles

void	handle_quotes(t_tokenizer *t, char quote)
{
	int		j;
	int		size;
	char	*buffer;

	j = 0;
	size = t->len - t->i + 1;
	buffer = malloc(size);
	t->i++;
	if (!buffer)
		return ;
	if (quote == '\"')
		t->inside_double_quotes = 1;
	while (t->i < t->len && t->input[t->i] != quote)
	{
		if (quote == '\"' && t->input[t->i] == '\\')
			handle_escaped_chars(t, buffer, &j);
		else
			buffer[j++] = t->input[t->i++];
	}
	if (t->i >= t->len)
	{
		fprintf(stderr, "Error: comillas sin cerrar\n");
		free(buffer);
	}
	else
		t->i++;
	buffer[j] = '\0';
	if (quote == '\'')
		add_token(t, ft_strjoin("\x01", buffer), j + 1);
	else
		add_token(t, buffer, j);
	if (quote == '\"')
		t->inside_double_quotes = 0;
	free(buffer);
}

void	add_token(t_tokenizer *t, char *start, int length)
{
	char	**new_tokens;

	new_tokens = allocate_new_tokens(t);
	if (!new_tokens)
		return ;
	copy_existing_tokens(new_tokens, t->tokens, t->token_count);
	new_tokens[t->token_count] = strndup(start, length);
	if (!new_tokens[t->token_count])
	{
		perror("strndup");
		free(new_tokens);
		return ;
	}
	new_tokens[t->token_count + 1] = NULL;
	free(t->tokens);
	t->tokens = new_tokens;
	t->token_count++;
}
