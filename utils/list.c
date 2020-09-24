/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 21:07:54 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/10 18:16:20 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list		*ft_lstnew(char *content)
{
	t_list	*newlst;

	newlst = (t_list *)malloc(sizeof(t_list));
	if (!newlst)
		return (0);
	newlst->content = content;
	newlst->next = 0;
	return (newlst);
}

void		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*cur;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = new;
}

int			ft_lstsize(t_list *lst)
{
	int		n;

	n = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}
