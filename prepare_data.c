/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:45:36 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 18:04:36 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void	move_to_zero(t_room *rooms, int offset_x, int offset_y)/////////maybe find parts of paths first?
{
	t_room *rooms_to_fix = rooms;

	while (rooms_to_fix)
	{
		rooms_to_fix->x -= offset_x;
		rooms_to_fix->y -= offset_y;
		rooms_to_fix = rooms_to_fix->next;
	}
}

static void	put_it_into_screen(t_room *rooms, float zoom)
{
	t_room *rooms_to_fix = rooms;

	while (rooms_to_fix)
	{
		rooms_to_fix->x *= zoom;
		rooms_to_fix->y *= zoom;
		rooms_to_fix = rooms_to_fix->next;
	}
}

static void	fix_initial_position(t_all_data *data, t_sdl_things *things)
{
	float zoom_factor;

	if ((float)things->width / DEFAULT_WIDTH > (float)things->height / DEFAULT_HEIGHT)
		zoom_factor = (float)DEFAULT_WIDTH / (float)things->width;
	else
		zoom_factor = (float)DEFAULT_HEIGHT / (float)things->height;
	put_it_into_screen(data->all_rooms, zoom_factor);
	things->width *= zoom_factor;
	things->height *= zoom_factor;
	things->zoom = zoom_factor;
}

void		find_win_size(t_all_data *data, t_sdl_things *things)///////////should i even do it?
{
	t_room *room;
	int		x_max;
	int		x_min;
	int		y_max;
	int		y_min;

	x_max = DEFAULT_WIDTH;
	x_min = 9999;////////////TEMP SHIT FIND SMTH BETTER
	y_max = DEFAULT_HEIGHT;
	y_min = 9999;/////////SAME
	room = data->all_rooms;
	while (room)
	{
		x_max = (x_max < room->x ? room->x : x_max);
		x_min = (x_min > room->x ? room->x : x_min);
		y_max = (y_max < room->y ? room->y : y_max);
		y_min = (y_min > room->y ? room->y : y_min);
		room = room->next;
	}
	things->width = x_max - x_min;
	things->height = y_max - y_min;
	int center_w = things->width / 2;
	int center_h = things->height / 2;
	int offset_w = center_w - x_max;
	int offset_h = center_h - y_max;

//	move_to_zero(data->all_rooms, center_w, center_h);
	if (things->width > DEFAULT_WIDTH || things->height > DEFAULT_HEIGHT)
		fix_initial_position(data, things);
}

void		find_parts_of_paths(t_all_data *data)
{
	t_room *room_checker = data->all_rooms;
	t_step *step_checker = data->all_steps;
}
