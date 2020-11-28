/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants_steps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:56:29 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 16:56:29 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static int		find_ant_to_move(t_step_line *old_step, t_step_line *new_step)
{
	t_step		*old_counter;
	t_step		*new_counter;

	old_counter = old_step->stepz;
	new_counter = new_step->stepz;
	while (new_counter)
	{
		if (new_counter->was_started)
		{
			new_counter = new_counter->next;
			continue ;
		}
		while (old_counter)
		{
			if (old_counter->ant_num == new_counter->ant_num)
			{
				new_counter->was_started = true;
				return (new_counter->ant_num);
			}
			old_counter = old_counter->next;
		}
		new_counter = new_counter->next;
	}
	return (0);
}

static t_step	*find_da_step_4_ant(t_step_line *step_line, int ant_num)
{
	t_step		*finder;

	finder = step_line->stepz;
	while (finder)
	{
		if (finder->ant_num == ant_num)
			break ;
		finder = finder->next;
	}
	return (finder);
}

static t_xy		find_x_y(t_sdl_things *things, t_step_line *old_step,
					t_step_line *new_step, int ant_num)
{
	t_xy		coords;
	t_step		*old;
	t_step		*new;
	t_room		*start;

	old = find_da_step_4_ant(old_step, ant_num);
	new = find_da_step_4_ant(new_step, ant_num);
	start = old->room;
	coords.x = start->x + (new->room->x - start->x) * things->step_progress;
	coords.y = start->y + (new->room->y - start->y) * things->step_progress;
	return (coords);
}

bool			try_step(t_sdl_things *things,
				t_step_line *old_step,
				t_step_line *new_step)
{
	int			ant_num;
	t_xy		x_y;

	ant_num = find_ant_to_move(old_step, new_step);
	if (!ant_num)
		return (false);
	x_y = find_x_y(things, old_step, new_step, ant_num);
	draw_cheemz(things, x_y.x, x_y.y);
	return (true);
}

int				count_stepz(t_step_line *stepz_line)
{
	int			stepz_amount;
	t_step		*counter;

	stepz_amount = 0;
	counter = stepz_line->stepz;
	while (counter)
	{
		stepz_amount++;
		counter = counter->next;
	}
	return (stepz_amount);
}
