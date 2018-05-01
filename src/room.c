/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:02:16 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/30 03:50:19 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

void		add_r(t_room **room, char *name, int x, int y)
{
	t_room *tmp;

	if (!*room)
	{
		*room = (t_room *)malloc(sizeof(t_room));
		(*room)->name = ft_strdup(name);
		(*room)->next = NULL;
		(*room)->x = x;
		(*room)->y = y;
		(*room)->val = 0;
		(*room)->nr = NULL;
		return ;
	}
	tmp = *room;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_room *)malloc(sizeof(t_room));
	tmp = tmp->next;
	tmp->name = ft_strdup(name);
	tmp->next = NULL;
	tmp->x = x;
	tmp->y = y;
	tmp->val = 0;
	tmp->nr = NULL;
}

void		rmv_r(t_room **room, char *name)
{
	t_room	*tmp;
	t_room	*tmp2;

	tmp = *room;
	tmp2 = tmp;
	while (ft_strcmp(tmp->name, name))
	{
		if (tmp->next == NULL)
			return ;
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp2->next = tmp->next;
	ft_strdel(&(tmp->name));
	ft_strdel(&(tmp->nr));
	free(tmp);
	tmp = NULL;
}

void		dst_r(t_room **room)
{
	if (!*room)
		return ;
	if ((*room)->next)
		dst_r(&((*room)->next));
	ft_strdel(&((*room)->name));
	ft_strdel(&((*room)->nr));
	free(*room);
	*room = NULL;
}

t_room		*find_start(t_room *rooms)
{
	while (rooms->val != -1)
		rooms = rooms->next;
	return (rooms);
}

t_room		*find_ant(t_room *rooms, int ant)
{
	while (rooms->val != ant)
	{
		rooms = rooms->next;
		if (!rooms)
			return (NULL);
	}
	return (rooms);
}
