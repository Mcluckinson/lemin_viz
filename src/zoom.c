//
// Created by Carly Yuriko on 10/31/20.
//

#include "lem_viz.h"

static int getLeft(t_all_data *data)
{
	t_room *counter;
	int left;

	counter = data->all_rooms;
	left = DEFAULT_WIDTH;
	while (counter)
	{
		if (counter->x > 0 && counter->x < DEFAULT_WIDTH)
		{
			if (counter->x < left)
				left = counter->x;
		}
		counter = counter->next;
	}
	return (left);
}

static int gettop(t_all_data *data)/////optimize it: do it one function instead of traversing the list twice
{
	t_room *counter;
	int top;

	counter = data->all_rooms;
	top = DEFAULT_HEIGHT;
	while (counter)
	{
		if (counter->y > 0 && counter->y < DEFAULT_HEIGHT)
		{
			if (counter->y < top)
				top = counter->y;
		}
		counter = counter->next;
	}
	return (top);
}

static void move_to_mouse(t_all_data *data, int mouse_x, int mouse_y, float factor)
{
	int offset_x;
	int offset_y;
	t_room *counter;

	mouse_x -= DEFAULT_WIDTH / 2;
	mouse_y -= DEFAULT_HEIGHT / 2;

	counter = data->all_rooms;
	offset_x = (mouse_x - (getLeft(data) - DEFAULT_WIDTH / 2))* (factor - 1.0);
	offset_y = (mouse_y - (gettop(data) - DEFAULT_HEIGHT / 2)) * (factor - 1.0);
	while(counter)
	{
		counter->x -= offset_x;
		counter->y -= offset_y;
		counter = counter->next;
	}

}

static void zoom_coords(t_all_data *data, float ratio)
{
	t_room *counter;
	int mouse_x;
	int mouse_y;

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

static void get_ratio(t_sdl_things *things, SDL_Event event)
{
	if (event.wheel.y < 0)
		things->zoom = (float)1.1;
	else if (event.wheel.y > 0)
		things->zoom = (float)0.9;
}

void	zoom(t_all_data *data, SDL_Event event, t_sdl_things *things)
{
	get_ratio(things, event);
	zoom_coords(data, things->zoom);
}