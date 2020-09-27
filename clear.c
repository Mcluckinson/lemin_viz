/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 18:20:30 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 18:21:20 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

void	clear_sdl(t_all_data *data, t_sdl_things *thing)
{
	SDL_DestroyWindow(thing->win);
	SDL_Quit();
	ft_error("EXITING ALRIGHT");
}
