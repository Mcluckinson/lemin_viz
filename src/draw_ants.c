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

void check_ant_was_starded(t_room *start, t_step *current_step, t_step *next_step)
{
	if (current_step->ant_num == next_step->ant_num)
	{
		next_step->was_started = true;
	}
}

void print_ant(int old_x, int old_y, int new_x, int new_y, int ant_num)
{
	printf("ant %d goes from x %d y %d to x %d y %d\n", ant_num, old_x, old_y, new_x, new_y);
}

void draw_one_ant(t_room *start, t_room *end, t_step *current_step, t_step *next_step)
{
	int old_x;
	int old_y;
	int new_x;
	int new_y;
	int ant_num;

	ant_num = current_step->ant_num;
	if (is_end_room(current_step->room->name, end->name))
		return ;
	while (next_step->ant_num != ant_num && next_step->next)
	{
		next_step = next_step->next;
	}
	check_ant_was_starded(start, current_step, next_step);
	old_x = get_old_x(current_step, start);
	old_y = get_old_y(current_step, start);
	new_x = get_new_x(current_step, next_step);
	new_y = get_new_y(current_step, next_step);
	print_ant(old_x, old_y, new_x, new_y, ant_num);
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
	}
}

void draw_all_steps(t_all_data *data)
{
	t_step_line *steps;

	steps = data->all_steps;
	draw_one_step(data->start, data->end, steps, steps->next);
	while (steps)
	{
		draw_one_step(data->start, data->end, steps, steps->next);
		steps = steps->next;
	}
}

void initial_ants(t_sdl_things *things, t_all_data *data)
{
	Uint32 color = 0x9cd244;
	int radius = things->radius * 2;


	draw_filled_circle_in_buff(data->start->x, data->start->y, radius, things, color);

}
