/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:15:11 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/24 16:44:42 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	process_quote_content(t_tokenizer *t, char quote, char **buffer, int *j)
{
	while (t->i < t->len && t->input[t->i] != quote)
	{
		if (quote == '\"' && t->input[t->i] == '\\')
			handle_escaped_chars(t, *buffer, j);
		else
			(*buffer)[(*j)++] = t->input[t->i++];
	}
	if (t->i >= t->len)
	{
		ft_putendl_fd("Error: unclosed quotes", 2);
		free(*buffer);
		*buffer = NULL;
	}
	else
	{
		t->i++;
	}
}

static char	*collect_quote_content(t_tokenizer *t, char quote, int *length)
{
	int		size;
	char	*buf;

	size = t->len - t->i + 1;
	buf = malloc(size);
	if (!buf)
	{
		t->i--;
		return (NULL);
	}
	t->i++;
	if (quote == '\"')
		t->inside_double_quotes = 1;
	process_quote_content(t, quote, &buf, length);
	if (quote == '\"')
		t->inside_double_quotes = 0;
	buf[*length] = '\0';
	return (buf);
}

void	handle_quotes(t_tokenizer *t, char quote)
{
	int		len;
	char	*buffer;
	char	*wrapped;

	len = 0;
	buffer = collect_quote_content(t, quote, &len);
	if (!buffer)
		return ;
	if (quote == '\'')
	{
		wrapped = ft_strjoin("\x01", buffer);
		if (wrapped)
		{
			add_token(t, wrapped, len + 1);
			free(wrapped);
		}
	}
	else
		add_token(t, buffer, len);
	free(buffer);
}

void	add_token(t_tokenizer *t, char *start, int length)
{
	char	**new_tokens;
	char	*dup_str;

	new_tokens = allocate_new_tokens(t);
	if (!new_tokens)
		return ;
	copy_existing_tokens(new_tokens, t->tokens, t->token_count);
	dup_str = ft_strndup(start, length);
	if (!dup_str)
	{
		perror("ft_strndup");
		free(new_tokens);
		return ;
	}
	new_tokens[t->token_count] = dup_str;
	new_tokens[t->token_count + 1] = NULL;
	free(t->tokens);
	t->tokens = new_tokens;
	t->token_count++;
}
