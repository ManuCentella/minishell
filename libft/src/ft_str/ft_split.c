/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:52:18 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:45:24 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	word_count(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	copy_word(char **dst, char const **src, char c)
{
	int	length;

	if (!dst || !src || !*src)
		return (-1);
	length = 0;
	while ((*src)[length] && (*src)[length] != c)
		length++;
	if (length < 0)
		return (-1);
	*dst = malloc(length + 1);
	if (*dst == NULL)
	{
		return (-1);
	}
	ft_memcpy(*dst, *src, length);
	(*dst)[length] = '\0';
	*src += length;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		wc;
	char	**result;

	wc = word_count(s, c);
	result = malloc((wc + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		while (*s == c)
			s++;
		if (copy_word(&result[i], &s, c) == -1)
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[wc] = NULL;
	return (result);
}

/*int main(void)
{
	char const *str;
	char c;
	char **result;
	int i;

	str = "Hola, cómo estás? Espero que estés bien.";
	c = ' ';
	result = ft_split(str, c);
	printf("Resultado:\n");
	for (i = 0; result[i] != NULL; i++)
	{
		printf("%s\n", result[i]);
	}
	return (0);
}*/
