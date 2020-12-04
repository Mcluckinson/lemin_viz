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

static void	draw_fat_horizontal_line_in_buff
	(t_xy x_y, int radius, t_sdl_things *things, Uint32 color)
{
	int counter;

	counter = -radius;
	while (counter < radius)
	{
		if (x_y.x + counter > 0 && x_y.x + counter < DEFAULT_WIDTH
		&& x_y.y > 0 && x_y.y < DEFAULT_HEIGHT)
			things->m_buffer1[x_y.y * DEFAULT_WIDTH + x_y.x + counter] = color;
		counter++;
	}
}

static void	draw_fat_vertical_line_in_buff
	(t_xy x_y, int radius, t_sdl_things *things, Uint32 color)
{
	int counter;

	counter = -radius;
	while (counter < radius)
	{
		if (x_y.y + counter > 0 && x_y.y + counter < DEFAULT_HEIGHT
		&& x_y.x > 0 && x_y.x < DEFAULT_WIDTH)
			things->m_buffer1[(x_y.y + counter)
			* DEFAULT_WIDTH + x_y.x] = color;
		counter++;
	}
}

static void	draw_line
	(t_drawing_things drawing_things, t_sdl_things *things, int steep, t_xy xy)
{
	int	buff;

	if (steep)
	{
		buff = xy.x;
		xy.x = xy.y;
		xy.y = buff;
		draw_fat_horizontal_line_in_buff(xy,
			drawing_things.radius, things, drawing_things.color);
	}
	else
		draw_fat_vertical_line_in_buff(xy,
			drawing_things.radius, things, drawing_things.color);
}

static void	swapity_swaps(int steep, t_drawing_things *drawing_things)
{
	if (steep)
	{
		swap_values(&drawing_things->x0, &drawing_things->y0);
		swap_values(&drawing_things->x1, &drawing_things->y1);
	}
	if (drawing_things->x0 > drawing_things->x1)
	{
		swap_values(&drawing_things->x1, &drawing_things->x0);
		swap_values(&drawing_things->y1, &drawing_things->y0);
	}
}

void		draw_brezenham_line_in_buff
	(t_sdl_things *things, t_drawing_things drawing_things)
{
	t_xy	d_xy;
	t_xy	xy;
	int		steep;
	int		error;
	int		ystep;

	steep = abs(drawing_things.y1 - drawing_things.y0) >
			abs(drawing_things.x1 - drawing_things.x0);
	swapity_swaps(steep, &drawing_things);
	d_xy.x = drawing_things.x1 - drawing_things.x0;
	d_xy.y = abs(drawing_things.y1 - drawing_things.y0);
	xy.x = drawing_things.x0 - 1;
	xy.y = drawing_things.y0;
	error = d_xy.x / 2;
	ystep = (drawing_things.y0 < drawing_things.y1) ? 1 : -1;
	while (++xy.x < drawing_things.x1)
	{
		draw_line(drawing_things, things, steep, xy);
		error -= d_xy.y;
		if (error < 0)
		{
			xy.y += ystep;
			error += d_xy.x;
		}
	}
}
