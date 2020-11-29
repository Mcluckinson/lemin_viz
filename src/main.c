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

int					main(int ac, char **av)
{
	t_sdl_things	*sdl_things;
	t_all_data		*data;

	if (ac != 0)
		data = NULL;
	sdl_things = NULL;
	if (!(data = (t_all_data*)ft_memalloc(sizeof(t_all_data))))
		return (0);
	data->del_me_fd = open(av[1], O_RDONLY);
	if (!(read_data(data)))
		return (ft_error("Invalid data"));
	set_levels_from_data(data);
	if (!(sdl_things = (t_sdl_things*)ft_memalloc(sizeof(t_sdl_things))))
		return (ft_error_new(data, sdl_things, SDL_GetError()));
	fix_coords(data, sdl_things);
	if ((!init_sdl(sdl_things)))
		return (ft_error_new(data, sdl_things, SDL_GetError()));
	delete_unused(data);
	data->curr_step = data->all_steps;
	init_music(sdl_things);
	loopz(sdl_things, data);
	ft_error_new(data, sdl_things, "Exit");
	return (0);
}
