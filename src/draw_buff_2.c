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

static void		draw_line_in_buff(Uint32 color, Uint32 *buff, int x0, int x1, int y, t_sdl_things *things)
{
	int		x;
	int		side;

	x = x0;
	side = x0 < x1 ? 1 : -1;
	while (x != x1)
	{
		if (x >= 0 && x < things->width && y >= 0 && y < things->height)
			buff[y * things->width + x] = color;
		x += side;
	}
}

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

void		draw_filled_circle_in_buff(int x, int y, int radius, t_sdl_things *things, Uint32 color)
{
	int		xoff = 0;
	int		yoff = radius;
	int		balance = -radius;

	int		p0;
	int		p1;
	int		w0;
	int		w1;
	while (xoff <= yoff)
	{
		p0 = x - xoff;
		p1 = x - yoff;
		w0 = xoff + xoff;
		w1 = yoff + yoff;
		draw_line_in_buff(color, things->m_buffer1, p0, p0 + w0, y + yoff, things);
		draw_line_in_buff(color, things->m_buffer1, p0, p0 + w0, y - yoff, things);
		draw_line_in_buff(color, things->m_buffer1, p1, p1 + w1, y + xoff, things);
		draw_line_in_buff(color, things->m_buffer1, p1, p1 + w1, y - xoff, things);
		if ((balance += (xoff + xoff + 1)) >= 0)
		{
			yoff--;
			balance -= (yoff + yoff);
		}
		xoff++;
	}
}
