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
	}

}
