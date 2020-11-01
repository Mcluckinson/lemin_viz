//
// Created by Carly Yuriko on 10/18/20.
//

#include "lem_viz.h"



void 	pulse_map(t_sdl_things *env, t_all_data *data)
{
	env->radius = (env->radius == env->original_radius ? env->original_radius + 1 : env->original_radius);
//	render_background(env);
	draw_all_paths2(env, data);
	SDL_RenderPresent(env->renderer);
}