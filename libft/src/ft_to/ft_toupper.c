/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:15:58 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:36 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

/*int	main(void)
{
	char c = 'a';
	printf("Antes de ft_toupper: %c\n", c);
	c = ft_toupper(c);
	printf("Despues de ft_toupper: %c\n", c);
	return (0);
}*/