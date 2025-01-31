/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:12:21 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:01 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	pos;
	unsigned int	i;

	if (!*to_find)
		return ((char *)str);
	pos = 0;
	while (str[pos] != '\0' && (size_t)pos < len)
	{
		if (str[pos] == to_find[0])
		{
			i = 1;
			while (to_find[i] != '\0' && str[pos + i] == to_find[i]
				&& (size_t)(pos + i) < len)
				++i;
			if (to_find[i] == '\0')
				return ((char *)&str[pos]);
		}
		++pos;
	}
	return (0);
}

/*int	main(void)
{
	const char haystack[20] = "TutorialsPoint";
	const char needle[10] = "to";
	char *result;

	result = ft_strnstr(haystack, needle, 4);
	if (result != NULL)
		printf("La subcadena es: %s\n", result);
	else
		printf("La subcadena no se encontró\n");
	return (0);
}*/
