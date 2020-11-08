//
// Created by Carly Yuriko on 11/8/20.
//

#include "lem_viz.h"

void 	loopz(t_sdl_things *things, t_all_data *data)
{
	SDL_Event		event;

	draw_map(things, data);
	SDL_RenderPresent(things->renderer);
	while (1)
	{
		SDL_WaitEvent(&event);
		if (SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		if (event.type == SDL_MOUSEWHEEL)
		{
			zoom(data, event, things);
			draw_map(things, data);
			SDL_RenderPresent(things->renderer);////clear old?
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