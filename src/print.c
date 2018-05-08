/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:00:40 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/07 20:39:41 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

void		print_farm(int ants, t_comm *comms)
{
	ft_putnbr(ants);
	ft_putchar('\n');
	while (comms)
	{
		ft_putendl(comms->co);
		comms = comms->next;
	}
	ft_putendl("");
}

void		print_move(int ant, t_room *room, int i)
{
	char *tmp;

	tmp = ft_itoa(ant);
	ft_putchar('L');
	ft_putstr(tmp);
	ft_putchar('-');
	ft_putstr(room->name);
	ft_putchar(' ');
	ft_strdel(&tmp);
	if (i == -2)
		ft_putchar('\n');
}
