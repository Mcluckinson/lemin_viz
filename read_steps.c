/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:52:49 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/10 21:19:06 by cyuriko          ###   ########.fr       */
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
	data->all_steps = step_lines;
	while (get_next_line(1, &line) > 0)
	{
		if (!(step_lines->next = next_step_line(line)))
			return (0);
	}
	return (1);
}