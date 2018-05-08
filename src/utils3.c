/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 00:33:45 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/07 21:24:55 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

int		find_nx_ant(t_room *rooms, int ant)
{
	int		aux;

	aux = ant;
	while (rooms)
	{
		if (rooms->val > ant && (aux == ant || rooms->val < aux))
			aux = rooms->val;
		rooms = rooms->next;
	}
	return (aux);
}

t_room	*nx_ant(t_room *rooms, int *current)
{
	t_room	*tmp;

	tmp = find_ant(rooms, find_nx_ant(rooms, *current));
	if (!tmp || *current == tmp->val)
	{
		*current = 0;
		return (NULL);
	}
	*current = tmp->val;
	return (tmp);
}
