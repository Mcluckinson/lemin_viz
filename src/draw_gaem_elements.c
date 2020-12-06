/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gaem_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 18:00:28 by cyuriko           #+#    #+#             */
/*   Updated: 2020/12/05 18:00:30 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void		draw_bar_texture(t_sdl_things *things, int x, int y)
{
	SDL_Rect	cheemz_frame;

	cheemz_frame.h = things->radius * 8;
	cheemz_frame.w = things->radius * 8;
	cheemz_frame.x = x - cheemz_frame.w / 2;
	cheemz_frame.y = y - cheemz_frame.h / 2;
	SDL_RenderCopy(things->renderer, things->start, NULL, &cheemz_frame);
}

void			draw_progress_bar(t_sdl_things *things, t_all_data *data)
{
	int	progress;
	int	x;
	int	y;
	int	elem_width;

	elem_width = things->radius * 100;
	y = DEFAULT_HEIGHT - 15;
	x = DEFAULT_WIDTH / 2 - elem_width / 2;
	progress =
			((double)data->game_ants_left / (double)data->default_ants) * 100;
	while (progress > 0)
	{
		draw_bar_texture(things, x, y);
		x += things->radius;
		progress--;
	}
}

static void		fix_bat_coords(SDL_Rect *cheemz_frame)
{
	int max_y;
	int max_x;

	max_y = DEFAULT_HEIGHT - cheemz_frame->h;
	max_x = DEFAULT_WIDTH - cheemz_frame->w;
	cheemz_frame->x -= cheemz_frame->w / 2;
	cheemz_frame->y -= cheemz_frame->h / 2;
	if (cheemz_frame->x < 1)
		cheemz_frame->x = 1;
	if (cheemz_frame->y < 1)
		cheemz_frame->y = 1;
	if (cheemz_frame->x > max_x - 1)
		cheemz_frame->x = max_x - 1;
	if (cheemz_frame->y > max_y - 1)
		cheemz_frame->y = max_y - 1;
}

void			draw_baseball_bat(t_sdl_things *things)
{
	SDL_Rect	cheemz_frame;

	cheemz_frame.h = DEFAULT_HEIGHT / 16 / 5 * things->radius;
	cheemz_frame.w = cheemz_frame.h;
	SDL_GetMouseState(&cheemz_frame.x, &cheemz_frame.y);
	cheemz_frame.x -= cheemz_frame.w / 2;
	cheemz_frame.y -= cheemz_frame.h / 2;
	if (things->mouse_down)
	{
		cheemz_frame.w = sqrt(2) * cheemz_frame.h;
		fix_bat_coords(&cheemz_frame);
		SDL_RenderCopy(things->renderer, things->bat_down, NULL, &cheemz_frame);
	}
	else
	{
		fix_bat_coords(&cheemz_frame);
		SDL_RenderCopy(things->renderer,
			things->bat_right, NULL, &cheemz_frame);
	}
}

void			draw_horni_sign(t_sdl_things *things, t_all_data *data)
{
	SDL_Rect	cheemz_frame;

	cheemz_frame.h = things->radius * 40;
	cheemz_frame.w = things->radius * 40;
	cheemz_frame.x = data->end->x;
	cheemz_frame.y = data->end->y - cheemz_frame.h;
	SDL_RenderCopy(things->renderer, things->horni_land, NULL, &cheemz_frame);
}
