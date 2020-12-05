#include "lem_viz.h"

static t_xy	catch_mouse_coords()
{
	t_xy mouse_coords;

	SDL_GetMouseState(&mouse_coords.x, &mouse_coords.y);
	return (mouse_coords);
}

static bool 	find_ant(t_xy mouse_coords, t_xy current_coords, int radius)
{
	if (current_coords.x < mouse_coords.x + radius && current_coords.x > mouse_coords.x - radius
	&& current_coords.y < mouse_coords.y + radius && current_coords.y > mouse_coords.y - radius)
		return (true);
	return (false);
}

static void 	delete_ant(t_all_data *data, int ant_num)
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
					break ;
				}
				else
				{
					connor->next = terminator->next;
					free(terminator);
					terminator = NULL;
					break ;
				}
			}
			if (terminator != connor)
				connor = connor->next;
			terminator = terminator->next;
		}
		counter = counter->next;
	}
}

bool	delete_cheemz(int ant_num, t_all_data *data, t_xy cheemz_coords, t_sdl_things *things)
{
	t_xy mouse_coords = catch_mouse_coords();
	bool should_kill = find_ant(mouse_coords, cheemz_coords, things->radius * 20);

	if (should_kill)
	{
		data->game_ants_left--;
		delete_ant(data, ant_num);
	}
	return (should_kill);
}