/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_filled_circle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:50:48 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 15:50:50 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void	draw_line(t_sdl_things *things, t_xy res, int xoff, int yoff)
{
	int		p0;
	int		p1;
	int		w0;
	int		w1;

	p0 = res.x - xoff;
	p1 = res.x - yoff;
	w0 = xoff + xoff;
	w1 = yoff + yoff;
	SDL_RenderDrawLine(things->renderer, p0, res.y + yoff,
					p0 + w0, res.y + yoff);
	SDL_RenderDrawLine(things->renderer, p0, res.y - yoff,
					p0 + w0, res.y - yoff);
	SDL_RenderDrawLine(things->renderer, p1, res.y + xoff,
					p1 + w1, res.y + xoff);
	SDL_RenderDrawLine(things->renderer, p1, res.y - xoff,
					p1 + w1, res.y - xoff);
}

void		draw_filled_circle(int x, int y, int radius, t_sdl_things *things)
{
	int		xoff;
	int		yoff;
	int		balance;
	t_xy	res;

	xoff = 0;
	yoff = radius;
	balance = -radius;
	res.x = x;
	res.y = y;
	while (xoff <= yoff)
	{
		draw_line(things, res, xoff, yoff);
		if ((balance += (xoff + xoff + 1)) >= 0)
		{
			yoff--;
			balance -= (yoff + yoff);
		}
		xoff++;
	}
}
