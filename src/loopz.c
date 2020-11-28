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

static void		event_key_down(SDL_Event event,
							t_sdl_things *things, t_all_data *data)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_SPACE
	&& !things->ants_go_brrrr)
	{
		things->ants_go_brrrr = true;
		data->ants_reduced = false;
		while (things->step_progress <= 1)
		{
			draw_map(things, data);
			data->ants_reduced = true;
			SDL_RenderPresent(things->renderer);
			things->step_progress += 0.01;
			SDL_Delay(1000 / 200);
		}
		things->ants_go_brrrr = false;
		if (data->curr_step)
			data->curr_step = data->curr_step->next;
		things->step_progress = 0.01;
	}
}

static void		event_mousewheel(SDL_Event event,
							t_sdl_things *things, t_all_data *data)
{
	things->redraw = true;
	zoom(data, event, things);
	draw_map(things, data);
	SDL_RenderPresent(things->renderer);
	things->redraw = false;
}

void			loopz(t_sdl_things *things, t_all_data *data)
{
	SDL_Event	event;

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
			event_mousewheel(event, things, data);
		}
 		if (event.type == SDL_KEYDOWN)
		{
			event_key_down(event, things, data);
		}
	}
	clear_sdl(data, things);
	exit(0);
}
