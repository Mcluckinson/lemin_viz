/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:56:29 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 16:56:29 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void	initial_step(t_sdl_things *things, t_all_data *data)
{
	t_room	*start;
	t_step	*step;
	int		x;
	int		y;

	start = data->start;
	step = data->curr_step->stepz;
	while (step)
	{
		x = start->x + (step->room->x - start->x) * things->step_progress;
		y = start->y + (step->room->y - start->y) * things->step_progress;
		draw_cheemz(things, x, y);
		if (!data->ants_reduced)
			data->ants--;
		step = step->next;
	}
}

static void	new_stepz(t_sdl_things *things, t_all_data *data,
					t_step_line *new_step)
{
	t_room	*start;
	t_step	*step;
	int		x;
	int		y;

	start = data->start;
	step = new_step->stepz;
	while (step)
	{
		if (!step->was_started)
		{
			x = start->x + (step->room->x - start->x) * things->step_progress;
			y = start->y + (step->room->y - start->y) * things->step_progress;
			draw_cheemz(things, x, y);
			if (!data->ants_reduced)
				data->ants--;
		}
		step = step->next;
	}
}

static void	clear_stepz_progress(t_step_line *stepz)
{
	t_step	*step_counter;

	step_counter = stepz->stepz;
	while (step_counter)
	{
		step_counter->was_started = 0;
		step_counter = step_counter->next;
	}
}

static void	next_step(t_sdl_things *things, t_all_data *data,
					t_step_line *old_step, t_step_line *new_step)
{
	int		stepz_to_go;
	bool	steps_done;

	if (!old_step || !new_step)
		return ;
	stepz_to_go = count_stepz(new_step);
	steps_done = true;
	while (steps_done)
	{
		steps_done = try_step(things, old_step, new_step);
		if (steps_done)
			stepz_to_go--;
		else
			break ;
	}
	while (stepz_to_go > 0)
	{
		new_stepz(things, data, new_step);
		stepz_to_go--;
	}
	clear_stepz_progress(new_step);
}

void		draw_step(t_sdl_things *things, t_all_data *data)
{
	if (data->curr_step == data->all_steps)
		initial_step(things, data);
	else
		next_step(things, data, data->curr_step->prev, data->curr_step);
}
