#include "lem_viz.h"

static void draw_bar_texture(t_sdl_things *things, int x, int y)
{
	SDL_Rect	cheemz_frame;

	cheemz_frame.h = things->radius * 8;
	cheemz_frame.w = things->radius * 8;
	cheemz_frame.x = x - cheemz_frame.w / 2;
	cheemz_frame.y = y - cheemz_frame.h / 2;
	SDL_RenderCopy(things->renderer, things->start, NULL, &cheemz_frame);
}

void 	draw_progress_bar(t_sdl_things *things, t_all_data *data)
{
	int 	progress;
	int		x;
	int 	y;
	int 	elem_width = things->radius * 100;

	y = DEFAULT_HEIGHT - 15;
	x = DEFAULT_WIDTH / 2 - elem_width / 2;
	progress = ((double)data->game_ants_left / (double)data->default_ants) * 100;
	while (progress > 0)
	{
		draw_bar_texture(things, x, y);
		x += things->radius;
		progress--;
	}
}