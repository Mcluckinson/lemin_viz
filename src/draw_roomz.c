#include "lem_viz.h"

void draw_all_rooms(t_sdl_things *things, t_all_data *data)
{
	t_room *counter;
	Uint32 color;
	int radius;

	radius = things->radius * 2;
	color = 0XFF00FF;
	counter = data->all_rooms;
	while (counter)
	{
		draw_filled_circle_in_buff(counter->x, counter->y, radius, things, color);
		counter = counter->next;
	}
}