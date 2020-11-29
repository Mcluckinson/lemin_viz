/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buff_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:28:36 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/29 14:28:37 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_drawing_things		assemble_coords(t_room *start,
t_room *end, t_drawing_things things)
{
	things.x0 = start->x;
	things.x1 = end->x;
	things.y0 = start->y;
	things.y1 = end->y;
	return (things);
}

void						draw_all_paths_b4_blur
	(t_sdl_things *things, t_all_data *data)
{
	t_link				*start;
	t_drawing_things	drawing_things;

	start = data->all_links;
	drawing_things.color = 0xFF00FF;
	drawing_things.radius = things->radius;
	while (start)
	{
		drawing_things = assemble_coords(start->first_room,
							start->second_room, drawing_things);
		draw_brezenham_line_in_buff(things, drawing_things);
		start = start->next;
	}
}

static SDL_Color			update_color(float percent_stuff)
{
	SDL_Color this;

	this.b = 255;
	this.r = 255;
	this.g = 255 - 255 * percent_stuff + 10;
	return (this);
}

void						draw_all_paths_after_blur
	(t_sdl_things *things, t_all_data *data)
{
	int					rad_buff;
	float				percent_stuff;
	SDL_Color			color;
	t_link				*start;
	t_drawing_things	drawing_things;

	rad_buff = ((float)things->radius -
			(float)1 * things->zoom) * (things->zoom);
	if (things->radius < 2)
		return ;
	drawing_things.radius = things->radius - 1;
	while (--rad_buff > 0)
	{
		percent_stuff = (float)rad_buff / (float)things->radius;
		color = update_color(percent_stuff);
		start = data->all_links;
		drawing_things.color = color.r << 16 | color.g << 8 | color.b;
		while (start)
		{
			drawing_things = assemble_coords(start->first_room,
									start->second_room, drawing_things);
			draw_brezenham_line_in_buff(things, drawing_things);
			start = start->next;
		}
	}
}
