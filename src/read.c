/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:02:05 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/29 09:44:40 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

static int	format_link(char *line)
{
	int i;
	int j;

	i = 0;
	while (ft_isalpha(line[i]) || ft_isdigit(line[i]))
		i++;
	if (line[i] != '-' || i == 0)
		return (0);
	i++;
	j = i;
	while (ft_isalpha(line[i]) || ft_isdigit(line[i]))
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
	if (line[0] == 'L')
		return (0);
	if (!ft_strncmp(line, "##", 2))
		return (3);
	if (!ft_strncmp(line, "#", 1))
		return (4);
	if (format_link(line))
		return (2);
	if (format_room(line))
		return (1);
	return (0);
}

int			read_in(t_room **rooms, t_link **links, t_comm **comms)
{
	char	*line;
	int		f;
	char	*cm;

	line = NULL;
	cm = NULL;
	while (get_next_line(0, &line))
	{
		if (!(f = format(line)))
			ft_strdel(&line);
		if (f == 0)
			return (-1);
		if (f == 1)
			add_to_rooms(rooms, line, &cm, 0);
		if (f == 2)
			add_to_links(links, line, *rooms);
		if (f == 3)
			ft_strdel(&cm);
		if (f == 3)
			cm = ft_strdup(line);
		if (f == 4)
			add_to_comm(line, comms, *rooms);
		ft_strdel(&line);
	}
	return (0);
}
