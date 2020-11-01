/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:54:57 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/09 18:02:00 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

int			valid_coords(t_room *room, t_room *list)
{
	t_room	*start;

	start = list;
	while (start && start->next)
	{
		if (start->x == room->x)
		{
			if (start->y == room->y)
				return (0);
		}
		if (ft_strequ(start->name, room->name))
			return (0);
		start = start->next;
	}
	return (1);
}

int			duplicate_links(t_link *link, t_all_data *data)
{
	t_link	*start;

	start = data->all_links;
	while (start != link && start)
	{
		if ((start->first_room == link->first_room
			&& start->second_room == link->second_room)
			|| (start->first_room == link->second_room
				&& start->second_room == link->first_room)
			|| (start->first_room == start->second_room
				|| link->first_room == link->second_room))
			return (1);
		start = start->next;
	}
	return (0);
}
