/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:42:31 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/20 16:43:42 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

void		add_m(t_move **move, int turn, int ant, t_room *room)
{
	t_move *tmp;

	if (!*move)
	{
		*move = (t_move *)malloc(sizeof(t_move));
		(*move)->turn = turn;
		(*move)->ant = ant;
		(*move)->room = room;
		(*move)->next = NULL;
		return ;
	}
	tmp = *move;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_move *)malloc(sizeof(t_move));
	tmp = tmp->next;
	tmp->turn = turn;
	tmp->ant = ant;
	tmp->room = room;
	tmp->next = NULL;
}

void		dst_m(t_move **move)
{
	if (!*move)
		return ;
	if ((*move)->next)
		dst_m((&(*move)->next));
	free(*move);
	*move = NULL;
}

void		add_to_moves(t_move **moves, char *line, int *turn, t_room *rooms)
{
	int		ant;
	int		i;
	int		j;
	t_room	*room;
	char	*aux;

	i = 0;
	while (line[i])
	{
		j = 0;
		ant = ft_atoi(&line[i + 1]);
		while (line[i] != '-')
			i++;
		while (line[i + 1 + j] && !ft_iswhitespace(line[i + 1 + j]))
			j++;
		aux = ft_strnew(j);
		ft_strncpy(aux, &line[i + 1], j);
		room = find_room(rooms, aux);
		add_m(moves, *turn, ant, room);
		ft_strdel(&aux);
		while (line[i] != 'L' && line[i])
			i++;
	}
	(*turn)++;
}
