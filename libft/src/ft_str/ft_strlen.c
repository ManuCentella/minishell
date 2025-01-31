/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:10:16 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:45:50 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/*int	main(void)
{
	char	cadena[100];

	printf("introduce una cadena; ");
	fgets(cadena, 100, stdin);
	printf("La longitud de la cadena es: %d\n", ft_strlen(cadena) - 1);
	return (0);
}
*/