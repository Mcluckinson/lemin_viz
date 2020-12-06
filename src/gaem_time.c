/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaem_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:59:20 by cyuriko           #+#    #+#             */
/*   Updated: 2020/12/05 17:59:22 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static bool		find_ant(t_xy mouse_coords, t_xy current_coords, int radius)
{
	if (current_coords.x < mouse_coords.x + radius
	&& current_coords.x > mouse_coords.x - radius
	&& current_coords.y < mouse_coords.y + radius
	&& current_coords.y > mouse_coords.y - radius)
		return (true);
	return (false);
}

static void		delete_ant(t_all_data *data, int ant_num)
{
	t_step_line	*counter;
	t_step		*terminator;
	t_step		*connor;

	counter = data->all_steps;
	while (counter)
	{
		terminator = counter->stepz;
		connor = counter->stepz;
		while (terminator)
		{
			if (terminator->ant_num == ant_num)
			{
				if (terminator == connor)
					counter->stepz = terminator->next;
				else
					connor->next = terminator->next;
				ft_memdel((void**)&terminator);
				break ;
			}
			connor = (terminator != connor) ? connor->next : connor;
			terminator = terminator->next;
		}
		counter = counter->next;
	}
}

bool			delete_cheemz(int ant_num,
	t_all_data *data, t_xy cheemz_coords, t_sdl_things *things)
{
	t_xy	mouse_coords;
	bool	should_kill;
	int		radius;

	radius = things->radius * 15;
	SDL_GetMouseState(&mouse_coords.x, &mouse_coords.y);
	if ((mouse_coords.x < data->start->x + radius &&
			mouse_coords.x > data->start->x - radius && mouse_coords.y >
			data->start->y - radius && mouse_coords.y < data->start->y + radius)
			|| (mouse_coords.x < data->end->x + radius &&
				mouse_coords.x > data->end->x - radius
				&& mouse_coords.y > data->end->y - radius
				&& mouse_coords.y < data->end->y + radius))
		return (false);
	should_kill = find_ant(mouse_coords, cheemz_coords, radius / 15 * 11);
	if (should_kill)
	{
		data->game_ants_left--;
		delete_ant(data, ant_num);
	}
	return (should_kill);
}
