/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:31:30 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/09 19:33:40 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_room *find_room(t_all_data *data, char *name)
{
	t_room *room;

	room = data->all_rooms;
	while (room)
	{
		if (ft_strequ(room->name, name))
			return (room);
		room = room->next;
	}
	return (NULL);
}

static t_link 	*make_link(char *line, t_link *link, t_all_data *data)
{
	t_link	*result;
	char **split;

	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		ft_strdel(&line);
		return (NULL);
	}
	link->next = result;
	if (!(split = ft_strsplit(line, '-')))
	{
		ft_strdel(&line);
		return (NULL);
	}
	ft_strdel(&line);
	result->room1 = find_room(data, split[0]);
	result->room2 = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->room1 || !result->room2 || duplicate_links(result, data))
		return (NULL);
	return (result);
}

static t_link *initital_link(t_all_data *data)
{
	t_link *result;
	char **split;

	split = NULL;
	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
		return (NULL);
	data->all_links = result;
	if (!(split = ft_strsplit(data->courier, '-')))
		return (NULL);
	ft_strdel(&data->courier);
	result->room1 = find_room(data, split[0]);
	result->room2 = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->room1 || !result->room2)
		return (NULL);
	return (result);
}

static int is_command(char *line)
{
	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		return (1);
	return (0);
}

int 	read_links(t_all_data *data)
{
	t_link	*link;
	char *line;
	int check;

	if (!(link = initital_link(data)))
		return (0);
	while (1)
	{
		if (get_next_line(1, &line) != 1)
			del_line_and_return(line, 0);
		if (is_comment(line))
		{
			check = is_command(line);
			ft_strdel(&line);
			if (!check)
				continue;
			break;
		}
		if (is_link(line))
		{
			link = make_link(line, link, data);
			if (link)
				continue;
		}
		if (is_step(line))
		{
			data->courier = line;
			return (1);
		}
		break ;
	}
	return (0);
}

