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

# include "../SDL2/SDL2.framework/Headers/SDL.h"
# include "../SDL2/SDL2_image.framework/Headers/SDL_image.h"
# include "../libft/libft.h"
# include "math.h"
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>

# define DEFAULT_WIDTH 1366
# define DEFAULT_HEIGHT 768

# define MODIFIER_X 2
# define MODIFIER_Y 20
# define BLUR_EXTENT 3

typedef struct			s_xy
{
	int					x;
	int					y;
	int					width;
	int					height;
}						t_xy;

typedef struct			s_room
{
	int					x;
	int					y;
	int					level;
	char				*name;
	int					is_part_of_path;
	struct s_room		*next;
}						t_room;

typedef struct			s_link
{
	t_room				*first_room;
	t_room				*second_room;
	struct s_link		*next;
}						t_link;

typedef struct			s_step
{
	int					ant_num;
	int					was_started;
	t_room				*room;
	struct s_step		*next;
}						t_step;

typedef struct			s_step_line
{
	char				*line;
	t_step				*stepz;
	struct s_step_line	*next;
	struct s_step_line	*prev;
}						t_step_line;

typedef struct			s_all_data
{
	int					ants;
	int					default_ants;
	t_room				*all_rooms;
	t_link				*all_links;
	t_step_line			*all_steps;
	t_room				*start;
	t_room				*end;
	char				*courier;
	int					del_me_fd;
	int					is_generated_map;
	t_step_line			*curr_step;
	bool				ants_reduced;
	int					game_ants_left;
}						t_all_data;

typedef struct			s_sdl_things
{
	bool				game_mode;
	int					radius;
	SDL_Window			*win;
	SDL_Event			event;
	SDL_Renderer		*renderer;
	Uint8				*wav_buffer;
	SDL_AudioDeviceID	device_id;
	SDL_Texture			*texture;
	SDL_Texture			*cheems;
	SDL_Texture			*roomz;
	SDL_Texture			*start;
	SDL_Texture			*end;
	SDL_Texture			*bat_right;
	SDL_Texture			*bat_down;
	SDL_Texture			*horni_land;
	SDL_Texture			*u_win;
	SDL_Texture			*u_looz;
	SDL_Texture			*cryin;
	Uint32				*m_buffer1;
	Uint32				*m_buffer2;
	float				zoom;
	bool				ants_go_brrrr;
	double				step_progress;
	bool				redraw;
	t_xy				xy;
	bool				mouse_down;
}						t_sdl_things;

typedef struct			s_drawing_things
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					radius;
	Uint32				color;
}						t_drawing_things;

/*
** util functions
*/
int						ft_error(const char *error);
int						ft_error_new(t_all_data *data,
							t_sdl_things *things, const char *error);
void					clear_data(t_all_data *data);
int						del_line_and_return(char *line, int ret);
int						is_all_digits(char *line);
void					del_str_arr(char **to_delete);
int						str_contains(char *str, char *contains);
void					modify_levels(t_all_data *data);
char					**get_ants_array(int ants_count);
int						path_count(char *ants);
void					fix_coords(t_all_data *data, t_sdl_things *things);
int						init_music(t_sdl_things *things);
void					swap_values(int *a, int *b);
void					check_args(int argc, char **argv,
							t_all_data *data, t_sdl_things *things);

/*
** read functions
*/
int						read_ants(t_all_data *data);
int						read_rooms(t_all_data *data);
int						read_links(t_all_data *data);
int						read_steps(t_all_data *data);
int						set_levels_from_data(t_all_data *data);
/*
** validation
*/
int						is_comment(char *line);
int						split_bits(char *line, char c);
int						is_link(char *line);
int						is_step(char *step);
int						is_room(char *line);
int						valid_coords(t_room *room, t_room *list);
int						duplicate_links(t_link *link, t_all_data *data);
bool					check_ants_quantity(int quantity, char *line);

/*
** drawing
*/
int						init_sdl(t_sdl_things *things);
void					buff_to_texture(t_sdl_things *things);
void					loop(t_sdl_things *env, t_all_data *data);
void					loop_game_mode(t_sdl_things *env, t_all_data *data);
void					draw_map(t_sdl_things *things, t_all_data *data);
void					draw_step(t_sdl_things *things, t_all_data *data);
void					draw_cheemz(t_sdl_things *things, int x, int y);
void					draw_roomz(t_sdl_things *things, t_all_data *data);
bool					load_cheemz(t_sdl_things *things);
void					finish_step(t_sdl_things *things, t_all_data *data);
void					draw_progress_bar(t_sdl_things *things,
							t_all_data *data);
void					draw_baseball_bat(t_sdl_things *things);
void					draw_horni_sign(t_sdl_things *things, t_all_data *data);

/*
**BUFF DRAWING
*/
void					draw_all_paths_b4_blur(t_sdl_things *things,
							t_all_data *data);
void					blur_v4(t_sdl_things *things);
void					draw_all_paths_after_blur(t_sdl_things *things,
							t_all_data *data);
void					initial_ants(t_sdl_things *things, t_all_data *data);
void					draw_brezenham_line_in_buff(t_sdl_things *things,
							t_drawing_things drawing_things);

/*
** Link_helper
*/
t_link					*make_link(char *line, t_link *link, t_all_data *data);
t_link					*initial_link(t_all_data *data);
int						is_command(char *line);

/*
** Steps_helper
*/
t_step					*assign_step(char *step_line, t_all_data *data,
							t_step *curr_step);
int						check_correct_steps(char **line);
bool					is_all_steps_found(t_step_line *all_steps,
							int ants_count);

/*
** Ants steps Helpers
*/
bool					try_step(t_sdl_things *things, t_step_line *old_step,
							t_step_line *new_step, t_all_data *data);
int						count_stepz(t_step_line *stepz_line);
bool					delete_cheemz(int ant_num, t_all_data *data,
							t_xy cheemz_coords, t_sdl_things *things);

/*
** Helpers
*/
void					delete_unused(t_all_data *data);
t_xy					get_cheemz_pos(t_room *start, t_step *step,
							t_sdl_things *things);
void					init_params_norminette_kek(bool *killd, t_step **step,
							t_step **bckup, t_step_line *new_step);
void					update_step_sorry_norminette
					(t_sdl_things *things, t_step *step, t_xy cheemz_pos);

/*
** zoomin and movin
*/
void					zoom(t_all_data *data, SDL_Event event,
							t_sdl_things *things);

#endif
