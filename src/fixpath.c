/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:16:18 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/28 01:01:47 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static int	d_b(t_link *link, t_link *links)
{
	t_link	*tmp;
	int		(d);

	d = 0;
	tmp = has_prev(link, links);
	while (tmp)
	{
		d++;
		tmp = has_prev(tmp, links);
	}
	return (d);
}

static void	apply_p_l(t_link *link)
{
	if (link->next_p && link != link->next_p)
		apply_p_l(link->next_p);
	if (!link->next_p)
	{
		link->val = 0;
		return ;
	}
	if (link->next_p->val == 0)
		link->val = 0;
}

static void	apply_p_r(t_link *l1, t_link *l2, t_room *rooms)
{
	t_room	*r;

	if (!ft_strcmp(l1->ra, l2->ra) || !ft_strcmp(l1->ra, l2->rb))
	{
		r = find_room(rooms, l1->rb);
		if (!r->nr)
			r->nr = ft_strdup(l1->ra);
	}
	if (!ft_strcmp(l1->rb, l2->ra) || !ft_strcmp(l1->rb, l2->rb))
	{
		r = find_room(rooms, l1->ra);
		if (!r->nr)
			r->nr = ft_strdup(l1->rb);
	}
}

void		apply_path(t_room *rooms, t_link *links)
{
	t_link	*tl;
	t_room	*tr;

	tl = links;
	tr = rooms;
	while (tr->val != -1)
		tr = tr->next;
	while (tl)
	{
		if (!ft_strcmp(tr->name, tl->ra) || !ft_strcmp(tr->name, tl->rb))
			apply_p_l(tl);
		tl = tl->next;
	}
	tl = links;
	while (tl)
	{
		if (tl->val != 0)
			apply_p_r(tl, tl->next_p, rooms);
		tl = tl->next;
	}
}

void		fix_path(t_link *links)
{
	t_link	*tmp;
	t_link	*tmp2;

	tmp = links;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp2->next_p == tmp->next_p && tmp != tmp->next_p
			&& tmp2 != tmp2->next_p && tmp->next_p != NULL)
			{
				if (d_b(tmp2, links) < d_b(tmp, links) && tmp2->val != 0)
					tmp->val = 0;
				if (d_b(tmp2, links) < d_b(tmp, links) && tmp2->val != 0)
					tmp->next_p = NULL;
				if (d_b(tmp, links) < d_b(tmp2, links) && tmp->val != 0)
					tmp2->val = 0;
				if (d_b(tmp, links) < d_b(tmp2, links) && tmp->val != 0)
					tmp2->next_p = NULL;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}