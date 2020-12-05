/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_game_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:00:00 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/29 00:00:01 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static bool		add_gaem_textures(t_sdl_things *things)
{
	SDL_Surface	*surface;

	surface = IMG_Load("../rsrcs/bat_right.png");
	if (!surface)
		return (false);
	things->bat_right = SDL_CreateTextureFromSurface(things->renderer, surface);
	SDL_FreeSurface(surface);
	if (!things->bat_right)
		return (false);
	surface = IMG_Load("../rsrcs/bat_down.png");
	if (!surface)
		return (false);
	things->bat_down = SDL_CreateTextureFromSurface(things->renderer, surface);
	SDL_FreeSurface(surface);
	if (!things->bat_down)
		return (false);
	return (true);
}

void			loop_game_mode(t_sdl_things *things, t_all_data *data)
{
	SDL_Event	event;

	things->step_progress = 0.01;
	things->redraw = true;
	draw_map(things, data);
	SDL_RenderPresent(things->renderer);
	things->redraw = false;
	data->game_ants_left = data->ants;
	data->default_ants = data->ants;
	if (!add_gaem_textures(things))
		return ;
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				things->mouse_down = true;
				break ;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				things->ants_go_brrrr = true;
				break ;
			}
			if (event.type == SDL_MOUSEBUTTONUP)
				things->mouse_down = false;
			break ;
		}
		if (SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		if (things->step_progress == 0.01)
			data->ants_reduced = false;
		draw_map(things, data);
		if (things->ants_go_brrrr)///this and below can be reduced to only one if
			data->ants_reduced = true;
		SDL_RenderPresent(things->renderer);
		things->gaem_delay++;
		if (things->step_progress < 1 && things->ants_go_brrrr)
		{
			if (things->gaem_delay >= GAEM_DELAY)
			{
				things->gaem_delay = 0;
				things->step_progress += 0.01;
			}
		}
		if (things->step_progress >= 1 && things->ants_go_brrrr)
		{
			if (data->curr_step)
				data->curr_step = data->curr_step->next;
			things->step_progress = 0.01;
		}
	}
}