/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:43:20 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 19:41:29 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblb.h"

static void		move(t_room *room, int dir, int scale)
{
	while (room)
	{
		if (dir == 1)
			room->x -= scale;
		if (dir == 2)
			room->x += scale;
		if (dir == 3)
			room->y += scale;
		if (dir == 4)
			room->y -= scale;
		room = room->next;
	}
}

static int		deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_putnbr(key);
	if (key == 0 && mlx->turn > 0)
		mlx->turn--;
	if (key == 1)
		mlx->turn++;
	if (key >= 123 && key <= 126)
		move(mlx->rooms, key - 122, 1);
	if (key == 53)
		dst_mlx(mlx);
	if (key == 69)
		mlx->scale += 3;
	if (key == 78)
		mlx->scale -= 3;
	mlx_clear_window(mlx->mlx, mlx->win);
	draw_map(mlx);
	return (0);
}

int				main(void)
{
	t_mlx	*mlx;
	t_link	*links;
	t_room	*rooms;
	t_move	*moves;
	int		ants;

	rooms = NULL;
	links = NULL;
	moves = NULL;
	ants = get_ants();
	read_in(&rooms, &links, &moves);
	if (!links || !rooms || !moves)
	{
		printf("INVALID INPUT!\n");
		return (0);
	}
	mlx = create_mlx(rooms, links, moves);
	draw_map(mlx);
	mlx_key_hook(mlx->win, deal_key, (void *)mlx);
	mlx_loop(mlx->mlx);
	free(mlx);
	return (0);
}
