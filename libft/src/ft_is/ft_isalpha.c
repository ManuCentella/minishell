/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:55:15 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:41 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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
	char	c;

	printf("introduzca un caracter: ");
	scanf("%c", &c);
	if (ft_is_alpha(c))
	{
		printf("%c es un caracter alfabetico.\n", c);
	}
	else
	{
		printf("%c no es un caracter alfabetico.\n", c);
	}
	return (0);
}*/
