

#include "lem_viz.h"

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

