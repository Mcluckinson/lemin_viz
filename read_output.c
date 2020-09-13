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

	str_index = ft_itoa(index);
	ant_name = ft_strjoin("L", str_index);
	free(str_index);
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

char **remove_ant_from_array(char **ants)
{

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

char	*get_room_name(char *line, char *ant)
{
	char *name;
	char **lines;
	int i;
	int is_contain;

	lines = ft_strsplit(line, ' ');
	i = 0;
	is_contain = 0;
	while (*lines)
	{
		is_contain = str_contains(lines[i], ant);
		if (is_contain)
		{
			name = ft_strchr(lines[i], '-');
			name++;
			return name;
		}
		i++;
		lines++;
	}

	return NULL;
}

void	set_levels(t_all_data *data, int number_of_paths)
{
	int is_contain;
	char **ants_array;
	int i;

	ants_array = get_ants_array(number_of_paths);
	is_contain = 0;
	i = 0;
	while (*ants_array)
	{
		t_step_line *step = data->all_steps;
		char *room_name = get_room_name(step->line, ants_array[i]);
	}
	while (is_contain)
	{

	}
}

int 	read_output(t_all_data *data)
{
	int p_count = path_count(data->all_steps->line);
	char **link = ft_strsplit(data->all_steps->next->line, ' ');
	set_levels(data, p_count);
}

