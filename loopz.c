//
// Created by Carly Yuriko on 11/8/20.
//

#include "lem_viz.h"

void 	loopz(t_sdl_things *things, t_all_data *data)
{
	SDL_Event		event;
	double			step_completed;

	step_completed = 0.01;
	draw_map(things, data, step_completed);
	SDL_RenderPresent(things->renderer);
	while (1)
	{
		SDL_WaitEvent(&event);
		if (SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		if (event.type == SDL_MOUSEWHEEL)
		{
			zoom(data, event, things);
			draw_map(things, data, step_completed);
			SDL_RenderPresent(things->renderer);
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				things->ants_go_brrrr = true;
				while (step_completed <= 1)
				{
					draw_map(things, data, step_completed);
					SDL_RenderPresent(things->renderer);
					step_completed += 0.01;
				}
				data->curr_step = data->curr_step->next;
				step_completed = 0.01;
			}
			//	draw_next_step();
		}

	}
	if (things->renderer)
		SDL_DestroyRenderer(things->renderer);
	free(things->m_buffer1);
	free(things->m_buffer2);
	SDL_DestroyWindow(things->win);
	SDL_Quit();
	exit(0);
}