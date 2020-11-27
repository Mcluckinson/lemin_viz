//
// Created by Carly Yuriko on 11/27/20.
//

#include "lem_viz.h"

void		load_cheemz(t_sdl_things *things)
{
	SDL_Surface	*surface;

	surface = IMG_Load("../rsrcs/cheems.png");
	if (!surface)
		ft_error(SDL_GetError());
	things->cheems = SDL_CreateTextureFromSurface(things->renderer, surface);
	SDL_FreeSurface(surface);
	if (!things->cheems)
		ft_error(SDL_GetError());
}

void draw_cheemz(t_sdl_things *things, int x, int y)
{
	SDL_Rect	cheemz_frame;

	cheemz_frame.h = things->radius * 8;
	cheemz_frame.w = things->radius * 8;

	cheemz_frame.x = x - cheemz_frame.w / 2;
	cheemz_frame.y = y - cheemz_frame.h / 2;
	SDL_RenderCopy(things->renderer, things->cheems, NULL, &cheemz_frame);
}