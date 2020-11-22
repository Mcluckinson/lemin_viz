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




void initial_ants(t_sdl_things *things, t_all_data *data)
{
	Uint32 color = 0xFFFF00;
	int radius = things->radius * 2;

	draw_filled_circle_in_buff(data->start->x, data->start->y, radius, things, color);
}

static int count_stepz(t_step_line *stepz_line)
{
	int stepz_amount;
	t_step *counter;

	stepz_amount = 0;
	counter = stepz_line->stepz;///kek
	while (counter)
	{
		stepz_amount++;
		counter = counter->next;
	}
}

static int find_ant_to_move(t_step_line *old_step, t_step_line *new_step)
{

}

static t_xy find_x_y()
{

}

static bool	try_step(t_sdl_things *things, t_all_data *data, t_step_line *old_step, t_step_line *new_step)
{
	int ant_num;

	ant_num = find_ant_to_move(old_step, new_step);
	if (!ant_num)
		return (false);
	t_xy x_y;
	int radius = things->radius * 2;///should put it in *things and stop doing this operation so many times;
	Uint32 color = 0XFFFF00;///DEFINE THIS IN HEADER

	x_y = find_x_y();
	draw_filled_circle_in_buff(x_y.x, x_y.y, radius, things, color);
	return (true);
}

static void	initial_step(t_sdl_things *things, t_all_data *data, double step_completed)
{
	t_room *start = data->start;
	t_step *step = data->curr_step->stepz;
	int x;
	int y;
	int radius = things->radius * 2;
	Uint32 color = 0XFFFF00;

	while (step)
	{
		x = start->x + (step->room->x - start->x) * step_completed;////change to things->step_progress
		y = start->y + (step->room->y - start->y) * step_completed;////change to things->step_progress
		draw_filled_circle_in_buff(x, y, radius, things, color);
		step = step->next;
	}
}

static void new_stepz(t_sdl_things *things, t_all_data *data, t_step_line *new_step)
{
	t_room *start = data->start;
	t_step *step = new_step->stepz;
	int x;
	int y;
	int radius = things->radius * 2;
	Uint32 color = 0XFFFF00;

	while (step)
	{
		if (!step->was_started)
		{
			x = start->x + (step->room->x - start->x) * things->step_progress;
			y = start->y + (step->room->y - start->y) * things->step_progress;
			draw_filled_circle_in_buff(x, y, radius, things, color);
		}
		step = step->next;
	}
}

static void clear_stepz_progress(t_step_line *stepz)
{
	t_step *step_counter;

	step_counter = stepz->stepz;///kek
	while (step_counter)
	{
		step_counter->was_started = 0;
		step_counter = step_counter->next;
	}
}

static void next_step(t_sdl_things *things, t_all_data *data, t_step_line *old_step, t_step_line *new_step)
{
	if (!old_step || !new_step)
		return ;
	int stepz_to_go = count_stepz(new_step);
	bool steps_done = true;
	while (steps_done)
	{
		steps_done = try_step(things, data, old_step, new_step);
		if (steps_done)
			stepz_to_go--;
		else
			break ;
	}
	while (stepz_to_go > 0)
		new_stepz(things, data, new_step);
	clear_stepz_progress(new_step);

}

void	draw_step(t_sdl_things *things, t_all_data *data, double step_completed)
{
	t_step *step_counter;
	int x;
	int y;

	step_counter = data->curr_step->stepz;
	if (data->curr_step == data->all_steps)
		initial_step(things, data, step_completed);
	else
	{
		next_step(things, data, data->curr_step, data->curr_step->next);
		data->curr_step = data->curr_step->next;
	}
}
