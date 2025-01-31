/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:36:49 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:45:28 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

/*int	main(void)
{
	char str[] = "Hola Mundo!";
	char c = 'M';
	char *res = ft_strchr(str, c);
	if (res != NULL)
		printf("Caracter encontrado: %c\n", *res);
	else
		printf("Caracter no encontrado\n");
	return (0);
}*/