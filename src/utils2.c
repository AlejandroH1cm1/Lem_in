/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 22:54:29 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/30 05:24:08 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

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

int			get_v(t_room *r1, t_room *r2, t_link *links)
{
	t_link	*tmp;

	if (!r1 || !r2)
		return (-1);
	tmp = connected_r(r1, r2, links);
	return (tmp->val);
}

t_link		*connected_r(t_room *r1, t_room *r2, t_link *links)
{
	while (links)
	{
		if (r1 == links->ra && r2 == links->ra)
			if (links->val != 0)
				return (links);
		if (r1 == links->rb && r2 == links->rb)
			if (links->val != 0)
				return (links);
		if (r1 == links->rb && r2 == links->ra)
			if (links->val != 0)
				return (links);
		if (r1 == links->ra && r2 == links->rb)
			if (links->val != 0)
				return (links);
		links = links->next;
	}
	return (NULL);
}

int			find_small(t_room *rooms, t_link *links)
{
	int		v;

	v = 0;
	while (rooms->val != -1)
		rooms = rooms->next;
	while (links)
	{
		if (!ft_strcmp(links->ra->name, rooms->name)
		|| !ft_strcmp(links->rb->name, rooms->name))
			if ((links->val != 0 && links->val < v) || v == 0)
				v = links->val;
		links = links->next;
	}
	return (v);
}

int			choose_r(int v1, int v2, int v, int a)
{
	if (v2 == -1 && v1 == v)
		return (1);
	if (v2 == -1 && v1 - v <= a)
		return (1);
	if (v2 == -1)
		return (0);
	if (v1 == 1)
		return (1);
	if (v2 == 1)
		return (0);
	if (v1 <= v2)
		return (1);
	return (0);
}
