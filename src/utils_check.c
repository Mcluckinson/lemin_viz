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

static void	show_usage(void)
{
	char *usage;

	usage = "ok now, you need a proper file with a full output produced by "
	"lem-in\n"
	"u can run the program with it or you can try the little game mode\n"
	"use -g or -G (and the file of course) to do it\n"
	"In game mode Cheemz (that dog from memes) is 'horni' again, "
	"but we all know he just\n"
	"wants to be happy\n"
	"Use the bat to stop Cheemz from going to horni land, "
	"to do so you need to\n"
	"PUNCH\nEM\nALL\nThe blue bar below the map "
	"shows your progress, have fun mate";
	ft_error(usage);
}

void		check_args(int argc, char **argv,
				t_all_data *data, t_sdl_things *things)
{
	int		fd;
	bool	help;

	help = false;
	fd = 0;
	if (argc == 1)
		ft_error("Pass the argument, -h flag 4 usage");
	while (--argc)
	{
		if (ft_strequ(argv[argc], "-g") || ft_strequ(argv[argc], "-G"))
			things->game_mode = true;
		else if (ft_strequ(argv[argc], "-h")
		|| ft_strequ(argv[argc], "-H"))
			help = true;
		fd = open(argv[argc], O_RDONLY);
		if (fd > 0)
			data->del_me_fd = fd;
	}
	if (help)
		show_usage();
	if (data->del_me_fd < 1)
		ft_error("u r doin it wrong tho, try using -h 4 help");
}

t_xy		get_cheemz_pos(t_room *start, t_step *step, t_sdl_things *things)
{
	t_xy	cheemz_position;

	cheemz_position.x =
			start->x + (step->room->x - start->x) * things->step_progress;
	cheemz_position.y =
			start->y + (step->room->y - start->y) * things->step_progress;
	return (cheemz_position);
}

void		init_params_norminette_kek
	(bool *killd, t_step **step, t_step **bckup, t_step_line *new_step)
{
	killd = false;
	*step = new_step->stepz;
	*bckup = new_step->stepz;
}

void		update_step_sorry_norminette
	(t_sdl_things *things, t_step *step, t_xy cheemz_pos)
{
	draw_cheemz(things, cheemz_pos.x, cheemz_pos.y);
	step->was_started = 1;
}
