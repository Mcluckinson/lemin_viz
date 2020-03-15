#include "lem_viz.h"



static void			render_background(t_sdl_things *sdl)
{
	SDL_Rect rect;

	rect.h = sdl->height;
	rect.w = sdl->width;
	rect.y = 0;
	rect.x = 0;
	SDL_FillRect(sdl->sur, &rect,
				 SDL_MapRGB(sdl->sur->format, 0, 0, 0));
}


void				main_loop(t_sdl_things *env, t_all_data *data)
{
	SDL_Event		event;

	while (1)
	{
	//	render_background(env);
		draw_all_paths(env, data);
		SDL_WaitEvent(&event);
		if (SDL_QUIT == event.type || SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		SDL_UpdateWindowSurface(env->win);
		SDL_Delay(1000 / 60);
	}
	if (env->renderer)
		SDL_DestroyRenderer(env->renderer);
	SDL_DestroyWindow(env->win);
	SDL_Quit();
}

void draw_test_window(t_sdl_things *things, t_all_data *data)
{
	main_loop(things, data);


}