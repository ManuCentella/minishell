/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:11:02 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:22 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elt;

	elt = (t_list *)malloc(sizeof(*elt));
	if (!elt)
		return (NULL);
	elt->content = content;
	elt->next = NULL;
	return (elt);
}

/*int	main(void)
{
	char	*contenido;
	t_list	*nuevo_nodo;

	// Crear un nuevo nodo con contenido "Hola, mundo!"
	contenido = "Hola, mundo!";
	nuevo_nodo = ft_lstnew(contenido);
	// Verificar si la creación del nodo fue exitosa
	if (nuevo_nodo == NULL)
	{
		fprintf(stderr, "Error al crear el nodo.\n");
		return (1);
	}
	// Imprimir el contenido del nodo
	printf("Contenido del nodo: %s\n", (char *)nuevo_nodo->content);
	// Liberar la memoria asignada para el nodo
	free(nuevo_nodo);
	return (0);
}*/