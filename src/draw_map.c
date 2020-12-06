/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:50:48 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 15:50:50 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void	draw_win(t_sdl_things *things)
{
	SDL_Rect	cheemz_frame;

	cheemz_frame.h = DEFAULT_HEIGHT / 2;
	cheemz_frame.w = DEFAULT_WIDTH / 2;
	cheemz_frame.x = DEFAULT_WIDTH / 2 - cheemz_frame.w / 2;
	cheemz_frame.y = DEFAULT_HEIGHT / 2 - cheemz_frame.h / 2;
	SDL_RenderCopy(things->renderer, things->u_win, NULL, &cheemz_frame);
}

static void	draw_looz(t_sdl_things *things)
{
	SDL_Rect	cheemz_frame;
	SDL_Rect	looz_frame;

	looz_frame.h = DEFAULT_HEIGHT / 2;
	looz_frame.w = DEFAULT_WIDTH / 2;
	looz_frame.x = DEFAULT_WIDTH / 2 - looz_frame.w / 2;
	looz_frame.y = DEFAULT_HEIGHT / 2 - looz_frame.h / 2;
	SDL_RenderCopy(things->renderer, things->u_looz, NULL, &looz_frame);
	cheemz_frame.h = DEFAULT_HEIGHT / 8;
	cheemz_frame.h = DEFAULT_HEIGHT / 2;
	cheemz_frame.w = DEFAULT_WIDTH / 2;
	cheemz_frame.x = DEFAULT_WIDTH - cheemz_frame.w / 1.4;
	cheemz_frame.y = DEFAULT_HEIGHT - cheemz_frame.h / 1.4;
	SDL_RenderCopy(things->renderer, things->cryin, NULL, &cheemz_frame);
}

static void	redraw_map(t_sdl_things *things, t_all_data *data)
{
	ft_bzero(things->m_buffer1,
		sizeof(Uint32) * (DEFAULT_WIDTH * DEFAULT_HEIGHT));
	draw_all_paths_b4_blur(things, data);
	blur_v4(things);
	draw_all_paths_after_blur(things, data);
	buff_to_texture(things);
}

void		draw_map(t_sdl_things *things, t_all_data *data)
{
	SDL_RenderClear(things->renderer);
	if (things->redraw)
		redraw_map(things, data);
	SDL_RenderCopy(things->renderer, things->texture, NULL, NULL);
	draw_roomz(things, data);
	if (things->ants_go_brrrr && data->curr_step)
		draw_step(things, data);
	if ((!things->ants_go_brrrr && data->curr_step) ||
	(things->ants_go_brrrr && data->curr_step && things->step_progress == 1))
	{
		if (data->curr_step != data->all_steps)
			finish_step(things, data);
	}
	if (data->ants > 0)
		initial_ants(things, data);
	if (things->game_mode)
	{
		draw_baseball_bat(things);
		draw_progress_bar(things, data);
		draw_horni_sign(things, data);
		if (!data->game_ants_left)
			draw_win(things);
		if (data->curr_step == NULL && data->game_ants_left)
			draw_looz(things);
	}
}
