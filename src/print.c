/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:00:40 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/29 09:44:16 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static void	print_link(t_link *link)
{
	ft_putstr(link->ra->name);
	ft_putchar('-');
	ft_putendl(link->rb->name);
}

static void	print_room(t_room *room, t_comm *comms)
{
	char	*tmp;

	if (room->val == -1)
		ft_putendl("##start");
	if (room->val == -2)
		ft_putendl("##end");
	ft_putstr(room->name);
	ft_putchar(' ');
	tmp = ft_itoa(room->x);
	ft_putstr(tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(room->y);
	ft_putchar(' ');
	ft_putendl(tmp);
	while (comms)
	{
		if (comms->room && !ft_strcmp(room->name, comms->room))
			ft_putendl(comms->co);
		comms = comms->next;
	}
	ft_strdel(&tmp);
}

void		print_farm(int ants, t_room *rooms, t_link *links, t_comm *comms)
{
	char	*tmp;
	t_comm	*tmp2;

	tmp = ft_itoa(ants);
	tmp2 = comms;
	while (tmp2)
	{
		if (!(tmp2->room))
			ft_putendl(tmp2->co);
		tmp2 = tmp2->next;
	}
	ft_putendl(tmp);
	ft_strdel(&tmp);
	while (rooms)
	{
		print_room(rooms, comms);
		rooms = rooms->next;
	}
	while (links)
	{
		print_link(links);
		links = links->next;
	}
	ft_putendl("");
}

void		print_move(int ant, t_room *room)
{
	char *tmp;

	tmp = ft_itoa(ant);
	ft_putchar('L');
	ft_putstr(tmp);
	ft_putchar('-');
	ft_putstr(room->name);
	ft_putchar(' ');
	ft_strdel(&tmp);
}
