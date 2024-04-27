/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:25:02 by dramos-j          #+#    #+#             */
/*   Updated: 2024/04/21 14:14:39 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	create_list(t_list **list, int fd)
{
	char	*content;
	int		size;

	while (!newline(ft_lstlast(*list)))
	{
		content = malloc(BUFFER_SIZE + 1);
		if (!content)
			return (1);
		size = read(fd, content, BUFFER_SIZE);
		if (size < 0 || !size)
		{
			free(content);
			if (size < 0)
				return (2);
			if (!size)
				return (1);
		}
		content[size] = '\0';
		ft_lstadd_back(list, ft_lstnew(content));
	}
	return (1);
}

int	listlen(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	cpylist(char *dest, t_list *list)
{
	int	len;
	int	i;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				dest[len] = '\n';
				len++;
				dest[len] = '\0';
				return ;
			}
			dest[len] = list->content[i];
			len++;
			i++;
		}
		list = list->next;
	}
	dest[len] = '\0';
}

void	clean_list(t_list **list)
{
	t_list	*last_node;
	t_list	*rest_node;
	int		i;
	int		k;
	char	*rest;

	rest = malloc(BUFFER_SIZE + 1);
	if (!rest)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i])
	{
		i++;
		rest[k] = last_node->content[i];
		k++;
	}
	rest[k] = '\0';
	rest_node = ft_lstnew(rest);
	freemem(list, rest_node, rest);
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*line;
	int				testread;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	testread = create_list(&list[fd], fd);
	if (testread == 2 && list[fd])
		clean_list(&list[fd]);
	if (!list[fd])
		return (NULL);
	line = malloc(listlen(list[fd]) + 1);
	if (!line)
		return (NULL);
	cpylist(line, list[fd]);
	clean_list(&list[fd]);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	int		fd2;
	char	*next_line;
	char	*next_line2;

	fd = open("test.txt", O_RDONLY);
	next_line = get_next_line(fd);
	if (fd < 0)
	{
		printf("%s", next_line);;
		return (1);
	}
	fd2 = open("test2.txt", O_RDONLY);
	next_line2 = get_next_line(fd2);
	if (fd2 < 0)
	{
		printf("%s", next_line2);
		return (1);
	}
	printf("\n\nFile1:\n\n");
	while (next_line)
	{
		printf("%s", next_line);
		free(next_line);
		next_line = get_next_line(fd);
	}
	printf("\n\nFile2:\n\n");
	while (next_line2)
	{
		printf("%s", next_line2);
		free(next_line2);
		next_line2 = get_next_line(fd2);
	}
	close(fd);
	close(fd2);
	return (0);
}*/