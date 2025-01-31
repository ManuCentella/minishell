/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:56:27 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:33 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n-- > 0)
		*(ptr++) = 0;
}

/*int	main(void)
{
	char str[50] = "Hola Mundo!";
	printf("Antes de ft_bzero: %s\n", str);
	ft_bzero(str + 5, 5);
	printf("Despues de ft_bzero: %s\n", str);
	return (0);
}*/