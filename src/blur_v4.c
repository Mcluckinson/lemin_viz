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

static void 	swap_buffs(t_sdl_things *things)
{
	Uint32 *tmp;

	tmp = things->m_buffer1;
	things->m_buffer1 = things->m_buffer2;
	things->m_buffer2 = tmp;
}

void	blur_v4(t_sdl_things *things)
{

	swap_buffs(things);
	int current_x;
	int current_y;
	int y = -1;
	int x;
	int box_blur_x;
	Uint8 red, green, blue;
	int redTotal, greenTotal, blueTotal;

	if (things->radius < 2)
		return ;
	while (y++ < things->height)
	{
		x = -1;
		while (x++ < things->width)
		{
			box_blur_x = -BLUR_EXTENT - 1;
			redTotal = 0;
			greenTotal = 0;
			blueTotal = 0;
			while (box_blur_x++ <= BLUR_EXTENT)
			{
				current_x = x + box_blur_x;
				current_y = y;

				if (y >= 0 && x + box_blur_x >= 0 &&
				y < things->height && x + box_blur_x < things->width)
				{
					red = things->m_buffer2[current_y * things->width + current_x];
					green = red >> 8;
					blue = red >> 16;

					redTotal += red;
					greenTotal += green;
					blueTotal += blue;
				}
				red = redTotal / 9;
				green = greenTotal / 9;
				blue = blueTotal / 9;
			}
			things->m_buffer1[y * things->width + x] = red  | green << 8 | blue << 16;
		}
	}
}
