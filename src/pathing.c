/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:22:28 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/30 18:34:26 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static int	verify_c(t_link *links)
{
	int		count;

	count = 0;
	while (links)
	{
		if (links->ra->val == -1 && links->val != 0)
			count++;
		if (links->rb->val == -1 && links->val != 0)
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
	if ((l1->ra->val == -2 && (l2->ra->val == -2 || l2->rb->val == -2))
	|| (l1->rb->val == -2 && (l2->ra->val == -2 || l2->rb->val == -2))
	|| (l1->ra->val == -1 && (l2->ra->val == -1 || l2->rb->val == -1))
	|| (l1->rb->val == -1 && (l2->ra->val == -1 || l2->rb->val == -1)))
		return (0);
	if (l2->rb == l1->ra || l2->ra == l1->ra)
		return (1);
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

static int	next_row(t_link *links, int row)
{
	t_link	*tmp;
	t_link	*tmp2;
	int		count;

	count = 0;
	tmp = links;
	while (tmp)
	{
		tmp2 = links;
		while (tmp2)
		{
			if (connected(tmp, tmp2) && tmp->val == 0 && tmp2->val == row - 1)
			{
				tmp->next_p = tmp2;
				tmp->val = row;
				count++;
				break ;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (count);
}

int			pathing(t_room *rooms, t_link *links)
{
	int		i;

	i = 2;
	if (!f_values(links))
		return (0);
	while (next_row(links, i) != 0)
		i++;
	if (!alternate(links, rooms))
		fix_path(links);
	apply_path(rooms, links);
	if (!verify_c(links))
		return (1);
	return (1);
}
