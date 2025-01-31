/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:32:47 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:56 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len-- > 0)
		*(ptr++) = (unsigned char)c;
	return (b);
}

/*int	main(void)
{
	char str[50] = "Hola Mundo!";
	printf("Antes de ft_memset: %s\n", str);
	ft_memset(str + 5, '*', 5);
	printf("Despues de ft_memset: %s\n", str);
	return (0);
}*/
