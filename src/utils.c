/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:50:00 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/17 16:38:33 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

int		get_ants(t_comm **comms)
{
	char	*line;
	int		ants;

	line = NULL;
	get_next_line(0, &line);
	if (line == NULL)
		ft_strdel(&line);
	if (line == NULL)
		return (-1);
	while (!ft_strncmp(line, "#", 1))
	{
		add_to_comm(line, comms);
		ft_strdel(&line);
		get_next_line(0, &line);
	}
	if (!ft_isdigitstr(line))
	{
		ft_strdel(&line);
		return (-2);
	}
	ants = ft_atoi(line);
	ft_strdel(&line);
	if (ants == 0)
		return (-2);
	return (ants);
}

void	mod_val(t_room *rooms, char *name, int val)
{
	if (val == 0)
		return ;
	while (ft_strcmp(rooms->name, name))
		rooms = rooms->next;
	rooms->val = val;
}

void	add_to_rooms(t_room **rooms, char *line, char **cm, int val)
{
	char	*name;
	int		x;
	int		y;
	int		i;

	i = 0;
	while (line[i] != ' ')
		i++;
	name = ft_strnew(i);
	ft_strncpy(name, line, i);
	i++;
	x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	i++;
	y = ft_atoi(&line[i]);
	if (!ft_strcmp(*cm, "##start"))
		val = -1;
	if (!ft_strcmp(*cm, "##end"))
		val = -2;
	ft_strdel(cm);
	add_r(rooms, name, x, y);
	mod_val(*rooms, name, val);
	ft_strdel(&name);
}

void	add_to_links(t_link **links, char *line, t_room *rooms)
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

int		room_exists(t_room *rooms, t_room *room)
{
	while (rooms != room)
	{
		if (!(rooms->next))
			return (0);
		rooms = rooms->next;
	}
	return (1);
}
