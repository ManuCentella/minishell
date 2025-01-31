/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:15:01 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:30 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

/*int main(void)
{
	char c = 'A';
	printf("Antes de ft_toupper: %c\n", c);
	c = ft_tolower(c);
	printf("Despues de ft_toupper: %c\n", c);
	return (0);
}*/