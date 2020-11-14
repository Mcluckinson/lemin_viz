//
// Created by Carly Yuriko on 11/8/20.
//

#include "lem_viz.h"

void 	draw_map(t_sdl_things *things, t_all_data *data)
{
	ft_bzero(things->m_buffer1, sizeof(Uint32) * DEFAULT_WIDTH * DEFAULT_HEIGHT);
	draw_all_paths_b4_blur(things, data);
//	blur_v4(things);
//	fastend_blur(things);
//	draw_all_paths_after_blur(things, data);
	initial_ants(things, data);
	buff_to_texture(things);


}