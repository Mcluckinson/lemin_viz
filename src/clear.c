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

static void	clear_textures(t_sdl_things *things)
{
	if (things->texture)
		SDL_DestroyTexture(things->texture);
	if (things->cheems)
		SDL_DestroyTexture(things->cheems);
	if (things->roomz)
		SDL_DestroyTexture(things->roomz);
	if (things->start)
		SDL_DestroyTexture(things->start);
	if (things->end)
		SDL_DestroyTexture(things->end);
	if (things->cryin)
		SDL_DestroyTexture(things->cryin);
	if (things->u_win)
		SDL_DestroyTexture(things->u_win);
	if (things->u_looz)
		SDL_DestroyTexture(things->u_looz);
	if (things->horni_land)
		SDL_DestroyTexture(things->horni_land);
	if (things->bat_right)
		SDL_DestroyTexture(things->bat_right);
	if (things->bat_down)
		SDL_DestroyTexture(things->bat_down);
}

static void	clear_sdl(t_sdl_things *things)
{
	if (!things)
		return ;
	if (things->win)
		SDL_DestroyWindow(things->win);
	if (things->renderer)
		SDL_DestroyRenderer(things->renderer);
	if (things->m_buffer1)
		free(things->m_buffer1);
	if (things->m_buffer2)
		free(things->m_buffer2);
	clear_textures(things);
	free(things);
	SDL_Quit();
}

int			ft_error(const char *error)
{
	ft_putendl_fd(error, 2);
	exit(-1);
}

int			ft_error_new(t_all_data *data,
				t_sdl_things *things, const char *error)
{
	clear_sdl(things);
	clear_data(data);
	ft_putendl_fd(error, 2);
	exit(0);
}
