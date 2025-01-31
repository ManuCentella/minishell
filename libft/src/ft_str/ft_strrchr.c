/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:14:27 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:04 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

/*int	main(void)
{
	char str[] = "Hola Mundo!";
	char c = 'o';
	char *res = ft_strrchr(str, c);
	if (res != NULL)
		printf("Ultima ocurrencia del caracter encontrado: %c\n", *res);
	else
		printf("Caracter no encontrado\n");
	return (0);
}*/