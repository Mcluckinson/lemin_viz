/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_v4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:02:35 by cyuriko           #+#    #+#             */
/*   Updated: 2020/11/28 16:02:37 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void		swap_buffs(t_sdl_things *things)
{
	Uint32 *tmp;

	tmp = things->m_buffer1;
	things->m_buffer1 = things->m_buffer2;
	things->m_buffer2 = tmp;
}

static void		init_params
	(int *red_total, int *green_total, int *blue_total, int *box_blur_x)
{
	*red_total = 0;
	*green_total = 0;
	*blue_total = 0;
	*box_blur_x = -BLUR_EXTENT - 1;
}

static bool		check_coords(t_sdl_things *things, int box_blur_x)
{
	if (things->xy.y >= 0 && things->xy.x + box_blur_x >= 0 &&
		things->xy.y < DEFAULT_HEIGHT
		&& things->xy.x + box_blur_x < DEFAULT_WIDTH)
		return (true);
	return (false);
}

static void		update_color
	(Uint8 *red, Uint8 *green, Uint8 *blue, t_sdl_things *things)
{
	Uint32	color;
	int		box_blur_x;
	int		red_total;
	int		green_total;
	int		blue_total;

	init_params(&red_total, &blue_total, &green_total, &box_blur_x);
	while (box_blur_x++ <= BLUR_EXTENT)
	{
		if (check_coords(things, box_blur_x))
		{
			color = things->m_buffer2[things->xy.y
					* DEFAULT_WIDTH + things->xy.x + box_blur_x];
			*red = color;
			*green = color >> 8;
			*blue = color >> 16;
			red_total += *red;
			green_total += *green;
			blue_total += *blue;
		}
		*red = red_total / 9;
		*green = green_total / 9;
		*blue = blue_total / 9;
	}
}

void			blur_v4(t_sdl_things *things)
{
	t_xy	xy;
	Uint8	red;
	Uint8	green;
	Uint8	blue;

	if (things->radius < 2)
		return ;
	swap_buffs(things);
	xy.y = -1;
	while (xy.y++ < DEFAULT_HEIGHT)
	{
		xy.x = -1;
		while (xy.x++ < DEFAULT_WIDTH)
		{
			things->xy = xy;
			update_color(&red, &green, &blue, things);
			things->m_buffer1[xy.y * DEFAULT_WIDTH + xy.x] =
					red | green << 8 | blue << 16;
		}
	}
}
