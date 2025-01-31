/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:18 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:45:42 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	res_d;
	unsigned int	res_s;

	i = ft_strlen(dest);
	j = 0;
	res_d = ft_strlen(dest);
	res_s = ft_strlen(src);
	if (size <= res_d)
		return (res_s + size);
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (res_d + res_s);
}

/*int	main(void)
{
	char dest[20] = "Hello";
	char src[] = " World";
	unsigned int size = sizeof(dest);

	unsigned int total_length = ft_strlcat(dest, src, size);

	printf("Concatenated string: %s\n", dest);
	printf("Total length: %u\n", total_length);

	return (0);
}*/