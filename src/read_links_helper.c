/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothor- <clothor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:25 by clothor-          #+#    #+#             */
/*   Updated: 2020/10/17 20:41:09 by clothor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_room	*find_room(t_all_data *data, char *name)
{
	t_room		*room;

	room = data->all_rooms;
	while (room)
	{
		if (ft_strequ(room->name, name))
			return (room);
		room = room->next;
	}
	return (NULL);
}

t_link			*make_link(char *line, t_link *link, t_all_data *data)
{
	t_link		*result;
	char		**split;

	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		ft_strdel(&line);
		return (NULL);
	}
	link->next = result;
	result->prev = link;
	if (!(split = ft_strsplit(line, '-')))
	{
		ft_strdel(&line);
		return (NULL);
	}
	ft_strdel(&line);
	result->first_room = find_room(data, split[0]);
	result->second_room = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->first_room || !result->second_room
		|| duplicate_links(result, data))
		return (NULL);
	return (result);
}

t_link			*initial_link(t_all_data *data)
{
	t_link		*result;
	char		**split;

	split = NULL;
	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
		return (NULL);
	data->all_links = result;
	if (!(split = ft_strsplit(data->courier, '-')))
		return (NULL);
	ft_strdel(&data->courier);
	result->first_room = find_room(data, split[0]);
	result->second_room = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->first_room || !result->second_room)
		return (NULL);
	return (result);
}

int				is_command(char *line)
{
	int			result;

	result = ft_strequ(line, "##start") || ft_strequ(line, "##end");
	ft_strdel(&line);
	if (result)
		return (1);
	return (0);
}
