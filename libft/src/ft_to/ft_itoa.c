/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:16:32 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:24 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	num_digit(long num)
{
	int	cur;

	cur = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		cur++;
	while (num != 0)
	{
		num = num / 10;
		cur++;
	}
	return (cur);
}

char	*ft_itoa(int n)
{
	long	len;
	long	nl;
	char	*result;

	len = num_digit(n);
	nl = n;
	if (n < 0)
		nl *= -1;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = 0;
	if (nl == 0)
		result[0] = '0';
	else
	{
		while (len--, nl != 0)
		{
			result[len] = (nl % 10) + '0';
			nl = (nl - (nl % 10)) / 10;
		}
		if (n < 0)
			result[len] = '-';
	}
	return (result);
}

/*int	main(void)
{
	int numbers[] = {123, -456, 0, 7890, -12345};
	char *str;
	int i;

	for (i = 0; i < 5; i++)
	{
		str = ft_itoa(numbers[i]);
		printf("El número %d convertido a cadena es: %s\n", numbers[i], str);
		free(str); // No olvides liberar la memoria después de usarla
	}

	return (0);
}*/