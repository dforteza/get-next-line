/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: difortez <difortez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 20:37:48 by difortez          #+#    #+#             */
/*   Updated: 2026/09/16 21:19:04 by difortez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*get_next_line(int fd)
{
	static t_list	*lst[MAX_FD];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	if (!ft_read_to_list(fd, &lst[fd]))
	{
		ft_free_list(&lst[fd]);
		return (NULL);
	}
	if (!lst[fd])
		return (NULL);
	line = ft_build_line(lst[fd]);
	if (!line)
	{
		ft_free_list(&lst[fd]);
		return (NULL);
	}
	ft_clean_list(&lst[fd]);
	return (line);
}
