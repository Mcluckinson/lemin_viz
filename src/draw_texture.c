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

bool			load_cheemz(t_sdl_things *things)
{
	SDL_Surface	*surface;

	surface = IMG_Load("../rsrcs/cheems.png");
	if (!surface)
		return (false);
	things->cheems = SDL_CreateTextureFromSurface(things->renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("../rsrcs/room.png");
	if (!surface)
		return (false);
	things->roomz = SDL_CreateTextureFromSurface(things->renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("../rsrcs/end.png");
	if (!surface)
		return (false);
	things->end = SDL_CreateTextureFromSurface(things->renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("../rsrcs/start.png");
	if (!surface)
		return (false);
	things->start = SDL_CreateTextureFromSurface(things->renderer, surface);
	SDL_FreeSurface(surface);
	if (!things->cheems || !things->roomz)
		return (false);
	return (true);
}

void			draw_cheemz(t_sdl_things *things, int x, int y)
{
	SDL_Rect	cheemz_frame;

	cheemz_frame.h = things->radius * 8;
	cheemz_frame.w = things->radius * 8;
	cheemz_frame.x = x - cheemz_frame.w / 2;
	cheemz_frame.y = y - cheemz_frame.h / 2;
	SDL_RenderCopy(things->renderer, things->cheems, NULL, &cheemz_frame);
}

void			draw_roomz(t_sdl_things *things, t_all_data *data)
{
	SDL_Rect	cheemz_frame;
	t_room		*counter;

	counter = data->all_rooms;
	cheemz_frame.h = things->radius * 30;
	cheemz_frame.w = things->radius * 30;
	while (counter)
	{
		cheemz_frame.x = counter->x - cheemz_frame.w / 2;
		cheemz_frame.y = counter->y - cheemz_frame.h / 2;
		if (counter == data->start)
			SDL_RenderCopy(things->renderer,
					things->start, NULL, &cheemz_frame);
		else if (counter == data->end)
			SDL_RenderCopy(things->renderer, things->end, NULL, &cheemz_frame);
		else
			SDL_RenderCopy(things->renderer,
				things->roomz, NULL, &cheemz_frame);
		counter = counter->next;
	}
}

void 			finish_step(t_sdl_things *things, t_all_data *data)
{
	t_step *counter;

	counter = data->curr_step->stepz;
	while (counter)
	{
		draw_cheemz(things, counter->room->x, counter->room->y);
		counter = counter->next;
	}
}
