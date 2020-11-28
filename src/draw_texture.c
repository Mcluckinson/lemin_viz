/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:00:12 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 16:00:14 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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
