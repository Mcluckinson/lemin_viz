/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:43:40 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 19:54:20 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

int 		init_sdl(t_sdl_things *things)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_error(SDL_GetError());
	if (!(things->win = SDL_CreateWindow("ANTS ACTUALLY DIE IN THE END",
									  SDL_WINDOWPOS_UNDEFINED,
									  SDL_WINDOWPOS_UNDEFINED,
									  things->width, things->height,
										 SDL_WINDOW_RESIZABLE)))
	{
		SDL_Quit();
		ft_error(SDL_GetError());
	}
//	if (!(things->renderer = SDL_CreateRenderer(things->win, -1, 0)) ||
//		!(things->floor = SDL_CreateRGBSurface(0, things->width, things->height, 32, 0, 0, 0, 0)))
//	{
//		SDL_Quit();
//		return (0);
//	}
	if (!(things->sur = SDL_GetWindowSurface(things->win)))
		ft_error(SDL_GetError());
	return (1);
}

/*SDL_Surface		*load_texture(char *path, t_wolf *wolf)
{
	SDL_Surface		*stock;
	SDL_Surface		*surface;

	stock = SDL_LoadBMP(path);
	if (stock == NULL)
	{
		ft_putstr("Error while loading a texture file\n");
		SDL_Quit();
		exit(1);
	}
	surface = SDL_ConvertSurfaceFormat(stock, wolf->surf->format->format, 0);
	SDL_FreeSurface(stock);
	return (surface);
}*/