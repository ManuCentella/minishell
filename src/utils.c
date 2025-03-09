/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:25:07 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 19:41:21 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Libera un array de strings generado por `ft_split()`
// Evita segfault si split es NULL
// Liberar cada string individual
void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// Une dos strings y libera opcionalmente uno o ambos
// Si ambos son NULL, devolver NULL
// No liberamos `s2` porque es `const char *`
// Si necesitas liberar `s2`, debe ser un `char *`, no `const char *`
char	*ft_strjoin_free(char *s1, const char *s2, int to_free)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = strlen(s1);
	if (s2)
		len2 = strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	if (s1)
		strcpy(result, s1);
	if (s2)
		strcat(result, s2);
	if (to_free == 1 || to_free == 3)
		free(s1);
	return (result);
}

// Si no lo usas, evita warnings
// Casting a (char *)
void	print_msg(t_data *data, const char *msg, int fd)
{
	(void)data;
	ft_putendl_fd((char *)msg, fd);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
