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

void	blur_v4(t_sdl_things *things)
{
	if (things->radius < 2)
		return ;
	Uint32 *temp = things->m_buffer1;
	things->m_buffer1 = things->m_buffer2;
	things->m_buffer2 = temp;

	Uint32 color;
	int current_x = 0;
	int current_y = 0;
	int y = -1;
	int x;
	int box_blur_x;
	int extent = 3;
	Uint8 red = 0, green = 0, blue = 0;
	int redTotal, greenTotal, blueTotal;
	while (y++ < things->height)
	{
		x = -1;
		while (x++ < things->width)
		{
			box_blur_x = -extent - 1;
			redTotal = 0;
			greenTotal = 0;
			blueTotal = 0;
			while (box_blur_x++ <= extent)
			{
				current_x = x + box_blur_x;
				current_y = y;

				if (y >= 0 && x + box_blur_x >= 0 &&
				y < things->height && x + box_blur_x < things->width)
				{
					color = things->m_buffer2[current_y * things->width + current_x];
					red = color;
					green = color >> 8;
					blue = color >> 16;

					redTotal += red;
					greenTotal += green;
					blueTotal += blue;
				}
				red = redTotal / 9;
				green = greenTotal / 9;
				blue = blueTotal / 9;
			}
			color = red  | green << 8 | blue << 16;
			things->m_buffer1[y * things->width + x] = color;
		}
	}
}
