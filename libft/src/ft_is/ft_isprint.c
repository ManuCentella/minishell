/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:11:46 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:53 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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

	if (ft_isprint(c))
	{
		printf("%c Es un caracter imprimible", c);
	}
	else
	{
		printf("%c No es un caracter imprimible", c);
	}
	return (0);
}*/