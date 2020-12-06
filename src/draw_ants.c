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
	t_step	*step;
	t_xy	cheemz_position;
	t_step	*backup;
	bool	killd;

	killd = false;
	step = data->curr_step->stepz;
	backup = step;
	while (step)
	{
		cheemz_position = get_cheemz_pos(data->start, step, things);
		if (things->game_mode && things->mouse_down)
		{
			backup = step->next;
			killd = delete_cheemz(step->ant_num, data, cheemz_position, things);
		}
		if (!things->game_mode || !killd)
			draw_cheemz(things, cheemz_position.x, cheemz_position.y);
		if (!data->ants_reduced)
			data->ants--;
		step = (killd) ? backup : step->next;
	}
}

static void	new_stepz(t_sdl_things *things, t_all_data *data,
					t_step_line *new_step)
{
	t_step	*step;
	t_step 	*backup;
	t_xy	cheemz_pos;
	bool	killd;

	init_params_norminette_kek(&killd, &step, &backup, new_step);
	while (step)
	{
		if (!step->was_started)
		{
			cheemz_pos = get_cheemz_pos(data->start, step, things);
			if (things->game_mode && things->mouse_down)
			{
				backup = step->next;
				killd = delete_cheemz(step->ant_num, data, cheemz_pos, things);
			}
			if (!things->game_mode || !killd)
			{
				draw_cheemz(things, cheemz_pos.x, cheemz_pos.y);
				step->was_started = 1;
			}
			data->ants += data->ants_reduced - 1;
		}
		step = killd ? backup : step->next;
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
		steps_done = try_step(things, old_step, new_step, data);
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
