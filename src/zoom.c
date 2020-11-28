/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:51:54 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 15:51:58 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_xy	get_offset(t_all_data *data)
{
	t_xy	result;
	t_room	*counter;

	counter = data->all_rooms;
	result.x = counter->x;
	result.y = counter->y;
	while (counter)
	{
		if (counter->y < result.y)
			result.y = counter->y;
		if (counter->x < result.x)
			result.x = counter->x;
		counter = counter->next;
	}
	return (result);
}

static void	move_to_mouse(t_all_data *data,
						int mouse_x, int mouse_y, float factor)
{
	t_room	*counter;
	t_xy	offset;

	offset = get_offset(data);
	mouse_x -= DEFAULT_WIDTH / 2;
	mouse_y -= DEFAULT_HEIGHT / 2;
	offset.x -= DEFAULT_WIDTH / 2;
	offset.y -= DEFAULT_HEIGHT / 2;
	factor -= (float)1;
	counter = data->all_rooms;
	offset.x = (mouse_x - offset.x) * factor;
	offset.y = (mouse_y - offset.y) * factor;
	while (counter)
	{
		counter->x -= offset.x;
		counter->y -= offset.y;
		counter = counter->next;
	}
}

static void	zoom_coords(t_all_data *data, float ratio)
{
	t_room	*counter;
	int		mouse_x;
	int		mouse_y;

	SDL_GetMouseState(&mouse_x, &mouse_y);
	counter = data->all_rooms;
	while (counter)
	{
		counter->x *= ratio;
		counter->y *= ratio;
		counter = counter->next;
	}
	move_to_mouse(data, mouse_x, mouse_y, ratio);
}

static void	get_ratio(t_sdl_things *things, SDL_Event event)
{
	if (event.wheel.y < 0)
		things->zoom = (float)1.1;
	else if (event.wheel.y > 0)
		things->zoom = (float)0.9;
}

void		zoom(t_all_data *data, SDL_Event event, t_sdl_things *things)
{
	get_ratio(things, event);
	zoom_coords(data, things->zoom);
}
