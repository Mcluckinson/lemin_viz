/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_viz.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:26:12 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 19:23:36 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEM_VIZ_H
# define LEM_VIZ_H

#include "SDL.h"
#include "libft/includes/libft.h"
#include "math.h"
#include <fcntl.h>///////////NOT RLY NEEDED DELETE ME PLZ

#define DEFAULT_WIDTH 1000
#define DEFAULT_HEIGHT 1000

typedef struct			s_room
{
	int					x;
	int					y;
	char				*name;
	struct s_room		*next;
}						t_room;

typedef struct 			s_link
{
	t_room 				*room1;
	t_room 				*room2;
	struct s_link		*next;
}						t_link;

typedef struct			s_step
{
	int 				ant_num;
	t_room 				*room;
	struct s_step		*next;
}						t_step;

typedef struct 			s_step_line
{
	char 				*line;
	struct s_step_line	*next;
	t_step 				*stepz;
}						t_step_line;

typedef struct			s_all_data
{
	int					bukashechki;
	t_room 				*all_rooms;
	t_link 				*all_links;
	t_step_line 		*all_steps;
	int 				w_height;
	int					w_width;
	t_room 				*start;
	t_room 				*end;
	char 				*courier;
	int 				del_me_fd;

}						t_all_data;

typedef struct 			s_sdl_things
{
	t_all_data			*map_data;
	SDL_Window			*win;
	SDL_Surface			*sur;
	SDL_Event			event;
	SDL_Surface			*ant;
	SDL_Surface			*floor;
	SDL_Surface			*check_surf;
	int 				width;
	int 				height;
	SDL_Renderer 		*renderer;
	Uint8				*wav_buffer;
	SDL_AudioDeviceID	device_id;
	SDL_Event 			*ev;

}						t_sdl_things;


/*
 * util functions
 */

int 	ft_error(const char *error);
int 	del_line_and_return(char *line, int ret);
int		is_all_digits(char *line);
void	del_str_arr(char **to_delete);
void		clear_sdl(t_all_data *data, t_sdl_things *thing);

/*
 *
 * read functions
 */

int 	read_ants(t_all_data *data);
int 	read_rooms(t_all_data *data);
int 	read_links(t_all_data *data);
int 	read_steps(t_all_data *data);
/*
 * validation
 */
int 	is_comment(char *line);
int 	split_bits(char *line, char c);
int 	is_link(char *line);
int 	is_step(char *step);
int 	is_room(char *line);
int 	valid_coords(t_room *room, t_room *list);
int 	duplicate_links(t_link *link, t_all_data *data);

/*
 * drawing
 */
int 		init_sdl(t_sdl_things *things);
void 	find_win_size(t_all_data *data, t_sdl_things *things);


/*
 * testing delete me
 */
void draw_test_window(t_sdl_things *things);

#endif