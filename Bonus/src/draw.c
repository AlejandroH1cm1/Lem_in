/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:42:45 by aherrera          #+#    #+#             */
/*   Updated: 2018/06/04 13:21:15 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

static void		draw_moves(t_mlx *mlx, t_move *moves)
{
	char	*s;

	while (moves)
	{
		if (moves->turn == mlx->turn)
		{
			s = ft_itoa(moves->ant);
			mlx_string_put(mlx->mlx, mlx->win,
				moves->room->x * mlx->scale + 190,
				moves->room->y * mlx->scale + 190, 0xad060c, s);
			ft_strdel(&s);
		}
		moves = moves->next;
	}
}

static void		draw_rooms(t_mlx *mlx, t_room *rooms)
{
	int	p;

	p = 200 - mlx->scale / 4;
	room_img = room_image(mlx, 0xFFFFFF, mlx->scale);
	start_room_img = room_image(mlx, 0x67167a, mlx->scale);
	end_room_img = room_image(mlx, 0x0d5b2f, mlx->scale);
	while (rooms)
	{
		if (rooms->val > -1)
			mlx_put_image_to_window(mlx->mlx, mlx->win, room_img.img,
			rooms->x * mlx->scale + p, rooms->y * mlx->scale + p);
		else if (rooms->val == -1)
			mlx_put_image_to_window(mlx->mlx, mlx->win, start_room_img.img,
			rooms->x * mlx->scale + p, rooms->y * mlx->scale + p);
		else if (rooms->val == -2)
			mlx_put_image_to_window(mlx->mlx, mlx->win, end_room_img.img,
			rooms->x * mlx->scale + p, rooms->y * mlx->scale + p);
		mlx_string_put(mlx->mlx, mlx->win, rooms->x * mlx->scale + p - 12,
				rooms->y * mlx->scale + p - 12, 0x00e5ff, rooms->name);
		rooms = rooms->next;
	}
	mlx_destroy_image(mlx->mlx, room_img.img);
	mlx_destroy_image(mlx->mlx, start_room_img.img);
	mlx_destroy_image(mlx->mlx, end_room_img.img);
}

static void		draw_inst(t_mlx *mlx)
{
	int		i;
	char	*s;

	i = 0;
	while (i < 160)
	{
		if (i < 145)
			mlx_pixel_put(mlx->mlx, mlx->win, 25, 25 + i, 0x666633);
		mlx_pixel_put(mlx->mlx, mlx->win, 25 + i, 25, 0x666633);
		if (i < 145)
			mlx_pixel_put(mlx->mlx, mlx->win, 185, 25 + i, 0x666633);
		mlx_pixel_put(mlx->mlx, mlx->win, 25 + i, 170, 0x666633);
		i++;
	}
	mlx_string_put(mlx->mlx, mlx->win, 32, 25, 0x215277, "Arrows: move");
	mlx_string_put(mlx->mlx, mlx->win, 32, 40, 0x215277, "-,+ to zoom");
	mlx_put_image_to_window(mlx->mlx, mlx->win, start_room_img.img, 32, 65);
	mlx_put_image_to_window(mlx->mlx, mlx->win, end_room_img.img, 32, 95);
	mlx_string_put(mlx->mlx, mlx->win, 60, 70, 0x215277, "Start room");
	mlx_string_put(mlx->mlx, mlx->win, 60, 100, 0x215277, "End room");
	mlx_string_put(mlx->mlx, mlx->win, 32, 122, 0x215277, "A, S for turns");
	mlx_string_put(mlx->mlx, mlx->win, 32, 140, 0x215277, "Turn: ");
	s = ft_itoa(mlx->turn);
	mlx_string_put(mlx->mlx, mlx->win, 90, 140, 0xcb42f4, s);
	ft_strdel(&s);
}

static void		draw_line(t_mlx *mlx, t_room *ra, t_room *rb)
{
	float	*x;
	int		dis;

	dis = d(mlx, ra, rb);
	x = (float *)malloc(6 * sizeof(float));
	x[0] = round(ra->x * mlx->scale + 200);
	x[1] = round(ra->y * mlx->scale + 200);
	x[2] = (round(rb->x * mlx->scale + 200) - x[0]) / dis;
	x[3] = (round(rb->y * mlx->scale + 200) - x[1]) / dis;
	while (round(x[0]) != round(rb->x * mlx->scale + 200)
	|| round(x[1]) != round(rb->y * mlx->scale + 200))
	{
		if (x[0] <= 1200 && x[1] <= 1200 && x[0] >= 0 && x[1] >= 0)
			mlx_pixel_put(mlx->mlx, mlx->win, x[0], x[1], 0xa9611e);
		round(x[0]) != rb->x * mlx->scale + 200 ? x[0] += x[2] : 1;
		round(x[1]) != rb->y * mlx->scale + 200 ? x[1] += x[3] : 1;
	}
	free(x);
}

void			draw_map(t_mlx *mlx)
{
	t_link	*links;

	links = mlx->links;
	while (links)
	{
		draw_line(mlx, links->ra, links->rb);
		links = links->next;
	}
	draw_rooms(mlx, mlx->rooms);
	draw_moves(mlx, mlx->moves);
	start_room_img = room_image(mlx, 0x67167a, 50);
	end_room_img = room_image(mlx, 0x0d5b2f, 50);
	draw_inst(mlx);
	mlx_destroy_image(mlx->mlx, start_room_img.img);
	mlx_destroy_image(mlx->mlx, end_room_img.img);
}
