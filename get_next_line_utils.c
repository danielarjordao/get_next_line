/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:37:59 by dramos-j          #+#    #+#             */
/*   Updated: 2024/03/24 16:12:53 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline(t_list *list)
{
	int	i;
	
	if (list == NULL)  
		return (0);
	i = 0;
	while (list->content[i])
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

void	cpylist(char *dest, t_list *list)
{
	int	i;
	int	len;

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
				dest[len++] = '\n';
				dest[len] = '\0';
				return ;
			}
			dest[len++] = list->content[i++];
		}
		list = list->next;
	}
	dest[len] = '\0';
}
