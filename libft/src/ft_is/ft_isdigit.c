/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:09:30 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:48 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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

	if (ft_isdigit(c))
	{
		printf("%c Es un caracter numerico", c);
	}
	else
	{
		printf("%c No es un caracter numerico", c);
	}
	return (0);
}*/