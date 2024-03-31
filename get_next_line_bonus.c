/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:25:02 by dramos-j          #+#    #+#             */
/*   Updated: 2024/03/31 14:56:40 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	create_list(t_list **list, int fd)
{
	char	*content;
	int		size;

	while (!newline(ft_lstlast(*list)))
	{
		content = malloc(BUFFER_SIZE + 1);
		if (!content)
			return ;
		size = read(fd, content, BUFFER_SIZE);
		if (!size)
		{
			free(content);
			return ;
		}
		content[size] = '\0';
		ft_lstadd_back(list, ft_lstnew(content));
	}
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
	static t_list	*list[FOPEN_MAX];
	char			*firstline;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, &firstline, 0) < 0)
		return (NULL);
	create_list(&list[fd], fd);
	if (list[fd] == NULL)
		return (NULL);
	firstline = malloc(listlen(list[fd]) + 1);
	if (!firstline)
		return (NULL);
	cpylist(firstline, list[fd]);
	clean_list(&list[fd]);
	return (firstline);
}
/*
int	main()
{
int		fd;
int		fd2;
char	*line;

fd = open("test.txt", O_RDONLY);
fd2 = open("test2.txt", O_RDONLY); 
line = get_next_line(fd);
printf("Line: %s", line);
line = get_next_line(fd2);
printf("Line: %s", line);
}*/