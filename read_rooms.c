/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 21:39:52 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 15:03:47 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_room *make_room(t_room *room, char *line, t_all_data *data)
{
	t_room	*result;
	char **room_data;

	if (!(result = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	if (room)
		room->next = result;
	if (!(room_data = ft_strsplit(line, ' ')))
		return (0);
	result->name = ft_strdup(room_data[0]);
	result->x = ft_atoi(room_data[1]);
	result->y = ft_atoi(room_data[2]);
	del_str_arr(room_data);
	if (!data->all_rooms)
		data->all_rooms = result;
	ft_strdel(&line);
	return (result);
}

static int		start_end_check(char *line, t_room **rooms, t_all_data *data)
{
	int 	flag;

	flag = 0;
	flag += (ft_strequ(line, "##start") ? 1 : 0);
	flag += (ft_strequ(line, "##end") ? 2 : 0);
	ft_strdel(&line);
	if (flag != 1 && flag != 2)
		return (1);
	if ((get_next_line(data->del_me_fd, &line) < 1) || !(is_room(line)))
		return (del_line_and_return(line, 1));
	if (flag == 1 && !data->start)
	{
		if (!(*rooms = make_room(*rooms, line, data)))
			return (del_line_and_return(line, 0));
		data->start = *rooms;
		return (1);
	}
	else if (flag == 2 && !data->end)
	{
		if (!(*rooms = make_room(*rooms, line, data)))
			return (del_line_and_return(line, 0));
		data->end = *rooms;
		return (1);
	}
	return (del_line_and_return(line, 0));
}

int 	read_rooms(t_all_data *data)
{
	char *line;
	t_room	*rooms;

	rooms = NULL;
	while (1)
	{
		if (get_next_line(data->del_me_fd, &line) != 1)
			del_line_and_return(line, 0);
		if (is_comment(line))
		{
			if (!start_end_check(line, &rooms, data))
				return (0);
			if (str_contains(line, "number of lines"))
				data->is_generated_map = 1;
			continue ;
		}
		if (is_room(line))
		{
			rooms = make_room(rooms, line, data);
			if (valid_coords(rooms, data->all_rooms));
				continue ;
		}
		if (is_link(line))
		{
			data->courier = line;
			return (1);
		}
		break;
	}
	return (0);
 }