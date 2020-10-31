//
// Created by Carly Yuriko on 10/31/20.
//

#include "lem_viz.h"

static void move_to_mouse(int x, int y, t_all_data *data)
{
	int diff_x;
	int diff_y;
	t_room *counter;

	diff_x = (DEFAULT_WIDTH / 2) - x;
	diff_y = (DEFAULT_HEIGHT / 2) - y;

	counter = data->all_rooms;
	while (counter)
	{
		counter->x -= diff_x;
		counter->y -= diff_y;
		counter = counter->next;
	}

}

static void zoom_coords(t_all_data *data, float ratio)
{
	t_room *counter;

	counter = data->all_rooms;
	while (counter)
	{
		counter->x *= ratio;
		counter->y *= ratio;
		counter = counter->next;
	}
}

static void get_ratio(t_sdl_things *things, SDL_Event event)
{
	if (event.wheel.y > 0)
		things->zoom += (float)0.1;
	else if (event.wheel.y < 0)
		things->zoom -= (float)0.1;
	return ;
}

void	zoom(t_all_data *data, SDL_Event event, t_sdl_things *things)
{
	int mouse_x;
	int mouse_y;

	SDL_GetMouseState(&mouse_x, &mouse_y);
	get_ratio(things, event);
	move_to_mouse(mouse_x, mouse_y, data);
	zoom_coords(data, things->zoom);
}