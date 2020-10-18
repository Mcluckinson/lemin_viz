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

int is_end_room(char *currentRoom, char *endRoom)
{
	if (ft_strequ(currentRoom, endRoom))
	{
		return (true);
	}
	return (false);
}

int get_old_x(t_step *current_step, t_room *start)
{
	int		current_x;

	current_x = 0;
	if (!current_step->was_started)
	{
		current_x = start->x;
	}
	else
	{
		current_x = current_step->room->x;
	}
	return (current_x);
}

int get_old_y(t_step *current_step, t_room *start)
{
	int		current_y;

	current_y = 0;
	if (!current_step->was_started)
	{
		current_y = start->y;
	}
	else
	{
		current_y = current_step->room->y;
	}
	return (current_y);
}

int get_new_x(t_step *current_step, t_step *next_step)
{
	int		current_x;

	current_x = 0;
	if (!current_step->was_started)
	{
		current_x = current_step->room->x;
	}
	else
	{
		current_x = next_step->room->x;
	}
	return (current_x);
}

int get_new_y(t_step *current_step, t_step *next_step)
{
	int		current_y;

	current_y = 0;
	if (!current_step->was_started)
	{
		current_y = current_step->room->y;
		current_step->was_started = true;
	}
	else
	{
		current_y = next_step->room->y;
	}
	return (current_y);
}

void draw_one_ant(t_room *start, t_room *end, t_step *current_step, t_step *next_step)
{
	t_room *current_room;
	t_room *next_room;
	int old_x;
	int old_y;
	int new_x;
	int new_y;

	current_room = current_step->room;
	next_room = next_step->room;
	if (is_end_room(current_room->name, end->name))
		return ;
	old_x = get_old_x(current_step, start);
	old_y = get_old_y(current_step, start);
	new_x = get_new_x(current_step, next_step);
	new_y = get_new_y(current_step, next_step);

	////then we will move ant to new coords
}

void draw_one_step(t_room *start, t_room *end, t_step_line *current_step, t_step_line *next_step)
{
	t_step *current;
	t_step *next;

	current = current_step->stepz;
	next = next_step->stepz;
	while (current)
	{
		draw_one_ant(start, end, current, next);
		current = current->next;
		if (next->next)
		{
			next = next->next;
		}
	}
}

void draw_all_steps(t_step_line *steps, t_all_data *data)
{
	draw_one_step(data->start, data->end, steps, steps->next);
	while (steps)
	{
		draw_one_step(data->start, data->end, steps, steps->next);
		steps = steps->next;
	}
}
