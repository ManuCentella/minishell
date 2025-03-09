/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:16:34 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 20:50:52 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
 * expansion_main.c
 * 
 * Función principal que expande variables en los tokens:
 *  - Maneja \x01 (comillas simples) para no expandir.
 *  - Maneja \x02 (para que "\$" se convierta en '$' literal).
 *  - Expande variables del entorno con $VAR.
 *  - Expande $? con el código de salida.
 ******************************************************************************/

// 🔹 No expandimos variables dentro de comillas simples
// 🔹 Si hay `\$`, lo tratamos como texto
// Copia `$` literal
// Salta `$`
// 🔥 Expansión normal de variables
char	*expand_variable(char *arg, t_env *env, int exit_status)
{
	char	*expanded;
	int		i;

	i = 0;
	expanded = ft_strdup("");
	if (ft_strchr(arg, '\x01'))
		return (ft_strdup(arg));
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1] == '$')
		{
			append_char(&expanded, '$', &i);
			i++;
		}
		else if (arg[i] == '$')
			expand_dollar(&expanded, arg, &i, env, exit_status);
		else
			append_char(&expanded, arg[i], &i);
	}
	return (expanded);
}
