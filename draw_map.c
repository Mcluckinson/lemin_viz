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

int			draw_all_paths2(t_sdl_things *things, t_all_data *data)
{
	SDL_SetRenderDrawColor( things->renderer, 0, 0, 0, 0xFF );
	SDL_RenderClear(things->renderer);
	ft_bzero(things->m_buffer1, sizeof(Uint32) * DEFAULT_HEIGHT * DEFAULT_WIDTH);
	ft_bzero(things->m_buffer2, sizeof(Uint32) * DEFAULT_HEIGHT * DEFAULT_WIDTH);
	draw_all_paths_b4_blur(things, data);
	blur_v4(things);
	draw_all_paths_after_blur(things, data);
	return (0);
}
