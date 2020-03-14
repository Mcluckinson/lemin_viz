/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:45:36 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 18:04:36 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

void 	find_win_size(t_all_data *data, t_sdl_things *things)
{
	t_room *room;
	int		x_max;
	int		x_min;
	int		y_max;
	int		y_min;

	x_max = DEFAULT_WIDTH;
	x_min = 0;
	y_max = DEFAULT_HEIGHT;
	y_min = 0;
	room = data->all_rooms;
	while (room)
	{
		x_max = (x_max < room->x ? room->x : x_max);
		x_min = (x_min > room->x ? room->x : x_min);
		y_max = (y_max < room->y ? room->y : y_max);
		y_min = (y_min > room->y ? room->y : y_min);
		room = room->next;
	}
	things->width = x_max - x_min;
	things->height = y_max - y_min;
}



void	find_parts_of_paths(t_all_data *data)
{

}