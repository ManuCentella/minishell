/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:22:30 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:43 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr2;

	if (n == 0)
		return (0);
	ptr = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (*ptr == *ptr2 && ++i < n)
	{
		ptr++;
		ptr2++;
	}
	return ((int)(*ptr - *ptr2));
}

/*int	main(void)
{
	char str1[] = "Hola Mndo!";
	char str2[] = "Hola Mundo!";
	int res = ft_memcmp(str1, str2, sizeof(str1));
	if (res < 0)
		printf("str1 es menor que str2\n");
	else if (res > 0)
		printf("str1 es mayor que str2\n");
	else
		printf("str1 es igual a str2\n");
	return (0);
}*/