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

static t_drawing_things assemble_coords(t_room *start, t_room *end, t_drawing_things things)
{
	things.x0 = start->x;
	things.x1 = end->x;
	things.y0 = start->y;
	things.y1 = end->y;
	return (things);
}

void		draw_all_paths_b4_blur(t_sdl_things *things, t_all_data *data)
{
	t_link	*start;
	t_drawing_things drawing_things;

	start = data->all_links;
	drawing_things.color = 0xFF00FF;
	drawing_things.radius = things->radius;
	while (start)
	{
		drawing_things = assemble_coords(start->first_room, start->second_room, drawing_things);
		draw_brezenham_line_in_buff(things, drawing_things);
		start = start->next;
	}
}

void		draw_all_paths_after_blur(t_sdl_things *things, t_all_data *data)
{
	int		rad_buff = ((float)things->radius - (float)1 * things->zoom) * (things->zoom);
	float	percent_stuff;
	Uint8	red = 255;
	Uint8	green;
	Uint8	blue = 255;
	t_link	*start;
	t_drawing_things drawing_things;

	if (things->radius < 2)
		return ;
	drawing_things.radius = things->radius - 1;
	while (rad_buff > 0)
	{
		percent_stuff = (float)rad_buff / (float)things->radius;
		green = 255 - 255 * percent_stuff + 10;
		start = data->all_links;
		drawing_things.color = red << 16 | green << 8 | blue;
		while (start)
		{
			drawing_things = assemble_coords(start->first_room, start->second_room, drawing_things);
			draw_brezenham_line_in_buff(things, drawing_things);
			start = start->next;
		}
		rad_buff -= 1;
	}
}
