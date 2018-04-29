/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:22:28 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/29 10:03:05 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static int	verify_c(t_link *links)
{
	int		count;

	count = 0;
	while (links)
	{
		if (links->ra->val == -1)
			count++;
		if (links->rb->val == -1)
			count++;
		links = links->next;
	}
	if (count == 0)
		return (0);
	return (1);
}

static int	connected(t_link *l1, t_link *l2)
{
	if (l1 == l2)
		return (0);
	if (l1->ra->val != -1)
		if (l2->rb == l1->ra || l2->ra == l1->ra)
			return (1);
	if (l1->rb->val != -1)
		if (l2->rb == l1->rb || l2->ra == l1->rb)
			return (1);
	return (0);
}

static int	f_values(t_link *links)
{
	int		count;

	count = 0;
	while (links)
	{
		if (links->ra->val == -2)
		{
			links->val = 1;
			links->next_p = links;
			count = 1;
		}
		if (links->rb->val == -2)
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

static void	calc_val(t_link *links, t_link *link)
{
	t_link	*tmp;

	tmp = links;
	while (tmp)
	{
		if (connected(link, tmp) && tmp->val != -1 && link != tmp)
		{
			if (tmp->val == 0)
			{
				link->val = -1;
				calc_val(links, tmp);
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
	if (!f_values(links))
		return (0);
	while (tmp)
	{
		if (tmp->val < 1)
			calc_val(links, tmp);
		tmp = tmp->next;
	}
	calc_val(links, links);
	fix_path(links);
	apply_path(rooms, links);
	if (!verify_c(links))
		return (0);
	return (1);
}
