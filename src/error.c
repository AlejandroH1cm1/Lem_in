/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:06:04 by aherrera          #+#    #+#             */
/*   Updated: 2018/04/26 00:20:32 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblem.h"

void	error(int er_no)
{
	char	*line;

	while (get_next_line(0, &line))
		ft_strdel(&line);
	ft_putendl("");
	ft_putendl("***");
	if (er_no == -1)
		ft_putendl("No input");
	if (er_no == -2)
		ft_putendl("Specify a valid amount of ants!");
	if (er_no == -3)
		ft_putendl("Invalid input");
	if (er_no == -4)
		ft_putendl("Invalid links");
	if (er_no == -5)
		ft_putendl("Missing/double start and/or end");
	if (er_no == -6)
		ft_putendl("No path from beggining to end");
	ft_putendl("***");
	return ;
}
