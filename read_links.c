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

static void		check_step(t_all_data *data, char *line)
{
	if (is_step(line))
	{
		data->courier = line;
	}
}

int				read_links(t_all_data *data)
{
	t_link		*link;
	char		*line;
	int			check;

	if (!(link = initial_link(data)))
		return (0);
	while (get_next_line(data->del_me_fd, &line) > 0)
	{
		if (is_comment(line))
		{
			check = is_command(line);
			if (!check)
				continue;
			break ;
		}
		if (is_link(line))
		{
			if (!(link = make_link(line, link, data)))
				return (0);
			continue;
		}
		check_step(data, line);
		break ;
	}
	return (1);
}
