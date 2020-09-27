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

static int	draw_line(t_link *link, t_sdl_things *things)
{
	SDL_SetRenderDrawColor(things->renderer, 255, 0, 255, 0);
	draw_brezenham(link->room1->x, link->room1->y, link->room2->x, link->room2->y, 10, things);
	return (1);
}

int			draw_all_paths(t_sdl_things *things, t_all_data *data)
{
	t_link	*start;

	start = data->all_links;
	SDL_SetRenderTarget(things->renderer, things->background);//////
	if (SDL_SetRenderDrawColor(things->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE))
		ft_error(SDL_GetError());
	if (SDL_RenderClear(things->renderer))
		ft_error(SDL_GetError());
	while (start)
	{
		if (!draw_line(start, things))
			return (0);
		start = start->next;
	}
	test_draw_neon_circle_line(300, 500, 600, 20, things);
	SDL_SetRenderTarget(things->renderer, NULL);
	SDL_RenderCopy(things->renderer, things->background, NULL, NULL);////////this is for texture get it back
//	SDL_RenderPresent(things->renderer);
//	blur_v2(things);
//	SDL_UpdateWindowSurface(things->win);
	SDL_RenderPresent(things->renderer);
	return (1);
}

int			draw_all_paths2(t_sdl_things *things, t_all_data *data)
{
	draw_all_paths_b4_blur(things, data);
	blur_v4(things);
	draw_all_paths_after_blur(things, data);
	return (0);
}
