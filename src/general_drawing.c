/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:51:13 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 15:51:15 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

void		buff_to_texture(t_sdl_things *things)
{
	int		x;
	int		y;
	Uint32	color;

	SDL_SetRenderTarget(things->renderer, things->texture);
	SDL_SetRenderDrawColor(things->renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(things->renderer);
	y = -1;
	while (++y < DEFAULT_HEIGHT)
	{
		x = -1;
		while (++x < DEFAULT_WIDTH)
		{
			color = things->m_buffer1[y * DEFAULT_WIDTH + x];
			SDL_SetRenderDrawColor(things->renderer, color,
						color >> 8, color >> 16, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(things->renderer, x, y);
		}
	}
	SDL_SetRenderTarget(things->renderer, NULL);
}
