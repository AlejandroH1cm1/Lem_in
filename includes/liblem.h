/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 16:45:26 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/19 18:21:59 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLEM_H
# define LIBLEM_H
# include "libft.h"
# define CHECK(x, y) if(x)return(y)

typedef struct		s_comm
{
	char			*co;
	struct s_comm	*next;
}					t_comm;

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

void				error(int er_no);
int					read_in(t_room **rooms, t_link **links, t_comm **comms);
void				add_to_comm(char *line, t_comm **commentaries);
void				dst_c(t_comm **comm);
void				add_r(t_room **room, char *name, int x, int y);
void				rmv_r(t_room **room, char *name);
void				dst_r(t_room **room);
t_room				*find_ant(t_room *rooms, int ant);
void				add_l(t_link **link, t_room *ra, t_room *rb);
void				rmv_l(t_link **link, t_room *ra, t_room *rb);
void				dst_l(t_link **link);
t_link				*has_prev(t_link *link, t_link *links);
void				add_to_links(t_link **links, char *line, t_room *rooms);
void				add_to_rooms(t_room **room, char *line, char **cm, int val);
void				mod_val(t_room *rooms, char *name, int val);
int					get_ants(t_comm **comms);
void				solve(int ants, t_room *rooms, t_link *links, t_comm *comm);
int					pathing(t_room *rooms, t_link *links);
int					room_exists(t_room *rooms, t_room *room);
t_room				*find_room(t_room *room, char *name);
void				print_farm(int ants, t_comm *comms);
int					get_v(t_room *r1, t_room *r2, t_link *links);
t_link				*connected_r(t_room *r1, t_room *r2, t_link *links);
void				fix_path(t_link *links);
void				apply_path(t_room *rooms, t_link *links);
t_room				*find_start(t_room *rooms);
int					find_small(t_room *rooms, t_link *links);
int					choose_r(int v1, int v2, int v, int a);
void				print_move(int ant, t_room *room, int i);
int					find_nx_ant(t_room *rooms, int ant);
t_room				*nx_ant(t_room *rmps, int *current);
int					alternate(t_link *links, t_room *rooms);

#endif
