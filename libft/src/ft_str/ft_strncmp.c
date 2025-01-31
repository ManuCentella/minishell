/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:44 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:45:57 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*int main(void) {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, Universerff!";
    size_t n = 10;

    int result = ft_strncmp(str1, str2, n);

    if (result < 0) {
        printf("str1 es menor que str2\n");
    } else if (result > 0) {
        printf("str1 es mayor que str2\n");
    } else {
        printf("str1 es igual a str2\n");
    }

    return 0;
}*/