/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:56:46 by mcentell          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:58 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	if (lst != NULL && *lst != NULL)
	{
		elem = *lst;
		elem = ft_lstlast(*lst);
		elem->next = new;
		return ;
	}
	*lst = new;
}

/*int main()
{
    // Crear algunos nodos para una lista enlazada de ejemplo
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));
    t_list *node3 = (t_list *)malloc(sizeof(t_list));

    // Inicializar el contenido de los nodos (pueden ser cualquier cosa)
    node1->content = (void *)1;
    node2->content = (void *)2;
    node3->content = (void *)3;

    // Establecer el siguiente nodo para cada nodo
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    // Imprimir la lista antes de agregar el nuevo nodo
    t_list *current = node1;
    printf("Lista antes de agregar el nuevo nodo:\n");
    while (current != NULL)
    {
        printf("%p -> ", current->content);
        current = current->next;
    }
    printf("NULL\n");

    // Crear un nuevo nodo para agregar al final de la lista
    t_list *newNode = (t_list *)malloc(sizeof(t_list));
    newNode->content = (void *)4;
    newNode->next = NULL;

    // Agregar el nuevo nodo al final de la lista utilizando ft_lstadd_back
    ft_lstadd_back(&node1, newNode);

    // Imprimir la lista después de agregar el nuevo nodo
    current = node1;
    printf("Lista después de agregar el nuevo nodo:\n");
    while (current != NULL)
    {
        printf("%p -> ", current->content);
        current = current->next;
    }
    printf("NULL\n");

    // Liberar la memoria de los nodos
    free(node1);
    free(node2);
    free(node3);
    free(newNode);

    return 0;
}*/