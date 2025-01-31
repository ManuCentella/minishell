/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:46:36 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:08 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

/*int	main(void)
{
	const char *original_str = "   \t  Trim this string \t   \n  ";
	const char *set = " \t\n";

	char *trimmed_str = ft_strtrim(original_str, set);

	if (trimmed_str == NULL)
	{
		perror("Error: No se pudo asignar memoria para la cadena trimmada.\n");
		return (EXIT_FAILURE);
	}
	printf("Original: \"%s\"\n", original_str);
	printf("Trimmada: \"%s\"\n", trimmed_str);
	free(trimmed_str);
	return (EXIT_SUCCESS);
}*/