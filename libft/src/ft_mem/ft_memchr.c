/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:12:27 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:39 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char str[] = "Hola Mundo!";
	char c = 'd';
	char *res = ft_memchr(str, c, sizeof(str));
	if (res != NULL)
		printf("Caracter encontrado: %c\n", *res);
	else
		printf("Caracter no encontrado\n");
	return (0);
}*/