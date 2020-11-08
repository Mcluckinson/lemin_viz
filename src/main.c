/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:27:38 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 19:44:15 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

static int			read_data(t_all_data *data)
{
	if (!read_ants(data))
		return (0);
	if (!read_rooms(data))
		return (0);
	if (!data->start || !data->end)
		return (0);
	if (!read_links(data))
		return (0);
	if (!read_steps(data))
		return (0);
	return (1);
}

///////////dont forget to delete em args he he
int					main(int ac, char **av)
{
	t_sdl_things	*sdl_things;
	t_all_data		*data;
	//DONT FORGET TO ADD WALL WEXtrA WError BACK TO MAKEFILE KEK

	data = NULL;
	if (!(data = (t_all_data*)ft_memalloc(sizeof(t_all_data))))
		return (0);
	///////////del this one below
	data->del_me_fd = open(av[1], O_RDONLY);
	if (!(read_data(data)))
		return (ft_error("Invalid data"));
	set_levels_from_data(data);
	//	return (huevie_dela());
	if (!(sdl_things = (t_sdl_things*)ft_memalloc(sizeof(t_sdl_things))))
		return (0);
		//	return (huevie_dela());
	fix_coords(data, sdl_things);
	if ((!init_sdl(sdl_things)))
		return (0);
	delete_unused(data);
	//	return (huevie_dela());
	loopz(sdl_things, data);
//	draw_test_window(sdl_things, data);
	return (0);
//		free_and_quit(data);
}
