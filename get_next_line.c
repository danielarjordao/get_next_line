/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:25:02 by dramos-j          #+#    #+#             */
/*   Updated: 2024/03/24 17:02:48 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	return (0);
}

void	create_list(t_list **list, int fd)
{
	char	*content;
	int		size;

	while (!newline(ft_lstlast(*list))) // enquanto não encontrar uma quebra de linha
	{
		content = malloc(BUFFER_SIZE + 1);
		if (!content)
			return;
		size = read(fd, content, BUFFER_SIZE); // lê o arquivo
		if (!size)
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

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)  // testa se o arquivo foi aberto corretamente
		return (NULL);
	create_list(&list, fd); // cria a lista ligada
	if (list == NULL)
		return (NULL);
	line = malloc(listlen(list) + 1);
	if (!line)
		return (NULL);
	cpylist(line, list); // copia o conteúdo da lista ligada para a string line
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY); // O_RDONLY read only; abrir um arquivo para leitura
	line = get_next_line(fd); 
	printf("%s\n", line); 
}*/