/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:01:55 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 16:01:56 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void draw_fat_horizontal_line_in_buff(int x, int y, int radius, t_sdl_things *things, Uint32 color)
{
	int counter;

	counter = -radius;
	while (counter < radius)
	{
		if (x + counter > 0 && x + counter < DEFAULT_WIDTH && y > 0 && y < DEFAULT_HEIGHT)
			things->m_buffer1[y * DEFAULT_WIDTH + x + counter] = color;
		counter++;
	}
}

static void draw_fat_vertical_line_in_buff(int x, int y, int radius, t_sdl_things *things, Uint32 color)
{
	int counter;

	counter = -radius;
	while (counter < radius)
	{
		if (y + counter > 0 && y + counter < DEFAULT_HEIGHT && x > 0 && x < DEFAULT_WIDTH)
			things->m_buffer1[(y + counter) * DEFAULT_WIDTH + x] = color;
		counter++;
	}
}

void 		draw_brezenham_line_in_buff(t_sdl_things *things, t_drawing_things drawing_things)
{
	int		dx, dy, x, y;
	int steep = abs(drawing_things.y1 - drawing_things.y0) > abs(drawing_things.x1 - drawing_things.x0);

	if (steep)
	{
		swap_values(&drawing_things.x0, &drawing_things.y0);
		swap_values(&drawing_things.x1, &drawing_things.y1);
	}
	if (drawing_things.x0 > drawing_things.x1)
	{
		swap_values(&drawing_things.x1, &drawing_things.x0);
		swap_values(&drawing_things.y1, &drawing_things.y0);
	}
	dx = drawing_things.x1 - drawing_things.x0;
	dy = abs(drawing_things.y1 - drawing_things.y0);
	x = drawing_things.x0;
	y = drawing_things.y0;
	int error = dx / 2;
	int ystep = (drawing_things.y0 < drawing_things.y1) ? 1 : -1;
	while(x < drawing_things.x1)
	{
		steep ? draw_fat_horizontal_line_in_buff(steep ? y : x, steep ? x : y, drawing_things.radius, things, drawing_things.color)
		: draw_fat_vertical_line_in_buff(steep ? y : x, steep ? x : y, drawing_things.radius, things, drawing_things.color);
		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
		x++;
	}
}
