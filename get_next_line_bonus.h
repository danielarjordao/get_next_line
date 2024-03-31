/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:40:38 by dramos-j          #+#    #+#             */
/*   Updated: 2024/03/31 14:30:33 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct t_list
{
	char			*content;
	struct t_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	create_list(t_list **list, int fd);
void	cpylist(char *dest, t_list *list);
void	clean_list(t_list **list);
int		newline(t_list *list);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		listlen(t_list *list);
void	freemem(t_list **list, t_list *clean_node, char *buf);

#endif