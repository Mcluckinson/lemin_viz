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

//	draw_filled_circle_in_buff(data->start->x, data->start->y, radius, things, color);///use draw cheemz instead
	draw_cheemz(things, data->start->x, data->start->y);
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
	return (stepz_amount);
}

static int find_ant_to_move(t_step_line *old_step, t_step_line *new_step)
{
	t_step *old_counter = old_step->stepz;
	t_step *new_counter = new_step->stepz;

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

static t_step *find_da_step_4_ant(t_step_line *step_line, int ant_num)
{
	t_step *finder;

	finder = step_line->stepz;
	while (finder)
	{
		if (finder->ant_num == ant_num)
			break ;
		finder = finder->next;
	}
	return (finder);
}

static t_xy find_x_y(t_sdl_things *things, t_step_line *old_step, t_step_line *new_step, int ant_num)
{
	t_xy coords;
	t_step *old;
	t_step *new;
	t_room *start;

	old = find_da_step_4_ant(old_step, ant_num);
	new = find_da_step_4_ant(new_step, ant_num);
	start = old->room;

	coords.x = start->x + (new->room->x - start->x) * things->step_progress;////change to things->step_progress
	coords.y = start->y + (new->room->y - start->y) * things->step_progress;////change to things->step_progress
}

static bool	try_step(t_sdl_things *things, t_all_data *data, t_step_line *old_step, t_step_line *new_step)
{
	int ant_num;

	ant_num = find_ant_to_move(old_step, new_step);
	if (!ant_num)
		return (false);
	t_xy x_y;
	x_y = find_x_y(things,old_step, new_step, ant_num);
	draw_cheemz(things, x_y.x, x_y.y);
	return (true);
}

static void	initial_step(t_sdl_things *things, t_all_data *data)
{
	t_room *start = data->start;
	t_step *step = data->curr_step->stepz;
	int x;
	int y;

	while (step)
	{
		x = start->x + (step->room->x - start->x) * things->step_progress;
		y = start->y + (step->room->y - start->y) * things->step_progress;
		draw_cheemz(things, x, y);
		step = step->next;
	}
}

static void new_stepz(t_sdl_things *things, t_all_data *data, t_step_line *new_step)
{
	t_room *start = data->start;
	t_step *step = new_step->stepz;
	int x;
	int y;

	while (step)
	{
		if (!step->was_started)
		{
			x = start->x + (step->room->x - start->x) * things->step_progress;
			y = start->y + (step->room->y - start->y) * things->step_progress;
			draw_cheemz(things, x, y);
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
	{
		new_stepz(things, data, new_step);
		stepz_to_go--;
	}
	clear_stepz_progress(new_step);
}

void	draw_step(t_sdl_things *things, t_all_data *data)
{
	if (data->curr_step == data->all_steps)
		initial_step(things, data);
	else
		next_step(things, data, data->curr_step->prev, data->curr_step);
}
