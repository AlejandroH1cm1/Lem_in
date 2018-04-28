/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:22:28 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/27 20:31:06 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static int	verify_c(t_room *rooms, t_link *links)
{
	t_room	*tmp;
	int		count;

	count = 0;
	while (links)
	{
		tmp = find_room(rooms, links->ra);
		if (tmp->val == -1)
			count++;
		tmp = find_room(rooms, links->rb);
		if (tmp->val == -1)
			count++;
		links = links->next;
	}
	if (count == 0)
		return (0);
	return (1);
}

static int	connected(t_room *rooms, t_link *l1, t_link *l2)
{
	t_room	*tmp;

	if (l1 == l2)
		return (0);
	tmp = find_room(rooms, l1->ra);
	if (tmp->val != -1)
		if (!ft_strcmp(l2->rb, tmp->name) || !ft_strcmp(l2->ra, tmp->name))
			return (1);
	tmp = find_room(rooms, l1->rb);
	if (tmp->val != -1)
		if (!ft_strcmp(l2->rb, tmp->name) || !ft_strcmp(l2->ra, tmp->name))
			return (1);
	return (0);
}

static int	f_values(t_room *rooms, t_link *links)
{
	t_room	*tmp;
	int		count;

	count = 0;
	while (links)
	{
		tmp = find_room(rooms, links->ra);
		if (tmp->val == -2)
		{
			links->val = 1;
			links->next_p = links;
			count = 1;
		}
		tmp = find_room(rooms, links->rb);
		if (tmp->val == -2)
		{
			links->val = 1;
			links->next_p = links;
			count = 1;
		}
		links = links->next;
	}
	if (count == 0)
		return (0);
	return (1);
}

static void	calc_val(t_room *rooms, t_link *links, t_link *link)
{
	t_link	*tmp;

	tmp = links;
	while (tmp)
	{
		if (connected(rooms, link, tmp) && tmp->val != -1 && link != tmp)
		{
			if (tmp->val == 0)
			{
				link->val = -1;
				calc_val(rooms, links, tmp);
			}
			if ((tmp->val + 1 < link->val || link->val < 1) && tmp->val > 0)
			{
				link->next_p = tmp;
				link->val = tmp->val + 1;
			}
		}
		tmp = tmp->next;
	}
	if (link->val > 0)
		return ;
	link->val = 0;
}

int			pathing(t_room *rooms, t_link *links)
{
	t_link	*tmp;

	tmp = links;
	if (!f_values(rooms, links))
		return (0);
	while (tmp)
	{
		if (tmp->val < 1)
			calc_val(rooms, links, tmp);
		tmp = tmp->next;
	}
	calc_val(rooms, links, links);
	fix_path(links);
	apply_path(rooms, links);
	if (!verify_c(rooms, links))
		return (0);
	return (1);
}
