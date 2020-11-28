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

int			ft_error(const char *error)
{
	ft_putendl_fd(error, 2);
	exit(-1);
}

void	clear_sdl(t_all_data *data, t_sdl_things *things)
{
	if (things->win)
		SDL_DestroyWindow(things->win);
	if (things->renderer)
		SDL_DestroyRenderer(things->renderer);
	if (things->texture)
		SDL_DestroyTexture(things->texture);
	if (things->cheems)
		SDL_DestroyTexture(things->cheems);
	free(things->m_buffer1);
	free(things->m_buffer2);
	free(things);
	SDL_Quit();
	ft_error("Quit");
}
