/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 08:56:25 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/27 20:24:04 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

void		add_l(t_link **link, char *ra, char *rb)
{
	t_link *tmp;

	if (!*link)
	{
		*link = (t_link *)malloc(sizeof(t_link));
		(*link)->ra = ft_strdup(ra);
		(*link)->rb = ft_strdup(rb);
		(*link)->val = 0;
		(*link)->ant = 0;
		(*link)->next = NULL;
		(*link)->next_p = NULL;
		return ;
	}
	tmp = *link;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_link *)malloc(sizeof(t_link));
	tmp = tmp->next;
	tmp->ra = ft_strdup(ra);
	tmp->rb = ft_strdup(rb);
	tmp->val = 0;
	tmp->ant = 0;
	tmp->next = NULL;
	tmp->next_p = NULL;
}

void		rmv_l(t_link **link, char *ra, char *rb)
{
	t_link	*tmp;
	t_link	*tmp2;

	tmp = *link;
	tmp2 = tmp;
	while (ft_strcmp(tmp->ra, ra) || ft_strcmp(tmp->rb, rb))
	{
		if (tmp->next == NULL)
			return ;
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp2->next = tmp->next;
	free(tmp->ra);
	free(tmp->rb);
	free(tmp);
	tmp = NULL;
}

void		dst_l(t_link **link)
{
	if (!*link)
		return ;
	if ((*link)->next)
		dst_l(&((*link)->next));
	free((*link)->ra);
	free((*link)->rb);
	free(*link);
	*link = NULL;
}

t_link		*has_prev(t_link *link, t_link *links)
{
	while (links)
	{
		if (links->next_p == link)
			return (links);
		links = links->next;
	}
	return (NULL);
}
