/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:34:52 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:26 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*int main()
{
    // Crear algunos nodos para una lista enlazada de ejemplo
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));
    t_list *node3 = (t_list *)malloc(sizeof(t_list));

    // Inicializar el contenido de los nodos (pueden ser cualquier cosa)
    node1->content = NULL;
    node2->content = NULL;
    node3->content = NULL;

    // Establecer el siguiente nodo para cada nodo
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    // Calcular el tamaño de la lista utilizando ft_lstsize
    int size = ft_lstsize(node1);

    // Imprimir el resultado
    printf("El tamaño de la lista es: %d\n", size);

    // Liberar la memoria de los nodos
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/