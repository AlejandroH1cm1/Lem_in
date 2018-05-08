/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alternate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 03:56:31 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/07 20:54:02 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static int		crossings(t_link *links, t_room *start, int *size, int *outs)
{
	int		res;
	t_link	*tmp;
	t_link	*tmp2;

	res = 0;
	tmp = links;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp2->next_p == tmp->next_p && tmp != tmp->next_p
			&& tmp2 != tmp2->next_p && tmp->next_p != NULL)
				res++;
			tmp2 = tmp2->next;
		}
		if (tmp->ra == start || tmp->rb == start)
			*outs = *outs + 1;
		tmp = tmp->next;
		*size = *size + 1;
	}
	return (res);
}

static	t_link	*get_rm(t_link *link, t_link *aux, int size)
{
	if (aux == link)
		return (aux);
	if (link->val > size)
	{
		link->val = 0;
		return (NULL);
	}
	if (!aux && link->val <= size)
		return (link);
	if (aux && link->val == size)
	{
		link->val = 0;
		return (aux);
	}
	return (link);
}

int				alternate(t_link *links, t_room *rooms)
{
	int		size;
	int		outs;
	t_room	*start;
	int		cross;
	t_link	*aux;

	size = 0;
	outs = 0;
	start = find_start(rooms);
	cross = crossings(links, start, &size, &outs);
	aux = NULL;
	if (cross > size / outs)
	{
		size = find_small(rooms, links);
		while (links)
		{
			if (links->ra == start || links->rb == start)
				aux = get_rm(links, aux, size);
			links = links->next;
		}
		return (1);
	}
	return (0);
}
