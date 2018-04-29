/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:16:50 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/29 10:05:20 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

int	main(void)
{
	int		ants;
	t_link	*links;
	t_room	*rooms;
	t_comm	*comms;

	rooms = NULL;
	links = NULL;
	comms = NULL;
	ants = get_ants(&comms);
	if (ants < 0)
		error(ants);
	if (ants < 0)
		return (0);
	if (read_in(&rooms, &links, &comms) || !rooms || !links)
		error(-3);
	else
		solve(ants, rooms, links, comms);
	dst_l(&links);
	dst_r(&rooms);
	dst_c(&comms);
	return (0);
}
