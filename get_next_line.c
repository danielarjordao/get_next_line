/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:25:02 by dramos-j          #+#    #+#             */
/*   Updated: 2024/03/23 17:37:05 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while (list)
	{
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (i);
			i++;
		}		
		list = list->next;
	}
	return (0);
}

void	create_list(t_list **list, int fd)
{
	char	*content;
	int		size;

	while (!newline(*list)) // enquanto não encontrar uma quebra de linha
	{
		content = malloc(BUFFER_SIZE + 1);
		if (!content)
			return;
		size = read(fd, content, BUFFER_SIZE); // lê o arquivo
		if (size < 0)
		{
			free(content);
			return ;
		}
		content[size] = '\0';
		ft_lstadd_back(list, ft_lstnew(content)); // adiciona o conteúdo lido na lista ligada
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL; // cria uma lista ligada
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)  // testa se o arquivo foi aberto corretamente
		return (NULL);
	create_list(&list, fd); // cria a lista ligada
	if (list == NULL)
		return (NULL);
	line = malloc(newline(list) + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, list->content, newline(list));
	line[newline(list)] = '\0';
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY); // O_RDONLY read only; abrir um arquivo para leitura
	line = get_next_line(fd); 
	printf("%s\n", line); 
}*/
