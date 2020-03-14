#include "lem_viz.h"



static void			render_background(t_sdl_things *sdl)
{
	SDL_Rect rect;

	rect.h = sdl->height;
	rect.w = sdl->width;
	rect.y = 0;
	rect.x = 0;
	SDL_FillRect(sdl->sur, &rect,
				 SDL_MapRGB(sdl->sur->format, 255, 0, 255));
}


void				main_loop(t_sdl_things *env)
{
	SDL_Event		event;

	while (1)
	{
		render_background(env);
		SDL_WaitEvent(&event);
		if (SDL_QUIT == event.type || SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		SDL_UpdateWindowSurface(env->win);
		SDL_Delay(1000 / 60);
	}
	SDL_DestroyWindow(env->win);
	SDL_Quit();
}

void draw_test_window(t_sdl_things *things)
{
	main_loop(things);


}