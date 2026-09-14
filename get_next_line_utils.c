/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: difortez <difortez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 20:35:05 by difortez          #+#    #+#             */
/*   Updated: 2026/09/14 20:35:56 by difortez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Devuelve 1 si el contenido de node tiene un '\n'; 0 si no o si es NULL. */
int	ft_has_newline(t_list *node)
{
	(void)node;
	return (0);
}

/* Devuelve el ultimo nodo de lst, o NULL si la lista esta vacia. */
t_list	*ft_last_node(t_list *lst)
{
	(void)lst;
	return (NULL);
}

/* Crea un nodo con content y lo engancha al final de *lst.
** Devuelve 1 si va bien; 0 si falla malloc (content NO se libera aqui). */
int	ft_add_node(t_list **lst, char *content)
{
	(void)lst;
	(void)content;
	return (0);
}

/* Cuenta los caracteres de la lista hasta el '\n' incluido,
** o hasta el final si no hay '\n'. */
size_t	ft_line_len(t_list *lst)
{
	(void)lst;
	return (0);
}

/* Libera todos los nodos y su contenido, y deja *lst a NULL. */
void	ft_free_list(t_list **lst)
{
	(void)lst;
}
