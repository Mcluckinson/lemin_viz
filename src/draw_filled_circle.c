//
// Created by scump on 24.04.2020.
//

#include "lem_viz.h"

void draw_stoopid_line (int x, int y, int radius2, t_sdl_things *things)
{
	int radius = radius2 * 2;
	SDL_RenderDrawPoint(things->renderer, x, y);
	while (--radius > 0)
	if (y - radius > 0)
		SDL_RenderDrawPoint(things->renderer, x, y - radius);
	if (y + radius < DEFAULT_HEIGHT)
		SDL_RenderDrawPoint(things->renderer, x, y + radius);
}

void		draw_filled_circle(int x, int y, int radius, t_sdl_things *things)
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

void		test_draw_circle_line(int x0, int y0, int x1, int radius, t_sdl_things *things)
{
	int		x_buff;

	x_buff = x0;
	while (x_buff <= x1)
	{
		draw_filled_circle(x_buff, y0, radius, things);
		x_buff++;
	}
}

void		test_draw_neon_circle_line(int x0, int y, int x1, int radius, t_sdl_things *things)
{
	int		rad_buff = radius;
	float	percent_stuff;
	Uint8	red = 255;
	Uint8	green = 0;
	Uint8	blue = 255;
	Uint8	alpha = 255;

	while (rad_buff > 0)
	{
		percent_stuff = (float)rad_buff / (float)radius;
		green = 255 - 255 * percent_stuff;
		alpha = 0;
		SDL_SetRenderDrawColor(things->renderer, red, green, blue, alpha);///check alfa?
		test_draw_circle_line(x0, y, x1, rad_buff, things);
		rad_buff--;
	}
}
