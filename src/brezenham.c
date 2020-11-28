/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:02:23 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 16:02:25 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

void	draw_brezenham(int x0, int y0, int x1, int y1, int radius, t_sdl_things *things)
{
	int	dx, dy, p, x, y;

	int steep = abs(y1 - y0) > abs(x1 - x0);

	if (steep)
	{

		y0 = (x0 + y0) - (x0 = y0);
		y1 = (x1 + y1) - (x1 = y1);
	}

	if (x0 > x1)
	{
		x1 = (x0 + x1) - (x0 = x1);
		y1 = (y0 + y1) - (y0 = y1);
	}

	dx = x1 - x0;
	dy = abs(y1 - y0);

	x = x0;
	y = y0;
	int error = dx / 2;
	int ystep = (y0 < y1) ? 1 : -1;

	while (x < x1)
	{
		draw_filled_circle(steep ? y : x, steep ? x : y, radius, things);
	//	draw_stoopid_line(steep ? y : x, steep ? x : y, radius, things);
		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
		x++;
	}
}
