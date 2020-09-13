//
// Created by scump on 05.05.2020.
//

#include "lem_viz.h"

void	draw_line_in_buff(Uint32 color, Uint32 *buff, int x0, int x1, int y, t_sdl_things *things)
{
	int x;
	int side;

	x = x0;
	side = x0 < x1 ? 1 : -1;
	while (x != x1)
	{
		if (x >= 0 && x < things->width && y >= 0 && y < things->height)
			buff[y * things->width + x] = color;
		x += side;
	}
}

void 	draw_filled_circle_in_buff(int x, int y, int radius, t_sdl_things *things, Uint32 color)
{
	int xoff = 0;
	int yoff = radius;
	int balance = -radius;

	int p0;
	int p1;
	int w0;
	int w1;
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
			balance-= (yoff + yoff);
		}
		xoff++;
	}
}

void 	draw_brezenham_line_in_buff(t_sdl_things *things, int x0, int y0, int x1, int y1, Uint32 color, Uint32 *buff, int radius)
{
	int dx, dy, p, x, y;


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

	dx=x1-x0;
	dy=abs(y1-y0);

	x=x0;
	y=y0;
	int error = dx / 2;
	int ystep = (y0 < y1) ? 1 : -1;

	while(x<x1)
	{
	//	draw_filled_circle(steep ? y : x, steep ? x : y, radius, things);
		draw_filled_circle_in_buff(steep ? y : x, steep ? x : y, radius, things, color);
		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
		x++;
	}
}

void 	draw_all_paths_b4_blur(t_sdl_things *things, t_all_data *data)
{
	Uint32 *buff = things->m_buffer1;
	t_link *start = data->all_links;;

	Uint32 color = 0xFF00FF;
//	Uint32 color = 16711935;
	while (start)
	{
		draw_brezenham_line_in_buff(things, start->room1->x, start->room1->y, start->room2->x, start->room2->y, color, buff, things->radius);
		start = start->next;
	}
}

void	draw_all_paths_after_blur(t_sdl_things *things, t_all_data *data)
{
	float 	rad_buff = ((float)things->radius - 1 * things->zoom) * ((!things->zoom ? 1 : things->zoom));///////////this should be in structure and changeable
	float	percent_stuff;
	Uint8	red = 255;
	Uint8	green = 0;
	Uint8	blue = 255;
	Uint8	alpha = 255;
	t_link	*start = data->all_links;

	while (rad_buff > things->zoom)
	{
		percent_stuff = (float)rad_buff / (float)things->radius;
		green = 255 - 255 * percent_stuff + 10;
		alpha = 0;
		SDL_SetRenderDrawColor(things->renderer, red, green, blue, alpha);///check alfa?
		start = data->all_links;
		while (start)
		{
			draw_brezenham(start->room1->x, start->room1->y, start->room2->x, start->room2->y, rad_buff, things);
			start = start->next;
		}
		rad_buff -= (float)0.9;
	}
}
