/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_unused.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothor- <clothor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:10:10 by clothor-          #+#    #+#             */
/*   Updated: 2020/11/08 18:44:19 by clothor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_room	*find_path_room(t_room *rooms)
{
	t_room		*room;

	while (!rooms->is_part_of_path && rooms->next)
	{
		room = rooms;
		rooms = rooms->next;
		free(room->name);
		room->name = NULL;
		free(room);
		room = NULL;
	}
	if (!rooms->is_part_of_path)
	{
		free(rooms->name);
		free(rooms);
		return (NULL);
	}
	return (rooms);
}

static t_link	*find_path_link(t_link *links)
{
	t_link		*link;

	while ((!links->first_room->is_part_of_path
			|| !links->second_room->is_part_of_path) && links->next)
	{
		link = links;
		links = links->next;
		link->first_room = NULL;
		link->second_room = NULL;
		link->next = NULL;
		free(link);
		link = NULL;
	}
	if (!links->first_room->is_part_of_path
		|| !links->second_room->is_part_of_path)
	{
		free(links);
		return (NULL);
	}
	return (links);
}

static t_room	*delete_unused_rooms(t_room *rooms)
{
	t_room		*ref;
	t_room		*room;

	ref = find_path_room(rooms);
	room = ref;
	while (room)
	{
		room->next = find_path_room(room->next);
		room = room->next;
	}
	return (ref);
}

static t_link	*delete_unused_links(t_link *links)
{
	t_link		*ref;
	t_link		*link;

	ref = find_path_link(links);
	link = ref;
	while (link)
	{
		link->next = find_path_link(link->next);
		link = link->next;
	}
	return (ref);
}

void			delete_unused(t_all_data *data)
{
	if (!data->is_generated_map)
		return ;
	data->all_links = delete_unused_links(data->all_links);
	data->all_rooms = delete_unused_rooms(data->all_rooms);
}
