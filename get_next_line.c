/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:25:02 by dramos-j          #+#    #+#             */
/*   Updated: 2024/01/07 14:48:11 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	create_list(t_list **list, int fd)
{
	char	*content;
	int		size;

	if (!*list)
		return ;
	while (!newline(*list) || newline(*list) > 0)
	{
		if (!newline(*list))
			content = malloc(BUFFER_SIZE + 1);
		if (newline(*list) > 0)
			content = malloc(newline(*list) + 1);
		if (!content)
			return ;
		if (newline(*list) > 0)
			size = read(fd, content, newline(*list));
		if (!newline(*list))
			size = read(fd, content, BUFFER_SIZE);
		if (size < 0)
		{
			free(content);
			return ;
		}
		content[size] = '\0';
		ft_lstadd_back(list, ft_lstnew(content));
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	line = malloc(newline(list) + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, list->content, newline(list));
	line[newline(list)] = '\0';
	return (line);
}

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}