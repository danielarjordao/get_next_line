/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:37:59 by dramos-j          #+#    #+#             */
/*   Updated: 2024/03/30 15:03:25 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline(t_list *list)
{
	int	i;

	if (NULL == list)
		return (0);
	i = 0;
	while (list->content[i] && i < BUFFER_SIZE)
	{
		if (list->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)malloc(sizeof(t_list));
	if (!lstnew)
		return (0);
	lstnew->content = content;
	lstnew->next = 0;
	return (lstnew);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstlast;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lstlast = ft_lstlast(*lst);
	lstlast->next = new;
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

void	freemem(t_list **list, t_list *rest_node, char *rest) 
{
	t_list	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next; // salva o próximo node
		free((*list)->content);
		free(*list);
		*list = temp; // avança para o próximo node
	}
	*list = NULL; // reseta a lista
	if (rest_node->content[0])
		*list = rest_node; // se o conteudo do rest_node for diferente de vazio, ele adiciona o rest_node na lista
	else 
	{
		free(rest); 
		free(rest_node);
	}
}
