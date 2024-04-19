/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:25:02 by dramos-j          #+#    #+#             */
/*   Updated: 2024/04/19 18:15:01 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		if (!size)
		{
			free(content);
			return (1);
		}
		if (size < 0)
		{
			free(content);
			return (2);
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

	if (!list)
		return (0);
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

	if (NULL == list)
		return ;
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
	if (rest == NULL)
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
	static t_list	*list = NULL;
	char			*line;
	int				testread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	testread = create_list(&list, fd);
	if (testread == 2 && list)
		clean_list(&list);
	if (list == NULL)
		return (NULL);
	line = malloc(listlen(list) + 1);
	if (!line)
		return (NULL);
	cpylist(line, list);
	clean_list(&list);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error");
		return (1);
	}
	next_line = get_next_line(fd);
	while (next_line)
	{
		count++;
		printf("[%d]: %s\n", count, next_line);
		free(next_line);
		next_line = get_next_line(fd);
		if (!next_line)
		{
			free (next_line);
			break ;
		}
	}
	close(fd);
	return (0);
}*/