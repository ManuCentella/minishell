/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:25:07 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/24 16:46:56 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_msg(t_data *data, const char *msg, int fd)
{
	(void)data;
	ft_putendl_fd((char *)msg, fd);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
