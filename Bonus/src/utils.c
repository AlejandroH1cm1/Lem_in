/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:31:38 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 19:06:05 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

int		ft_iswhitespace(char c)
{
	if ((c < 9 || c > 13) && c != 32)
		return (0);
	return (1);
}

void	mod_val(t_room *rooms, char *name, int val)
{
	if (val == 0)
		return ;
	while (ft_strcmp(rooms->name, name))
		rooms = rooms->next;
	rooms->val = val;
}

float	d(t_mlx *mlx, t_room *ra, t_room *rb)
{
	float	x;
	float	y;
	float	d;

	x = round(ra->x * mlx->scale + 200) -
		round(rb->x * mlx->scale + 200);
	y = round(ra->y * mlx->scale + 200) -
		round(rb->y * mlx->scale + 200);
	d = hypot(x, y);
	return (d);
}
