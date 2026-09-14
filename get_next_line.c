/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: difortez <difortez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 20:37:48 by difortez          #+#    #+#             */
/*   Updated: 2026/09/14 20:37:48 by difortez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Paso 2. Lee de fd y engancha cada trozo como nodo al final de *lst,
** hasta que el ultimo nodo tenga '\n' o read devuelva 0.
** Si hay error (read -1 o malloc), libera la lista y deja *lst a NULL. */
static void	ft_read_to_list(int fd, t_list **lst)
{
	(void)fd;
	(void)lst;
}

/* Paso 4. Devuelve una cadena nueva con el texto de la lista
** hasta el '\n' incluido. NULL si falla malloc. */
static char	*ft_build_line(t_list *lst)
{
	(void)lst;
	return (NULL);
}

/* Paso 5. Sustituye *lst por un nodo nuevo con el sobrante tras el '\n',
** o por NULL si no sobra nada. Libera la lista vieja. */
static void	ft_clean_list(t_list **lst)
{
	(void)lst;
}

/* Devuelve la siguiente linea de fd (con su '\n' si lo tiene),
** o NULL si no queda nada o hay error. Pasos 1, 3 y 6. */
char	*get_next_line(int fd)
{
	static t_list	*lst;

	(void)fd;
	(void)lst;
	(void)ft_read_to_list;
	(void)ft_build_line;
	(void)ft_clean_list;
	return (NULL);
}
