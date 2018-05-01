/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 23:02:51 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/30 18:39:56 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static int	send_try(int ants, t_room *rooms, t_link *links, int *sent)
{
	t_room	*aux;
	t_room	*tmp;
	t_room	*s;
	int		v;

	s = find_start(rooms);
	v = find_small(rooms, links);
	while (*sent < ants)
	{
		tmp = rooms;
		aux = NULL;
		while (tmp)
		{
			if (connected_r(s, tmp, links) && (tmp->val == 0 || tmp->val == -2))
				if (choose_r(get_v(s, tmp, links), get_v(s, aux, links), v,
						ants - *sent))
					aux = tmp;
			tmp = tmp->next;
		}
		CHECK(!aux, 0);
		*sent = *sent + 1;
		(aux->val != -2) ? aux->val = *sent : 1;
		print_move(*sent, aux, aux->val);
	}
	return (aux->val);
}

static void	send_ants(int ants, t_room *rooms, t_link *links, int recv)
{
	int		sent;
	int		current;
	t_room	*tmp;

	sent = 0;
	current = 0;
	while (recv < ants)
	{
		if (sent > 0)
			current = find_nx_ant(rooms, 0) - 1;
		while (current < sent && recv < ants)
		{
			tmp = nx_ant(rooms, &current);
			tmp->val = 0;
			tmp = find_room(rooms, tmp->nr);
			if (tmp->val != -2)
				tmp->val = current;
			else
				recv++;
			print_move(current, tmp, 0);
		}
		if (sent < ants && send_try(ants, rooms, links, &sent) == -2)
			recv = ants;
		ft_putchar('\n');
	}
}

static int	validate(t_room *rooms, t_link *links)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (links)
	{
		if (!room_exists(rooms, links->ra) || !room_exists(rooms, links->rb))
			return (-4);
		links = links->next;
	}
	while (rooms)
	{
		if (rooms->val == -1)
			start++;
		if (rooms->val == -2)
			end++;
		if (find_room(rooms->next, rooms->name))
			return (-7);
		rooms = rooms->next;
	}
	if (start != 1 || end != 1)
		return (-5);
	return (0);
}

void		solve(int ants, t_room *rooms, t_link *links, t_comm *comms)
{
	int		r;

	r = validate(rooms, links);
	if (r != 0)
		error(r);
	if (r != 0)
		return ;
	r = pathing(rooms, links);
	if (r == 0)
		error(-6);
	if (r == 0)
		return ;
	print_farm(ants, rooms, links, comms);
	send_ants(ants, rooms, links, 0);
}
