
#include "lem_viz.h"

/*static void blur_v5(t_sdl_things *things, int x, int y)/////gets blur for 1 point
{
	int box_blur_x;
	Uint8 red = 0, green = 0, blue = 0;
	int redTotal, greenTotal, blueTotal;
	Uint32 color;

		box_blur_x = -BLUR_EXTENT - 1;
		redTotal = 0;
		greenTotal = 0;
		blueTotal = 0;
		while (box_blur_x++ <= BLUR_EXTENT)
		{
			if (y >= 0 && x + box_blur_x >= 0 &&
				y < things->height &&
				x + box_blur_x < things->width)////////вынести этот иф выше, ограничить рамку толщиной 1 пиксель?
			{
				color = things->m_buffer2[y * things->width + x + box_blur_x];
				red = color;
				green = color >> 8;
				blue = color >> 16;

				redTotal += red;
				greenTotal += green;
				blueTotal += blue;
			}
			red = redTotal / 9;//кажется 16 кек
			green = greenTotal / 9;
			blue = blueTotal / 9;
		}
		if (red || green || blue)
		{
	//		SDL_SetRenderDrawColor(things->renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	//		if (SDL_RenderDrawPoint(things->renderer, current_x, current_y))
	//			printf("SDL failed: %s\n", SDL_GetError());////DELETE ME KEK
			things->m_buffer1[y * things->width + x] = color;
		}

}*/

/*static void	*threadman(void *things)
{
	t_xy		plot;
	t_xy		start_end;
	pthread_t	s;
	t_sdl_things *kek;

	kek = (t_sdl_things*)things;/////shortens code 4 norm kek
	start_end.x = 0;
	s = pthread_self();
	while (s != ((t_sdl_things *)things)->threads[start_end.x])
		start_end.x++;
	start_end.y = (start_end.x + 1) * DEFAULT_WIDTH / THREAD_NUM;
	start_end.x = start_end.x * DEFAULT_WIDTH / THREAD_NUM;
	plot.y = DEFAULT_HEIGHT;
	while (--plot.y)
	{
		plot.x = start_end.x;
		while (plot.x < start_end.y)
		{
			//KEK WAt
	//		put_pixel(mlx, plot.x, plot.y, color_set(mlx, \
	//			frac[((t_mlx*)mlx)->fractal](mlx, plot.y, plot.x)));
			blur_v5(things, plot.x, plot.y);
			++plot.x;
		}
	}
	pthread_exit(NULL);
}*/

/*void		fastend_blur(t_sdl_things *things)
{
	int			rc;
	int			i;
	Uint32 *temp = things->m_buffer1;
	///swapping buffs here kek
	things->m_buffer1 = things->m_buffer2;
	things->m_buffer2 = temp;

	i = 0;
	while (i < THREAD_NUM)
	{
		if ((rc = pthread_create(&things->threads[i], NULL, threadman, things)))
			ft_error("kek shouldnt have tried to go fasta");
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(things->threads[i], NULL))
			ft_error("kek shouldnt have tried to go fasta");
		i++;
	}
//	draw_it_all(things);
}*/

void	blur_v4(t_sdl_things *things)
{
	/*OK FIRST WE SWAP BUFFS
	 * DO IT OUTSIDe BiiieeeeaAACH
	 */
	Uint32 *temp = things->m_buffer1;
	things->m_buffer1 = things->m_buffer2;
	things->m_buffer2 = temp;

	Uint32 color;
	int current_x = 0;
	int current_y = 0;
	int y = -1;
	int x;
	int box_blur_x;
	int extent = 3;
	Uint8 red = 0, green = 0, blue = 0;
	int redTotal, greenTotal, blueTotal;
	while (y++ < things->height)
	{
		x = -1;
		while (x++ < things->width)
		{
			box_blur_x = -extent - 1;
			redTotal = 0;
			greenTotal = 0;
			blueTotal = 0;
			while (box_blur_x++ <= extent)
			{
				current_x = x + box_blur_x;
				current_y = y;

				if (y >= 0 && x + box_blur_x >= 0 &&
				y < things->height && x + box_blur_x < things->width)////////вынести этот иф выше, ограничить рамку толщиной 1 пиксель?
				{
					color = things->m_buffer2[current_y * things->width + current_x];
					red = color;
					green = color >> 8;
					blue = color >> 16;

					redTotal += red;
					greenTotal += green;
					blueTotal += blue;
				}
				red = redTotal / 9;
				green = greenTotal / 9;
				blue = blueTotal / 9;
			}
			if (red || green || blue)
			{
				SDL_SetRenderDrawColor(things->renderer, red, green, blue, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawPoint(things->renderer, current_x, current_y);
			}

		}
	}
}
