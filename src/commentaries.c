/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commentaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 01:53:19 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/28 01:53:20 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

void		add_to_comm(char *line, t_comm **commentaries, t_room *rooms)
{
	t_comm *tmp;

	if (rooms)
		while (rooms->next)
			rooms = rooms->next;
	if (!*commentaries)
	{
		(*commentaries) = (t_comm *)malloc(sizeof(t_comm));
		(*commentaries)->co = ft_strdup(line);
		(*commentaries)->room = NULL;
		if (rooms)
			(*commentaries)->room = ft_strdup(rooms->name);
		(*commentaries)->next = NULL;
		return ;
	}
	tmp = *commentaries;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_comm *)malloc(sizeof(t_comm));
	tmp = tmp->next;
	tmp->co = ft_strdup(line);
	(*commentaries)->room = NULL;
	if (rooms)
		tmp->room = ft_strdup(rooms->name);
	tmp->next = NULL;
}

void		dst_c(t_comm **comm)
{
	if (!*comm)
		return ;
	if ((*comm)->next)
		dst_c(&((*comm)->next));
	ft_strdel(&((*comm)->co));
	ft_strdel(&((*comm)->room));
	free(*comm);
	*comm = NULL;
}
