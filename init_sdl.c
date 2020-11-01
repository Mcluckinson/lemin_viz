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
	if (things->background)
		SDL_DestroyTexture(things->background);
	SDL_Quit();
	ft_error(SDL_GetError());
}

int			init_sdl(t_sdl_things *things)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		ft_error(SDL_GetError());
	if (!(things->win = SDL_CreateWindow("lem-in vizuals", 100, 100, things->width, things->height, SDL_WINDOW_SHOWN)))
		sdl_error(things);
	if (!(things->renderer = SDL_CreateRenderer(things->win, -1, SDL_RENDERER_ACCELERATED)))
		sdl_error(things);
	if (!(things->background = SDL_CreateTexture(things->renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, things->width, things->height)))
		sdl_error(things);////probably useless?
	things->m_buffer1 = (Uint32*)ft_memalloc(sizeof(Uint32) * things->width * things->height);
	things->m_buffer2 = (Uint32*)ft_memalloc(sizeof(Uint32) * things->width * things->height);
	!things->zoom ? (things->radius = 4) : (things->radius = 5 * things->zoom);
	things->original_radius = things->radius;
	return (1);
}
