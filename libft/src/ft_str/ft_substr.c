/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:47:33 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:12 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	str_len;

	if (!s)
		return (0);
	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_strdup(""));
	else if (str_len - start < len)
		len = str_len - start;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

/*int main(void) 
{
	const char *s = "Hola, mundo!";
	unsigned int start = 6;
	size_t len = 5;

	char *substring = ft_substr(s, start, len);

	if (substring) {
		printf("La subcadena es: %s\n", substring);
		free(substring);
	} else {
		printf("Hubo un error al obtener la subcadena.\n");
	}

	return 0;
}*/