#include "minishell.h"

// Libera un array de strings generado por `ft_split()`
void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split) // Evita segfault si split es NULL
		return ;
	while (split[i])
	{
		free(split[i]); // Liberar cada string individual
		i++;
	}
	free(split); // Liberar el array
}

// Une dos strings y libera opcionalmente uno o ambos
char	*ft_strjoin_free(char *s1, const char *s2, int to_free)
{
	char	*result;
	size_t	len1 = 0, len2;

	len1 = 0, len2 = 0;
	if (!s1 && !s2) // Si ambos son NULL, devolver NULL
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
	if (to_free == 1 || to_free == 3) // Liberar s1
		free(s1);
	// No liberamos `s2` porque es `const char *`
	// Si necesitas liberar `s2`, debe ser un `char *`, no `const char *`
	return (result);
}

void print_msg(t_data *data, const char *msg, int fd)
{
    (void)data; // Si no lo usas, evita warnings
    ft_putendl_fd((char *)msg, fd); // Casting a (char *)
}
