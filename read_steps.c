/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:52:49 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 21:51:24 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static t_step_line *next_step_line(char *line)
{
	t_step_line	*result;

	result = NULL;
	if (!line)
		return (NULL);
	if (!(result = (t_step_line*)ft_memalloc(sizeof(t_step_line))))
	{
		ft_strdel(&line);
		return (NULL);
	}
	if (!(result->line = ft_strdup(line)))
	{
		free(result);
		ft_strdel(&line);
		return (NULL);
	}
	ft_strdel(&line);
	return (result);
}

static int 		check_correct_steps(char **line)
{
	int i = -1;
	while (line[++i])
	{
		if (is_step(line[i]))
			continue;
		else
		{
			del_str_arr(line);
			return (0);
		}
	}
	return (1);
}

static t_step	*assign_step(char *step_line, t_all_data *data, t_step *curr_step)
{
	t_step *result;
	char **buff;
	t_room	*finder;

	if (!(buff = ft_strsplit(step_line, '-')))
		return (NULL);
	if (!(result = (t_step*)ft_memalloc(sizeof(t_step))) || split_bits(step_line, '-') != 2)
	{
		del_str_arr(buff);
		return (NULL);
	}
	if (curr_step)
		curr_step->next = result;
	result->ant_num = ft_atoi(ft_strchr(buff[0], 'L') + 1);
	if (result->ant_num < 1 || result->ant_num > data->bukashechki)
	{
		del_str_arr(buff);
		free(result);
		return (NULL);
	}
	finder = data->all_rooms;
	while (finder)
	{
		if (ft_strequ(finder->name, buff[1]))
		{
			result->room = finder;
			return (result);
		}
		finder = finder->next;
	}
	del_str_arr(buff);
	free(result);
	return (NULL);
}

static int 		split_steps(t_step_line *step_line, t_all_data *data)
{
	char **split_step_line;
	int i = -1;
	t_step	*step;

	step = NULL;
	if (!(split_step_line = ft_strsplit(step_line->line, ' ')))
		return (0);
	if (!check_correct_steps(split_step_line))
		return (0);
	while (split_step_line[++i])
	{
		if (!(step = assign_step(split_step_line[i], data, step)))
			return (0);
		if (!step_line->stepz)
			step_line->stepz = step;
	}
	return (1);
}

int read_steps(t_all_data *data)
{
	char *line;
	t_step_line	*step_lines;

	if (!(step_lines = (t_step_line*)ft_memalloc(sizeof(t_step_line))))
		return (0);
	if (!(step_lines->line = ft_strdup(data->courier)))
	{
		ft_memdel((void*)step_lines);
		return (0);
	}
	if (!split_steps(step_lines, data))
	{
		ft_memdel((void*)step_lines);
		return (0);
	}
	data->all_steps = step_lines;
	while (get_next_line(data->del_me_fd, &line) > 0)
	{
		if (!(step_lines->next = next_step_line(line)))
			return (0);
		if (!split_steps(step_lines->next, data))
			return (0);
		step_lines = step_lines->next;
	}
	return (1);
}