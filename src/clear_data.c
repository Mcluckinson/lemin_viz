/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothor- <clothor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 19:25:30 by clothor-          #+#    #+#             */
/*   Updated: 2020/11/28 20:25:20 by clothor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static void	clear_rooms(t_room *rooms)
{
	t_room *ref;

	while (rooms)
	{
		ref = rooms;
		rooms = rooms->next;
		ref->x = 0;
		ref->y = 0;
		ref->level = 0;
		free(ref->name);
		ref->name = NULL;
		ref->is_part_of_path = 0;
		ref->next = NULL;
		free(ref);
		ref = NULL;
	}
}

static void	clear_links(t_link *links)
{
	t_link *ref;

	while (links)
	{
		ref = links;
		links = links->next;
		if (links)
			links->prev = NULL;
		ref->first_room = NULL;
		ref->second_room = NULL;
		ref->next = NULL;
		ref->prev = NULL;
		free(ref);
		ref = NULL;
	}
}

static void	clear_stepz(t_step *stepz)
{
	t_step *ref;

	while (stepz)
	{
		ref = stepz;
		stepz = stepz->next;
		ref->ant_num = 0;
		ref->was_started = 0;
		ref->room = NULL;
		ref->next = NULL;
		free(ref);
		ref = NULL;
	}
}

static void	clear_steps(t_step_line *steps)
{
	t_step_line *ref;

	while (steps)
	{
		ref = steps;
		steps = steps->next;
		clear_stepz(ref->stepz);
		free(ref->line);
		ref->line = NULL;
		ref->stepz = NULL;
		ref->next = NULL;
		if (ref->prev)
			ref->prev = NULL;
		free(ref);
		ref = NULL;
	}
}

void		clear_data(t_all_data *data)
{
	if (!data)
		return ;
	clear_rooms(data->all_rooms);
	clear_links(data->all_links);
	clear_steps(data->all_steps);
	free(data);
}
