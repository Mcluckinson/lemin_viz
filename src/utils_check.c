/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothor- <clothor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:04:31 by clothor-          #+#    #+#             */
/*   Updated: 2020/11/29 22:21:22 by clothor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

void	check_args(int argc, char **argv,t_all_data *data, t_sdl_things *things)
{
	int	fd;

	if (argc == 1)
		ft_error("Pass the argument");
	while (--argc)
	{
		if (ft_strlen(argv[argc]) == 2
		&& (str_contains(argv[argc], "-G")
		|| str_contains(argv[argc], "-g")))
			things->game_mode = true;
		fd = open(argv[argc], O_RDONLY);
		if (fd > 0)
			data->del_me_fd = fd;
	}
}
