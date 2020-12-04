#include "lem_viz.h"

t_xy	catch_mouse_coords()
{
	t_xy mouse_coords;

	SDL_GetMouseState(&mouse_coords.x, &mouse_coords.y);
	return (mouse_coords);
}

bool 	find_ant(t_xy mouse_coords, t_xy current_coords, int radius)
{
	if (current_coords.x < mouse_coords.x + radius && current_coords.x > mouse_coords.x - radius
	&& current_coords.y < mouse_coords.y + radius && current_coords.y > mouse_coords.y - radius)
		return (true);
	return (false);
}

void 	delete_ant(t_all_data *data, int ant_num)
{
	t_step_line *counter;
	t_step 		*terminator;
	t_step 		*connor;

	counter = data->all_steps;
	while (counter)
	{
		terminator = counter->stepz;
		connor = counter->stepz;
		while (terminator)
		{
			if (terminator->ant_num == ant_num)
			{
				if (terminator == connor)
				{
					counter->stepz = terminator->next;
					connor = terminator->next;
					free(terminator);
					terminator = NULL;
				}
				else
				{
					connor->next = terminator->next;
					free(terminator);
					terminator = NULL;
					break ;
				}
				if (terminator != connor)
					connor = connor->next;
				terminator = terminator->next;
			}
			counter = counter->next;
		}
	}
}