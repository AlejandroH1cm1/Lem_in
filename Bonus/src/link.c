/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 08:56:25 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/20 15:42:20 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

static t_link	*new(t_room *ra, t_room *rb)
{
	t_link *link;

	link = (t_link *)malloc(sizeof(t_link));
	link->ra = ra;
	link->rb = rb;
	link->val = 0;
	link->ant = 0;
	link->next = NULL;
	link->next_p = NULL;
	return (link);
}

void			add_l(t_link **link, t_room *ra, t_room *rb)
{
	t_link *tmp;

	tmp = *link;
	while (tmp)
	{
		if (tmp->ra == ra && tmp->rb == rb)
			return ;
		if (tmp->ra == rb && tmp->rb == ra)
			return ;
		tmp = tmp->next;
	}
	if (!*link)
	{
		*link = new(ra, rb);
		return ;
	}
	tmp = *link;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new(ra, rb);
}

void			rmv_l(t_link **link, t_room *ra, t_room *rb)
{
	t_link	*tmp;
	t_link	*tmp2;

	tmp = *link;
	tmp2 = tmp;
	while (tmp->ra != ra || tmp->rb != rb)
	{
		if (tmp->next == NULL)
			return ;
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp2->next = tmp->next;
	free(tmp);
	tmp = NULL;
}

void			dst_l(t_link **link)
{
	if (!*link)
		return ;
	if ((*link)->next)
		dst_l(&((*link)->next));
	free(*link);
	*link = NULL;
}

void			add_to_links(t_link **links, char *line, t_room *rooms)
{
	char	*ra;
	char	*rb;
	int		i;
	int		j;

	i = 0;
	while (line[i] != '-')
		i++;
	ra = ft_strnew(i);
	j = 0;
	ft_strncpy(ra, line, i);
	i++;
	while (line[i + j])
		j++;
	rb = ft_strnew(j);
	ft_strncpy(rb, &line[i], j);
	add_l(links, find_room(rooms, ra), find_room(rooms, rb));
	ft_strdel(&ra);
	ft_strdel(&rb);
}
