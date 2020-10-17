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

int				read_links(t_all_data *data)
{
	t_link		*link;
	char		*line;
	int			check;

	if (!(link = initital_link(data)))
		return (0);
	while (1)
	{
		if (get_next_line(data->del_me_fd, &line) != 1)
			del_line_and_return(line, 0);
		if (is_comment(line))
		{
			check = is_command(line);
			ft_strdel(&line);
			if (!check)
				continue;
			break ;
		}
		if (is_link(line))
		{
			link = make_link(line, link, data);
			if (link)
				continue;
		}
		if (is_step(line))
		{
			data->courier = line;
			return (1);
		}
		break ;
	}
	return (0);
}
