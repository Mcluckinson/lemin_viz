//
// Created by Carly Yuriko on 11/8/20.
//

#include "lem_viz.h"

void 	loopz(t_sdl_things *things, t_all_data *data)
{
	SDL_Event		event;

	things->step_progress = 0.01;
	things->redraw = true;
	draw_map(things, data, things->step_progress);///fix
	SDL_RenderPresent(things->renderer);
	things->redraw = false;
	while (SDL_WaitEvent(&event))
	{
		if (SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		if (event.type == SDL_MOUSEWHEEL && !things->ants_go_brrrr)
		{
			things->redraw = true;
			zoom(data, event, things);
			draw_map(things, data, things->step_progress);///fix
			SDL_RenderPresent(things->renderer);
			things->redraw = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && !things->ants_go_brrrr)
			{
				things->ants_go_brrrr = true;
				while (things->step_progress <= 1)
				{
					draw_map(things, data, things->step_progress);///fix dis step_progress things
					SDL_RenderPresent(things->renderer);
					things->step_progress += 0.01;
					SDL_Delay(1000 / 60);
				}
				data->curr_step = data->curr_step->next;
				things->ants_go_brrrr = false;
				things->step_progress = 0.01;
			}
			//	draw_next_step();
		}

	}
	///the thing below should be performed by a CLEAR_STUFF funtion, make one if there's none
	///destroy textures and shit
	if (things->renderer)
		SDL_DestroyRenderer(things->renderer);
	free(things->m_buffer1);
	free(things->m_buffer2);
	SDL_DestroyWindow(things->win);
	SDL_Quit();
	exit(0);
}