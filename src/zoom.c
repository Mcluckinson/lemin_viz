//
// Created by Carly Yuriko on 10/31/20.
//

#include "lem_viz.h"

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
	center_x(data, mouse_x);
	center_y(data, mouse_y);
}

static void get_ratio(t_sdl_things *things, SDL_Event event)
{
	if (event.wheel.y > 0)
		things->zoom = (float)1.1;
	else if (event.wheel.y < 0)
		things->zoom = (float)0.9;
}

void	zoom(t_all_data *data, SDL_Event event, t_sdl_things *things)
{
	get_ratio(things, event);
	zoom_coords(data, things->zoom);
}