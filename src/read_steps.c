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

static t_step_line	*next_step_line(char *line)
{
	t_step_line		*result;

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

static int			split_steps(t_step_line *step_line, t_all_data *data)
{
	char			**split_step_line;
	int				i;
	t_step			*step;

	step = NULL;
	i = -1;
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
	del_str_arr(split_step_line);
	return (1);
}

int					read_steps_next(t_all_data *data)
{
	char			*line;
	t_step_line		*step_lines;

	step_lines = data->all_steps;
	while (get_next_line(data->del_me_fd, &line) > 0)
	{
		if (!(step_lines->next = next_step_line(line)))
			return (0);
		if (!split_steps(step_lines->next, data))
			return (0);
		if (step_lines->next)
			step_lines->next->prev = step_lines;
		step_lines = step_lines->next;
	}
	return (is_all_steps_found(data->all_steps, data->ants));
}

int					read_steps(t_all_data *data)
{
	t_step_line		*step_lines;

	if (!(step_lines = (t_step_line*)ft_memalloc(sizeof(t_step_line))))
		return (0);
	if (!(step_lines->line = ft_strdup(data->courier)))
	{
		ft_memdel((void*)step_lines);
		return (0);
	}
	ft_strdel(&data->courier);
	if (!split_steps(step_lines, data))
	{
		ft_memdel((void*)step_lines);
		return (0);
	}
	data->all_steps = step_lines;
	return (read_steps_next(data));
}
