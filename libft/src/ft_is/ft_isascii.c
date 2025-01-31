/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:05:02 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:45 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*int	main(void)
{
	char c;

	printf("Introduce un caracter: ");
	scanf("%c", &c);

	if (ft_isascii(c))
	{
		printf("%c Es un caracter ascii", c);
	}
	else
	{
		printf("%c No es un caracter ascii", c);
	}
	return (0);
}*/