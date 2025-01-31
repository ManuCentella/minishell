/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:52:10 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:15 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*elem;

	if (lst == NULL)
		return (NULL);
	elem = lst;
	while (elem->next != NULL)
		elem = elem->next;
	return (elem);
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

    // Obtener el último nodo utilizando ft_lstlast
    t_list *lastNode = ft_lstlast(node1);

    // Imprimir el resultado (puede ser NULL si la lista está vacía)
    if (lastNode != NULL)
        printf("El contenido del último nodo es: %p\n", lastNode->content);
    else
        printf("La lista está vacía\n");

    // Liberar la memoria de los nodos
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/