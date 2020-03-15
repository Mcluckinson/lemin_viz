/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:56:21 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/15 16:29:18 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static int draw_line(t_link *link, t_sdl_things *things)
{
	//if (link->room1->is_part_of_path && link->room2->is_part_of_path)
//		SDL_GetRenderDrawColor(things->renderer, (Uint8*)112, (Uint8*)128, (Uint8*)144, (Uint8*)SDL_ALPHA_OPAQUE);
//	else
//		SDL_GetRenderDrawColor(things->renderer, (Uint8*)255, (Uint8*)0, (Uint8*)255, (Uint8*)SDL_ALPHA_OPAQUE);
	if (SDL_RenderDrawLine(things->renderer, link->room1->x, link->room1->y, link->room2->x, link->room2->y))
		ft_error(SDL_GetError());
//	SDL_RenderPresent(things->renderer);
	return (1);
}

int 	draw_all_paths(t_sdl_things *things, t_all_data *data)
{
	t_link *start;

	start = data->all_links;
	if (SDL_SetRenderDrawColor(things->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE))
		ft_error(SDL_GetError());
	if (SDL_RenderClear(things->renderer))
		ft_error(SDL_GetError());
	if (SDL_GetRenderDrawColor(things->renderer, (Uint8*)255, (Uint8*)0, (Uint8*)255, (Uint8*)SDL_ALPHA_OPAQUE))
		ft_error(SDL_GetError());
	while (start)
	{
		if (!draw_line(start, things))
			return (0);
		start = start->next;
	}
	SDL_RenderPresent(things->renderer);
	return (1);
}