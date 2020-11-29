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

static t_xy		find_resolution(t_room *rooms)
{
	t_xy		result;
	int			max_x;
	int			min_x;
	int			max_y;
	int			min_y;

	max_x = rooms->x;
	min_x = rooms->x;
	max_y = rooms->y;
	min_y = rooms->y;
	while (rooms)
	{
		max_x = rooms->x > max_x ? rooms->x : max_x;
		min_x = rooms->x < min_x ? rooms->x : min_x;
		max_y = rooms->y > max_y ? rooms->y : max_y;
		min_y = rooms->y < min_y ? rooms->y : min_y;
		rooms = rooms->next;
	}
	result.x = (max_x + min_x) / 2;
	result.y = (max_y + min_y) / 2;
	result.width = max_x - min_x;
	result.height = max_y - min_y;
	return (result);
}

void			center_coordinate(t_all_data *data, int width, int height)
{
	t_room		*counter;
	int			offset_x;
	int			offset_y;
	t_xy		resolution;

	counter = NULL;
	resolution = find_resolution(data->all_rooms);
	offset_x = width - resolution.x;
	offset_y = height - resolution.y;
	counter = data->all_rooms;
	while (counter)
	{
		counter->x += offset_x;
		counter->y += offset_y;
		counter = counter->next;
	}
}

static float	should_fix(t_all_data *data)
{
	int			max_width;
	int			max_height;
	float		fix_ratio_x;
	float		fix_ratio_y;
	t_xy		resolution;

	resolution = find_resolution(data->all_rooms);
	fix_ratio_y = 1;
	fix_ratio_x = 1;
	max_width = resolution.width;
	max_height = resolution.height;
	if (max_width < DEFAULT_WIDTH && max_height < DEFAULT_HEIGHT)
		return (1);
	if (max_width > DEFAULT_WIDTH)
		fix_ratio_x = ((float)DEFAULT_WIDTH - 50) / (float)max_width;
	if (max_height > DEFAULT_HEIGHT)
		fix_ratio_y = ((float)DEFAULT_HEIGHT - 50) / (float)max_height;
	return (fix_ratio_x < fix_ratio_y ? fix_ratio_x : fix_ratio_y);
}

void			fix_coords(t_all_data *data, t_sdl_things *things)
{
	float		fixer;
	t_room		*counter;

	counter = data->all_rooms;
	fixer = should_fix(data);
	if (fixer != 1)
	{
		while (counter)
		{
			counter->x *= fixer;
			counter->y *= fixer;
			counter = counter->next;
		}
	}
	center_coordinate(data, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT / 2);
	things->radius = 4 * fixer;
	things->radius = things->radius ? things->radius : 1;
	things->height = DEFAULT_HEIGHT;
	things->width = DEFAULT_WIDTH;
	things->zoom = 1;
}
