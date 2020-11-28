/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loopz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:51:29 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 15:51:30 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_viz.h"

void 	loopz(t_sdl_things *things, t_all_data *data)
{
	SDL_Event		event;

	things->step_progress = 0.01;
	things->redraw = true;
	draw_map(things, data);
	SDL_RenderPresent(things->renderer);
	things->redraw = false;
	while (SDL_WaitEvent(&event))
	{
		if (SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		if (event.type == SDL_MOUSEWHEEL && !things->ants_go_brrrr)
		{
			things->redraw = true;
			zoom(data, event, things);
			draw_map(things, data);
			SDL_RenderPresent(things->renderer);
			things->redraw = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && !things->ants_go_brrrr)
			{
				things->ants_go_brrrr = true;
				while (things->step_progress <= 1)
				{
					draw_map(things, data);
					SDL_RenderPresent(things->renderer);
					things->step_progress += 0.01;
					SDL_Delay(1000 / 60);
				}
				data->curr_step = data->curr_step->next;
				things->ants_go_brrrr = false;
				things->step_progress = 0.01;
			}
		}

	}
	///the thing below should be performed by a ft_error funtion, update it to clear t_sdl_things and t_all_data_whatever_it's called
	///destroy textures and shit
	clear_sdl(data, things);
	exit(0);
}
