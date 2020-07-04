#include "lem_viz.h"


/*
 * SET COLOR FIRST
 */
int 	draw_circle(int x, int y, int rad, t_sdl_things *things)
{
	int 	x_point;
	int 	y_point;
	int 	error;
	int 	delta;

	x_point = 0;
	y_point = rad;
	error = 0;
	delta = 1 - 2 * rad;
	while (y_point >= 0)
	{
		SDL_RenderDrawPoint(things->renderer, x + x_point, y + y_point);
		SDL_RenderDrawPoint(things->renderer, x + x_point, y - y_point);
		SDL_RenderDrawPoint(things->renderer, x - x_point, y + y_point);
		SDL_RenderDrawPoint(things->renderer, x - x_point, y - y_point);
		error = 2 * (delta + y_point) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++x_point + 1;
			continue;
		}
		else if ((delta > 0) && (error > 0))
		{
			delta -= 2 * --y_point + 1;
			continue;
		}
		delta += 2 * (++x_point - y_point--);
	}
	return (0);
}

int 	draw_neon_circle(int x, int y, int radius, t_sdl_things *things)
{
	float percent;
	int 	r_radius;

	r_radius = 0;
	percent = 1;
	SDL_SetRenderDrawColor(things->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(things->renderer, x, y);

	while (++r_radius <= radius)
	{
		percent = (float)r_radius / (float)radius;
		printf("|%fd\n|", percent);
		float c = (float)255 - (float)255 * percent;

		SDL_SetRenderDrawColor(things->renderer, c, 0, c, SDL_ALPHA_OPAQUE);
		draw_circle(x, y, r_radius, things);
	}
	return (0);
}

