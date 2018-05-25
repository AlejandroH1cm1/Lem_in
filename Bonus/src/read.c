/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:41:46 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/20 19:54:40 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

int			get_ants(void)
{
	char	*line;
	int		ants;

	line = NULL;
	get_next_line(0, &line);
	while (line[0] == '#')
	{
		ft_strdel(&line);
		get_next_line(0, &line);
	}
	ants = ft_atoi(line);
	ft_strdel(&line);
	return (ants);
}

static int	format_link(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i] != '-' && line[i])
		i++;
	if (line[i] != '-' || i == 0)
		return (0);
	i++;
	j = i;
	while (line[i])
		i++;
	if (line[i] == j || line[i] != '\0')
		return (0);
	return (1);
}

static int	format_room(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] != ' ' && line[i])
		i++;
	if (line[i] == j || line[i] != ' ')
		return (0);
	i++;
	j = i;
	while (ft_isdigit(line[i]) && line[i])
		i++;
	if (line[i] == j || line[i] != ' ')
		return (0);
	i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

static int	format(char *line)
{
	if (!ft_strncmp(line, "##", 2))
		return (4);
	if (line[0] == 'L')
		return (3);
	if (format_link(line))
		return (2);
	if (format_room(line))
		return (1);
	return (0);
}

int			read_in(t_room **rooms, t_link **links, t_move **moves)
{
	char	*line;
	int		f;
	char	*cm;
	int		turn;

	line = NULL;
	cm = NULL;
	turn = 1;
	while (get_next_line(0, &line))
	{
		if (!(f = format(line)))
			ft_strdel(&line);
		if (f == 1)
			add_to_rooms(rooms, line, &cm, 0);
		if (f == 2)
			add_to_links(links, line, *rooms);
		if (f == 3)
			add_to_moves(moves, line, &turn, *rooms);
		if (f == 4)
			ft_strdel(&cm);
		if (f == 4)
			cm = ft_strdup(line);
		ft_strdel(&line);
	}
	return (0);
}
