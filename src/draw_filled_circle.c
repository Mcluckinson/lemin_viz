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

void	draw_filled_circle(int x, int y, int radius, t_sdl_things *things)
{
	int	xoff;
	int	yoff;
	int	balance;
	int	p0;
	int	p1;
	int	w0;
	int	w1;

	xoff = 0;
	yoff = radius;
	balance = -radius;
	while (xoff <= yoff)
	{
		p0 = x - xoff;
		p1 = x - yoff;
		w0 = xoff + xoff;
		w1 = yoff + yoff;
		SDL_RenderDrawLine(things->renderer, p0, y + yoff, p0 + w0, y + yoff);//1
		SDL_RenderDrawLine(things->renderer, p0, y - yoff, p0 + w0, y - yoff);//2
		SDL_RenderDrawLine(things->renderer, p1, y + xoff, p1 + w1, y + xoff);//3
		SDL_RenderDrawLine(things->renderer, p1, y - xoff, p1 + w1, y - xoff);//4
		if ((balance += (xoff + xoff + 1)) >= 0)
		{
			yoff--;
			balance -= (yoff + yoff);
		}
		xoff++;
	}
}
