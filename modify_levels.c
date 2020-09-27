/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_levels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothor- <clothor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:03:32 by clothor-          #+#    #+#             */
/*   Updated: 2020/09/25 18:04:36 by clothor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

int			str_contains(char *str, char *contains)
{
	char	*lhs;
	char	*rhs;

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
				return (1);
			if (*lhs != *rhs)
			{
				rhs = contains;
			}
		}
		else
			lhs++;
	}
	return (0);
}

char		*ant_name_for_index(int index)
{
	char	*ant_name;
	char	*str_index;
	char	*ref;

	str_index = ft_itoa(index);
	ref = ft_strjoin("L", str_index);
	ant_name = ft_strjoin(ref, "-");
	free(str_index);
	free(ref);
	return (ant_name);
}

int			path_count(char *ants)
{
	int		number_of_paths;
	int		is_contain;
	int		index;
	char	*ant_name;

	number_of_paths = 0;
	is_contain = 1;
	index = 1;
	while (is_contain)
	{
		ant_name = ant_name_for_index(index);
		is_contain = str_contains(ants, ant_name);
		free(ant_name);
		if (is_contain)
		{
			index++;
			number_of_paths++;
		}
	}
	return (number_of_paths);
}

char		**get_ants_array(int ants_count)
{
	char	**result;
	int		i;

	i = 0;
	result = (char**)ft_memalloc(sizeof(char *) * ants_count + 1);
	while (i <= ants_count)
	{
		result[i] = ant_name_for_index(i + 1);
		i++;
	}
	result[i] = NULL;
	return (result);
}

void		modify_levels(t_all_data *data)
{
	int		level;
	t_room	*ret;

	if (!data->is_generated_map)
		return ;
	ret = data->all_rooms;
	while (ret)
	{
		level = ret->level;
		if (!level)
			level = 1;
		ret->x = ret->x * level * MODIFIER_X;
		ret->y = ret->y * MODIFIER_Y;
		ret = ret->next;
	}
}
