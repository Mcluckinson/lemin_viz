#include "lem_viz.h"

void 	update(t_sdl_things *things)
{
	//SDL_UpdateTexture(things->background, NULL, pixels, int pitch);
	SDL_RenderClear(things->renderer);
	SDL_RenderCopy(things->renderer, things->background, NULL, NULL);
	SDL_RenderPresent(things->renderer);
}

void			render_background(t_sdl_things *sdl)
{
	SDL_Rect rect;

	rect.h = sdl->height;
	rect.w = sdl->width;
	rect.y = 0;
	rect.x = 0;
	SDL_FillRect(sdl->surf, &rect,
				 SDL_MapRGB(sdl->surf->format, 0, 0, 0));
}


void				main_loop(t_sdl_things *env, t_all_data *data)
{
	SDL_Event		event;

	render_background(env);
	draw_all_paths2(env, data);
	SDL_RenderPresent(env->renderer);

	while (1)
	{
		SDL_WaitEvent(&event);
		if (SDL_QUIT == event.type || SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		pulse_map(env, data);

		SDL_Delay(50);
	}
	if (env->renderer)
		SDL_DestroyRenderer(env->renderer);
	free(env->m_buffer1);
	free(env->m_buffer2);
	SDL_DestroyWindow(env->win);
	SDL_Quit();
	exit(0);
}

void draw_test_window(t_sdl_things *things, t_all_data *data)
{
	main_loop(things, data);
}