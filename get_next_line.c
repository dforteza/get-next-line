/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: difortez <difortez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 20:37:48 by difortez          #+#    #+#             */
/*   Updated: 2026/09/16 11:47:42 by difortez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Paso 2. Lee de fd y engancha cada trozo como nodo al final de *lst,
** hasta que el ultimo nodo tenga '\n' o read devuelva 0.
** Devuelve 1 si va bien; 0 si hay error (read -1 o malloc).
** La lista NO se libera aqui: la libera get_next_line si recibe 0. */
static int	ft_read_to_list(int fd, t_list **lst)
{
	char	*buffer;
	ssize_t	bytes;

	while (!ft_has_newline(ft_last_node(*lst)))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (0);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(buffer);
			if (bytes == -1)
				return (0);
			return (1);
		}
		buffer[bytes] = '\0';
		if (!ft_add_node(lst, buffer))
		{
			free(buffer);
			return (0);
		}
	}
	return (1);
}

/* Paso 4. Devuelve una cadena nueva con el texto de la lista
** hasta el '\n' incluido. NULL si falla malloc. */
static char	*ft_build_line(t_list *lst)
{
	char	*line;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_line_len(lst);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < len)
	{
		i = 0;
		while (lst->content[i] && j < len)
			line[j++] = lst->content[i++];
		lst = lst->next;
	}
	line[j] = '\0';
	return (line);
}

/* Paso 5a. Devuelve una cadena nueva con lo que hay tras el '\n' de content.
** NULL si no hay '\n', si no hay nada detras o si falla malloc. */
static char	*ft_get_leftover(char *content)
{
	char	*leftover;
	size_t	i;
	size_t	j;

	i = 0;
	while (content[i] != '\n' && content[i] != '\0')
		i++;
	if (!content[i] || !content[i + 1])
		return (NULL);
	j = i + 1;
	while (content[j])
		j++;
	leftover = (char *)malloc(sizeof(char) * (j - i));
	if (!leftover)
		return (NULL);
	j = 0;
	while (content[i + 1 + j])
	{
		leftover[j] = content[i + 1 + j];
		j++;
	}
	leftover[j] = '\0';
	return (leftover);
}

/* Paso 5b. Sustituye *lst por un nodo nuevo con el sobrante tras el '\n',
** o por NULL si no sobra nada. Libera la lista vieja. */
static void	ft_clean_list(t_list **lst)
{
	char	*leftover;

	leftover = ft_get_leftover(ft_last_node(*lst)->content);
	ft_free_list(lst);
	if (leftover)
	{
		if (!ft_add_node(lst, leftover))
			free(leftover);
	}
}

/* Devuelve la siguiente linea de fd (con su '\n' si lo tiene),
** o NULL si no queda nada o hay error. Pasos 1, 3 y 6. */
char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_read_to_list(fd, &lst))
	{
		ft_free_list(&lst);
		return (NULL);
	}
	if (!lst)
		return (NULL);
	line = ft_build_line(lst);
	if (!line)
	{
		ft_free_list(&lst);
		return (NULL);
	}
	ft_clean_list(&lst);
	return (line);
}
