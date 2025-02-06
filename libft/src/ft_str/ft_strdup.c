/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:06:49 by mcentell          #+#    #+#             */
/*   Updated: 2025/02/03 14:52:08 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*int	main(void)
{
	char *src = "Hola, mundo!";
	char *copy = ft_strdup(src);

	if (copy == NULL)
	{
		printf("Error al asignar memoria.\n");
		return (1);
	}

	printf("Cadena original: %s\n", src);
	printf("Copia de la cadena: %s\n", copy);

	free(copy); // No olvides liberar la memoria asignada por malloc

	return (0);
}*/