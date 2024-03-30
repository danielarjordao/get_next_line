/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:25:02 by dramos-j          #+#    #+#             */
/*   Updated: 2024/03/30 16:19:03 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	create_list(t_list **list, int fd)
{
	char	*content;
	int		size;

	while (!newline(ft_lstlast(*list))) // enquanto não encontrar uma quebra de linha no final da lista
	{
		content = malloc(BUFFER_SIZE + 1); // aloca espaço para o conteúdo do tamanho do buffer
		if (!content) 
			return;
		size = read(fd, content, BUFFER_SIZE); // lê o conteúdo do arquivo, armazena em content e retorna o tamanho
		if (!size)
		{
			free(content);
			return ;
		}
		content[size] = '\0'; // adiciona o terminador de string
		ft_lstadd_back(list, ft_lstnew(content)); // adiciona o conteúdo lido no final da lista
	}
}

void	cpylist(char *dest, t_list *list) // copia o conteúdo da lista ligada para a string line
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
			dest[len] = list->content[i]; // copia o conteúdo da lista para a string
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
	if (NULL == rest)
		return ;
	last_node = ft_lstlast(*list); // pega o ultimo node da lista
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n') // enquanto nao encontrar uma quebra de linha
		++i;
	while (last_node->content[i]) // enquanto nao encontrar o final da string; 
	{
		i++;
		rest[k] = last_node->content[i]; // copia o restante da string para rest
		k++;
	}
	rest[k] = '\0';
	rest_node = ft_lstnew(rest); // cria um novo node com o conteúdo rest
	freemem(list, rest_node, rest); // libera a memória
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL; // cria uma lista ligada
	char			*firstline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &firstline, 0) < 0)  // se o arquivo nao existir, ou o buffer for menor que 0, ou se nao conseguir ler o arquivo
		return (NULL);
	create_list(&list, fd); // cria a lista com o conteúdo da primeira linha do arquivo
	if (list == NULL)
		return (NULL);
	firstline = malloc(listlen(list) + 1); // aloca espaço para a string line
	if (!firstline)
		return (NULL);
	cpylist(firstline, list); // copia o conteúdo da lista ligada para a string line
	clean_list(&list); // limpa a lista ligada
	return (firstline);
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