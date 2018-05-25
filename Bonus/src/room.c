/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:43:22 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 19:06:02 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

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

void		add_to_rooms(t_room **rooms, char *line, char **cm, int val)
{
	char	*name;
	int		x;
	int		y;
	int		i;

	i = 0;
	while (line[i] != ' ')
		i++;
	name = ft_strnew(i);
	ft_strncpy(name, line, i);
	i++;
	x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	i++;
	y = ft_atoi(&line[i]);
	if (!ft_strcmp(*cm, "##start"))
		val = -1;
	if (!ft_strcmp(*cm, "##end"))
		val = -2;
	ft_strdel(cm);
	add_r(rooms, name, x, y);
	mod_val(*rooms, name, val);
	ft_strdel(&name);
}

t_room		*find_room(t_room *rooms, char *name)
{
	while (rooms)
	{
		if (!ft_strcmp(name, rooms->name))
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}
