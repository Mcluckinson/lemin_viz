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

int get_ant_x(int ant)
{
	int		current_x;

	current_x = 0;
	/////find current x_coordinate of ant with arg num;
	return (current_x);
}

int get_ant_y(int ant)
{
	int		current_y;

	current_y = 0;
	/////find current x_coordinate of ant with arg num;
	return (current_y);
}

void draw_one_ant(t_step *counter)
{
	int old_x = get_ant_x(counter->ant_num);
	int old_y = get_ant_y(counter->ant_num);
	////then we will move ant to new coords
}

void draw_one_step(t_step *counter)
{
	while (counter)
	{
		draw_one_ant(counter);
		counter = counter->next;
	}
}
