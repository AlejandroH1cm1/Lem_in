/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:41:50 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 20:01:11 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFDF_H
# define LIBFDF_H
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define BUFF_SIZE 2048
# define PI 3.14159265359

typedef struct		s_img
{
	char			*add;
	int				*img;
	int				bpp;
	int				line_size;
	int				endian;
}					t_img;

typedef struct		s_move
{
	int				turn;
	int				ant;
	struct s_room	*room;
	struct s_move	*next;
}					t_move;

typedef struct		s_room
{
	char			*name;
	char			*nr;
	int				x;
	int				y;
	int				val;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	t_room			*ra;
	t_room			*rb;
	int				val;
	int				ant;
	struct s_link	*next;
	struct s_link	*next_p;
}					t_link;

typedef struct		s_mlx
{
	int				turn;
	void			*mlx;
	void			*win;
	int				scale;
	t_room			*rooms;
	t_link			*links;
	t_move			*moves;
}					t_mlx;

t_img				room_img;
t_img				start_room_img;
t_img				end_room_img;

t_img				room_image(t_mlx *mlx, int color, int scale);
int					get_ants(void);
int					read_in(t_room **rooms, t_link **links, t_move **moves);
t_mlx				*create_mlx(t_room *rooms, t_link *links, t_move *moves);
void				dst_mlx(t_mlx *mlx);
void				draw_map(t_mlx *mlx);
int					ft_iswhitespace(char c);
void				mod_val(t_room *rooms, char *name, int val);
float				d(t_mlx *mlx, t_room *ra, t_room *rb);
void				add_r(t_room **room, char *name, int x, int y);
void				rmv_r(t_room **room, char *name);
void				dst_r(t_room **room);
void				add_l(t_link **link, t_room *ra, t_room *rb);
void				rmv_l(t_link **link, t_room *ra, t_room *rb);
void				dst_l(t_link **link);
void				add_m(t_move **move, int turn, int ant, t_room *room);
void				dst_m(t_move **move);
void				add_to_rooms(t_room **rooms, char *line, char **cm,
					int val);
void				add_to_links(t_link **links, char *line, t_room *rooms);
void				add_to_moves(t_move **moves, char *line, int *turn,
					t_room *rooms);
t_room				*find_room(t_room *rooms, char *name);


#endif
