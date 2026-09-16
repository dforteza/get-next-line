/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: difortez <difortez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 20:35:05 by difortez          #+#    #+#             */
/*   Updated: 2026/09/16 12:08:56 by difortez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Devuelve 1 si el contenido de node tiene un '\n'; 0 si no o si es NULL. */
int	ft_has_newline(t_list *node)
{
	int	i;

	if (!node || !node->content)
		return (0);
	i = 0;
	while (node->content[i])
	{
		if (node->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* Devuelve el ultimo nodo de lst, o NULL si la lista esta vacia. */
t_list	*ft_last_node(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/* Crea un nodo con content y lo engancha al final de *lst.
** Devuelve 1 si va bien; 0 si falla malloc (content NO se libera aqui). */
int	ft_add_node(t_list **lst, char *content)
{
	t_list	*new;
	t_list	*last;

	if (!lst || !content)
		return (0);
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_last_node((*lst));
		last->next = new;
	}
	return (1);
}

/* Cuenta los caracteres de la lista hasta el '\n' incluido,
** o hasta el final si no hay '\n'. */
size_t	ft_line_len(t_list *lst)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			len++;
			if (lst->content[i] == '\n')
				return (len);
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

/* Libera todos los nodos y su contenido, y deja *lst a NULL. */
void	ft_free_list(t_list **lst)
{
	t_list	*temp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free((*lst));
		*lst = temp;
	}
}
