/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_viz.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:26:12 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 16:03:06 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_VIZ_H
# define LEM_VIZ_H

//#include "SDL.h"
#include "../SDL2/SDL2.framework/Headers/SDL.h"
#include "../SDL2/SDL2_image.framework/Headers/SDL_image.h"
#include "../libft/libft.h"
#include "math.h"
#include <stdbool.h>
#include <limits.h>
#include <fcntl.h>///////////NOT RLY NEEDED DELETE ME PLZ
#include <pthread.h>

#define DEFAULT_WIDTH 1366
#define DEFAULT_HEIGHT 768
#define THREAD_NUM 8

#define MODIFIER_X 2
#define MODIFIER_Y 20
#define BLUR_EXTENT 3

typedef struct		s_xy
{
	int				x;
	int				y;
	int 			width;
	int 			height;
}					t_xy;

typedef struct			s_room
{
	int					x;
	int					y;
	int 				level;
	char				*name;
	int					is_part_of_path;
	struct s_room		*next;
}						t_room;

typedef struct 			s_link
{
	t_room 				*first_room;
	t_room 				*second_room;
	struct s_link		*prev;
	struct s_link		*next;
}						t_link;

typedef struct			s_step
{
	int 				ant_num;
	int					was_started;
	t_room 				*room;
	struct s_step		*next;
}						t_step;

typedef struct 			s_step_line
{
	char 				*line;
	t_step 				*stepz;
	struct s_step_line	*next;
	struct s_step_line	*prev;
}						t_step_line;

typedef struct			s_all_data
{
	int					ants;
	t_room 				*all_rooms;
	t_link 				*all_links;
	t_step_line 		*all_steps;
	int 				w_height;
	int					w_width;
	t_room 				*start;
	t_room 				*end;
	char 				*courier;
	int 				del_me_fd;
	int					is_generated_map;
	t_step_line 		*curr_step;
	bool				ants_reduced;
}						t_all_data;

typedef struct 			s_sdl_things
{
	int 				radius;
	int 				original_radius;
	t_all_data			*map_data;
	SDL_Window			*win;
	SDL_Surface			*surf;
	SDL_Event			event;
	int 				width;
	int 				height;
	SDL_Renderer 		*renderer;
	Uint8				*wav_buffer;
	SDL_AudioDeviceID	device_id;
	SDL_Texture 		*texture;
	SDL_Texture			*cheems;
	Uint32				*m_buffer1;
	Uint32				*m_buffer2;
	float 				zoom;
	bool				ants_go_brrrr;
	double				step_progress;
	bool				redraw;
}						t_sdl_things;

/*
 * util functions
 */
int		ft_error(const char *error);
int		del_line_and_return(char *line, int ret);
int		is_all_digits(char *line);
void	del_str_arr(char **to_delete);
void	clear_sdl(t_all_data *data, t_sdl_things *things);
void	sdl_error(t_sdl_things *things);
int		str_contains(char *str, char *contains);
void	modify_levels(t_all_data *data);
char	**get_ants_array(int ants_count);
int		path_count(char *ants);
void 		fix_coords(t_all_data *data, t_sdl_things *things);
int				init_music(t_sdl_things *things);

/*
 *
 * read functions
 */
int		read_ants(t_all_data *data);
int		read_rooms(t_all_data *data);
int		read_links(t_all_data *data);
int		read_steps(t_all_data *data);
int		set_levels_from_data(t_all_data *data);
/*
 * validation
 */
int		is_comment(char *line);
int		split_bits(char *line, char c);
int		is_link(char *line);
int		is_step(char *step);
int		is_room(char *line);
int		valid_coords(t_room *room, t_room *list);
int		duplicate_links(t_link *link, t_all_data *data);
bool	check_ants_quantity(int quantity, char *line);

/*
 * drawing
 */
int		init_sdl(t_sdl_things *things);
void	find_win_size(t_all_data *data, t_sdl_things *things);
int		draw_circle(int x, int y, int rad, t_sdl_things *things);
int		draw_line_of_circles(t_sdl_things *things);
void	draw_filled_circle(int x, int y, int radius, t_sdl_things *things);
void	test_draw_circle_line(int x0, int y0, int x1, int radius, t_sdl_things *things);
void	test_draw_neon_circle_line(int x0, int y0, int x1, int radius, t_sdl_things *things);
void	draw_brezenham(int x0, int y0, int x1, int y1, int radius, t_sdl_things *things);
void 	buff_to_texture(t_sdl_things *things);
void 	loopz(t_sdl_things *env, t_all_data *data);
void 	draw_map(t_sdl_things *things, t_all_data *data);
void	draw_step(t_sdl_things *things, t_all_data *data);
void draw_cheemz(t_sdl_things *things, int x, int y);
void load_cheemz(t_sdl_things *things);


/* BUFF DRAWING
 *
 */
void	draw_filled_circle_in_buff(int x, int y, int radius, t_sdl_things *things, Uint32 color);
void	draw_line_in_buff(Uint32 color, Uint32 *buff, int x0, int x1, int y, t_sdl_things *things);
void	draw_all_paths_b4_blur(t_sdl_things *things, t_all_data *data);
void	blur_v4(t_sdl_things *things);
int		draw_all_paths2(t_sdl_things *things, t_all_data *data);
void	draw_all_paths_after_blur(t_sdl_things *things, t_all_data *data);
void	draw_stoopid_line (int x, int y, int radius, t_sdl_things *things);
void 		draw_stoopid_line_in_buff(int x, int y, int radius, t_sdl_things *things, Uint32 color);
void		fastend_blur(t_sdl_things *things);
void initial_ants(t_sdl_things *things, t_all_data *data);
void	draw_circle_in_buff(int x, int y, int rad, t_sdl_things *things, Uint32 color);
void draw_all_rooms(t_sdl_things *things, t_all_data *data);

/*
 * Link_helper
 */
t_link	*make_link(char *line, t_link *link, t_all_data *data);
t_link	*initial_link(t_all_data *data);
int		is_command(char *line);

/*
 * Steps_helper
 */
t_step		*assign_step(char *step_line, t_all_data *data, t_step *curr_step);
int			check_correct_steps(char **line);
bool		is_all_steps_found(t_step_line *all_steps, int ants_count);

/*
 * Helpers
 */
void		delete_unused(t_all_data *data);

/*
 * zoomin and movin
 */
void		zoom(t_all_data *data, SDL_Event event, t_sdl_things *things);

#endif
