//
// Created by Carleton Lothor on 9/13/20.
//

#include "lem_viz.h"

int		str_contains(char *str, char *contains)
{
	char *lhs;
	char *rhs;

	if (!*str || !*contains)
		return (-1);
	lhs = str;
	rhs = contains;
	while (*lhs)
	{
		if (*lhs == *rhs && *lhs)
		{
			lhs++;
			rhs++;
			if (!*rhs)
			{
				return (1);
			}
			if (*lhs != *rhs)
			{
				rhs = contains;
			}
		}
		else
		{
			lhs++;
		}
	}
	return (0);
}

char	*ant_name_for_index(int index)
{
	char *ant_name;
	char *str_index;
	char *ref;

	str_index = ft_itoa(index);
	ref = ft_strjoin("L", str_index);
	ant_name = ft_strjoin(ref, "-");
	free(str_index);
	free(ref);

	return ant_name;
}

int		path_count(char *ants)
{
	int number_of_paths;
	int is_contain;
	int index;

	number_of_paths = 0;
	is_contain = 1;
	index = 1;
	while (is_contain)
	{
		char *ant_name = ant_name_for_index(index);
		is_contain = str_contains(ants, ant_name);
		free(ant_name);
		if (is_contain)
		{
			index++;
			number_of_paths++;
		}
	}

	return number_of_paths;
}

char	**get_ants_array(int ants_count)
{
	char **result;
	int i;

	i = 0;
	result = (char**)ft_memalloc(sizeof(char *) * ants_count + 1);
	while (i <= ants_count)
	{
		result[i] = ant_name_for_index(i + 1);
		i++;
	}

	result[i] = NULL;
	return result;
}

char	*get_room_name(char *line)
{
	char *name;

	while (*line != '-')
	{
		line++;
	}
	if (*line == '-')
	{
		line++;
	}

	name = ft_strdup(line);

	return name;
}

void	set_level_for_map(char *name, int level, t_room *rooms, int is_generated_map)
{
	t_room *room;

	room = rooms;
	while (room)
	{
		if (ft_strequ(name, room->name))
		{
			break;
		}
		room = room->next;
	}
	if (is_generated_map)
		room->level = level;
	room->is_part_of_path = 1;
}

int 	has_path(char **ants, char *line)
{
	while (*ants)
	{
		if (str_contains(line, *ants))
		{
			return 1;
		}
		ants++;
	}
	return 0;
}

int		set_levels(t_all_data *data, t_step_line *steps, char **ants, int level)
{
	char **link;
	char **ref;
	char *room_name;

	if (!has_path(ants, steps->line))
	{
		return 1;
	}

	link = ft_strsplit(steps->line, ' ');
	ref = link;
	while (*link)
	{
		if (has_path(ants, *link))
		{
			room_name = get_room_name(*link);
			set_level_for_map(room_name, level, data->all_rooms, data->is_generated_map);
			free(room_name);
		}
		link++;
	}

	ft_memdel((void **) ref);
	return 0;
}

void	modify_levels(t_all_data *data)
{
	if (!data->is_generated_map)
		return;

	t_room *ret = data->all_rooms;
	while (ret)
	{
		int level = ret->level;
		if (!level)
			level = 1;
		ret->x = ret->x * level * MODIFIER_X;
		ret->y = ret->y * MODIFIER_Y;
		ret = ret->next;
	}
}

int 	set_levels_from_data(t_all_data *data)
{
	t_step_line *steps;
	char **ants;
	int p_count;
	int level;
	int is_end;

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

	ft_memdel((void **) ants);
	// End тоже переопределяется
	// Здесь возможно нужно переопределить end->level = END_LEVEL; или как там..
	return 1;
}
