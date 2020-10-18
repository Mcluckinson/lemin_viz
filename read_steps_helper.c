/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothor- <clothor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:10:55 by clothor-          #+#    #+#             */
/*   Updated: 2020/10/18 18:01:44 by clothor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_step		*next_assign_steep(t_step *result,
										t_all_data *data, char **buff)
{
	t_room			*finder;

	finder = data->all_rooms;
	while (finder)
	{
		if (ft_strequ(finder->name, buff[1]))
		{
			result->room = finder;
			finder->is_part_of_path = 1;
			del_str_arr(buff);
			return (result);
		}
		finder = finder->next;
	}
	del_str_arr(buff);
	free(result);
	return (NULL);
}

t_step		*assign_step(char *step_line,
						t_all_data *data, t_step *curr_step)
{
	t_step			*result;
	char			**buff;

	if (!(buff = ft_strsplit(step_line, '-')))
		return (NULL);
	if (!(result = (t_step*)ft_memalloc(sizeof(t_step)))
		|| split_bits(step_line, '-') != 2)
	{
		del_str_arr(buff);
		return (NULL);
	}
	if (curr_step)
		curr_step->next = result;
	result->ant_num = ft_atoi(ft_strchr(buff[0], 'L') + 1);
	if (result->ant_num < 1 || result->ant_num > data->ants)
	{
		del_str_arr(buff);
		free(result);
		return (NULL);
	}
	return (next_assign_steep(result, data, buff));
}
