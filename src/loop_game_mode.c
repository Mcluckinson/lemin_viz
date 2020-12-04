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

	while (1)
	{
		SDL_PollEvent(&event);
		if (SDLK_ESCAPE == event.key.keysym.sym)
			break ;
//		if ()
		if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			things->ants_go_brrrr = true;
		if (things->step_progress == 0.01)
			data->ants_reduced = false;
		draw_map(things, data);
		if (things->ants_go_brrrr)///this and below can be reduced to only one if
			data->ants_reduced = true;
		SDL_RenderPresent(things->renderer);
		if (things->step_progress < 1 && things->ants_go_brrrr)
			things->step_progress += 0.01;
		SDL_Delay(1000 / 60);
		if (things->step_progress >= 1 && things->ants_go_brrrr)
		{
			if (data->curr_step)
				data->curr_step = data->curr_step->next;
			things->step_progress = 0.01;
		}
	}
}