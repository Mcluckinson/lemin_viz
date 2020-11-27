/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 18:03:32 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 18:04:36 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

int				init_music(t_sdl_things *things)
{
	SDL_AudioSpec	wav_spec;
	Uint32			wav_length;

	SDL_LoadWAV("./resources/wolves.wav", &wav_spec,
				&things->wav_buffer, &wav_length);
	things->device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
	SDL_QueueAudio(things->device_id, things->wav_buffer, wav_length);
	SDL_PauseAudioDevice(things->device_id, 0);
	return (0);
}
