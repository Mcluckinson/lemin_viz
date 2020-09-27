/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_levels_for_view.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothor- <clothor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:03:32 by clothor-          #+#    #+#             */
/*   Updated: 2020/09/14 18:04:36 by clothor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

char			*get_room_name(char *line)
{
	char		*name;

	while (*line != '-')
	{
		line++;
	}
	if (*line == '-')
	{
		line++;
	}
	name = ft_strdup(line);
	return (name);
}

void			set_level_for_map(char *name, int level,
							t_room *rooms, int is_generated_map)
{
	t_room		*room;

	room = rooms;
	while (room)
	{
		if (ft_strequ(name, room->name))
		{
			break ;
		}
		room = room->next;
	}
	if (is_generated_map)
		room->level = level;
	room->is_part_of_path = 1;
}

int				has_path(char **ants, char *line)
{
	while (*ants)
	{
		if (str_contains(line, *ants))
		{
			return (1);
		}
		ants++;
	}
	return (0);
}

int				set_levels(t_all_data *data, t_step_line *steps,
							char **ants, int level)
{
	char		**link;
	char		**ref;
	char		*room_name;

	if (!has_path(ants, steps->line))
	{
		return (1);
	}
	link = ft_strsplit(steps->line, ' ');
	ref = link;
	while (*link)
	{
		if (has_path(ants, *link))
		{
			room_name = get_room_name(*link);
			set_level_for_map(room_name, level,
							data->all_rooms, data->is_generated_map);
			free(room_name);
		}
		link++;
	}
	ft_memdel((void **)ref);
	return (0);
}

int				set_levels_from_data(t_all_data *data)
{
	t_step_line	*steps;
	char		**ants;
	int			p_count;
	int			level;
	int			is_end;

	steps = data->all_steps;
	p_count = path_count(steps->line);
	ants = get_ants_array(p_count);
	level = 1;
	is_end = 0;
	while (steps && !is_end)
	{
		is_end = set_levels(data, steps, ants, level);
		level++;
		steps = steps->next;
	}
	modify_levels(data);
	ft_memdel((void **)ants);
	return (1);
}
