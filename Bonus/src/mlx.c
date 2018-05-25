/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:31:44 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 19:41:57 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

t_img		room_image(t_mlx *mlx, int color, int scale)
{
	t_img	image;
	int		x;
	int		y;

	image.img = mlx_new_image(mlx->mlx, scale / 2, scale / 2);
	image.bpp = 0;
	image.line_size = 0;
	image.endian = 0;
	image.add = mlx_get_data_addr(image.img, &image.bpp, &image.line_size,
				&image.endian);
	x = -1;
	y = -1;
	while (x++ < scale / 2 - 1)
	{
		*(int *)&image.add[(x * image.bpp / 8) + (0 * image.line_size)] = color;
		*(int *)&image.add[(x * image.bpp / 8) +
			((scale / 2 - 1) * image.line_size)] = color;
	}
	while (y++ < scale / 2 - 1)
	{
		*(int *)&image.add[(y * image.line_size)] = color;
		*(int *)&image.add[((scale / 2 - 1) * image.bpp / 8) +
			(y * image.line_size)] = color;
	}
	return (image);
}

void		dst_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	dst_r(&mlx->rooms);
	dst_l(&mlx->links);
	dst_m(&mlx->moves);
	exit(0);
}

t_mlx		*create_mlx(t_room *rooms, t_link *links, t_move *moves)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 1200, 1200, "FdF");
	mlx->scale = 100;
	mlx->turn = 0;
	mlx->rooms = rooms;
	mlx->links = links;
	mlx->moves = moves;
	return (mlx);
}
