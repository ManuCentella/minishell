/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:28:08 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:46 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

/*int	main(void)
{
	char str1[50] = "Hola Mundo!";
	char str2[50] = "";
	printf("Antes de ft_memcpy: %s\n", str2);
	ft_memcpy(str2, str1, 11);
	printf("Despues de ft_memcpy: %s\n", str2);
	return (0);
}*/