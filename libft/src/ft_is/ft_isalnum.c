/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:57:54 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:37 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z'))
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
	if (ft_isalnum(c))
	{
		printf("%c Es un caracter alfanumerico", c);
	}
	else
	{
		printf("%c No es un caracter alfanumerico", c);
	}
	return (0);
}*/
