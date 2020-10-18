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

static int			find_max_width(t_all_data *data)
{
	int 	max;
	int		min;
	int 	result;
	t_room  *counter;

	counter = data->all_rooms;
	max = counter->x;
	min = counter->x;

	while (counter)
	{
		max = counter->x > max ? counter->x : max;
		min = counter->x < min ? counter->x : min;
		counter = counter->next;
	}
	result = max - min;
	return (result);
}

static int			find_max_height(t_all_data *data)
{
	int 	max;
	int		min;
	int 	result;
	t_room  *counter;


	counter = data->all_rooms;
	max = counter->y;
	min = counter->y;
	while (counter)
	{
		max = counter->y > max ? counter->y : max;
		min = counter->y < min ? counter->y : min;
		counter = counter->next;
	}
	result = max - min;
	return (result);
}

static void 			center_x(int max_width, t_all_data *data)
{
	t_room *counter;
	int		offset;
	int 	negative;

	negative = 0;
	offset = DEFAULT_WIDTH / 2 - max_width / 2;
	counter = data->all_rooms;
	while (counter)
	{
		counter->x-= offset;
		if (counter->x < negative)
			negative = counter->x;
		counter = counter->next;
	}
	counter = data->all_rooms;
	while (counter)
	{
		counter->x-= negative;
		counter = counter->next;
	}
}


static void 			center_y(int max_height, t_all_data *data)
{
	t_room *counter;
	int		offset;
	int 	negative;

	negative = 0;
	offset = DEFAULT_HEIGHT / 2 - max_height / 2;
	counter = data->all_rooms;
	while (counter)
	{
		counter->y-= offset;
		if (counter->y < negative)
			negative = counter->y;
		counter = counter->next;
	}
	counter = data->all_rooms;
	while (counter)
	{
		counter->y-= negative;
		counter = counter->next;
	}
}

static float			should_fix(t_all_data *data)
{
	int max_width;
	int max_height;
	float fix_ratio_x;
	float fix_ratio_y;

	fix_ratio_y = 1;
	fix_ratio_x = 1;
	max_width = find_max_width(data);
	max_height = find_max_height(data);

	if (max_width < DEFAULT_WIDTH && max_height < DEFAULT_HEIGHT)
		return (1);
	if (max_width > DEFAULT_WIDTH)
		fix_ratio_x = (float)DEFAULT_WIDTH / (float)max_width;
	if (max_height > DEFAULT_HEIGHT)
		fix_ratio_y = (float)DEFAULT_HEIGHT / (float)max_height;
	return (fix_ratio_x < fix_ratio_y ? fix_ratio_x : fix_ratio_y);
}


void 		fix_coords(t_all_data *data, t_sdl_things *things)
{
	float	fixer;
	t_room *counter;
	int 	max_width;
	int 	max_height;

	counter = data->all_rooms;
	fixer = should_fix(data);
	if (fixer != 1)
	{
		while (counter)
		{
			counter->x*=fixer;
			counter->y*=fixer;
			counter = counter->next;
		}
		things->radius = 4 * fixer;
		things->original_radius = things->radius;
	}
	max_width = find_max_width(data);
	max_height = find_max_height(data);
	center_x(max_width, data);
	center_y(max_height, data);
	things->height = DEFAULT_HEIGHT;
	things->width = DEFAULT_WIDTH;

}
