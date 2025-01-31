/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:51:44 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:36 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*int	main(void)
{
	int	*arr;

	arr = (int *)ft_calloc(5, sizeof(int));
	if (!arr)
	{
		printf("Failed to allocate memory\n");
		return (1);
	}
	for (int i = 0; i < 5; i++)
	{
		printf("%d ", arr[i]);
	}
	free(arr);
	return (0);
}*/