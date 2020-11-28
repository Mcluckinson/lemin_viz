/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:43:40 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/15 15:53:30 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

void		sdl_error(t_sdl_things *things)
{
	if (things->win)
		SDL_DestroyWindow(things->win);
	if (things->texture)
		SDL_DestroyTexture(things->texture);
	SDL_Quit();
	ft_error(SDL_GetError());
}

int			init_sdl(t_sdl_things *things)
{
	int		height;
	int		width;

	height = things->height;
	width = things->width;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		ft_error(SDL_GetError());
	if (!(things->win = SDL_CreateWindow("lem-in vizuals", 100, 100,
						width, height, SDL_WINDOW_SHOWN)))
		sdl_error(things);
	if (!(things->renderer = SDL_CreateRenderer(things->win, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)))
		sdl_error(things);
	if (!(things->texture = SDL_CreateTexture(things->renderer,
											SDL_PIXELFORMAT_RGB888,
											SDL_TEXTUREACCESS_TARGET,
											width, height)))
		sdl_error(things);
	things->m_buffer1 = (Uint32*)ft_memalloc(sizeof(Uint32) * width * height);
	things->m_buffer2 = (Uint32*)ft_memalloc(sizeof(Uint32) * width * height);
	load_cheemz(things);
	return (1);
}
