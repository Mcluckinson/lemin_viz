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

int			init_sdl(t_sdl_things *things)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return (false);
	if (!(things->win = SDL_CreateWindow("Lem-in", 100, 100,
						DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN)))
		return (false);
	if (!(things->renderer = SDL_CreateRenderer(things->win, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)))
		return (false);
	if (!(things->texture = SDL_CreateTexture(things->renderer,
											SDL_PIXELFORMAT_RGB888,
											SDL_TEXTUREACCESS_TARGET,
											DEFAULT_WIDTH, DEFAULT_HEIGHT)))
		return (false);
	things->m_buffer1 = (Uint32*)ft_memalloc(sizeof(Uint32)
			* DEFAULT_WIDTH * DEFAULT_HEIGHT);
	things->m_buffer2 = (Uint32*)ft_memalloc(sizeof(Uint32)
			* DEFAULT_WIDTH * DEFAULT_HEIGHT);
	if (!(load_cheemz(things)))
		return (false);
	if (things->game_mode)
		SDL_ShowCursor(SDL_DISABLE);
	return (true);
}
