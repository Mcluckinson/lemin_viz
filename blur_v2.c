#include "lem_viz.h"
//
// Created by scump on 29.04.2020.
//
/////////////THIS BELOW GETS THE VALAUE OF A PIXEL AIIII

/*void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("BoxBlurrer",
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  window_width, window_height, SDL_WINDOW_SHOWN);
	windowSurface = SDL_GetWindowSurface(window);
	imageSurface = IMG_Load(input_image_name.c_str());
}*/

/*void blur_v(t_sdl_things *things) //This manipulates with SDL_Surface and gives it box blur effect
{
	SDL_Texture	*source = things->background;
	SDL_Texture *dest = SDL_CreateTexture(things->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, things->width, things->height);
	int blur_extent = 3;


	Uint32* pixels = NULL;
	int pitch = 0;
	Uint32 format;

// Get the size of the texture.
	int w;
	int h;

	SDL_QueryTexture(source, &format, NULL, &w, &h);//////////maybe different SDL_textureaccess?

// Now let's make our "pixels" pointer point to the texture data.
	if (SDL_LockTexture(source, NULL, (void**)&pixels, &pitch))
	{
		// If the locking fails, you might want to handle it somehow. SDL_GetError(); or something here.
	}

	SDL_PixelFormat pixelFormat;
	pixelFormat.format = format;
	Uint8 R, G, B;
// Now you want to format the color to a correct format that SDL can use.
// Basically we convert our RGB color to a hex-like BGR color.
	Uint32 color = SDL_MapRGB(&pixelFormat, R, G, B);

// Before setting the color, we need to know where we have to place it.
	Uint32 pixelPosition = y * (pitch / sizeof(unsigned int)) + x;

// Now we can set the pixel(s) we want.
	pixels[pixelPosition] = color;

// Also don't forget to unlock your texture once you're done.
	SDL_UnlockTexture(texture);



	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		printf("TRUE\n");
	else
		printf("FALSE\n");
	Uint32 rr_mask = 0xff000000;
	Uint32 gg_mask = 0x00ff0000;
	Uint32 bb_mask = 0x0000ff00;
	Uint32 aa_mask = 0x000000ff;

	///////////IMA TRY IT AOUT
/*	Uint32 rr_mask = 0x000000ff;
	Uint32  gg_mask = 0x0000ff00;
	Uint32 bb_mask = 0x00ff0000;
	Uint32 aa_mask = 0xff000000;
*/

/*	for (int y = 0; y < things->height; y++)
	{
		for (int x = 0; x < (things->width); x++)
		{
			Uint32 color = ((Uint32*)surf_origin->pixels)[(y * (surf->pitch / 4)) + x];

			//SDL_GetRGBA() is a method for getting color
			//components from a 32 bit color
			Uint8 r = 0, g = 0, b = 0, a = 0;
			SDL_GetRGBA(color, surf_origin->format, &r, &g, &b, &a);

			Uint32 rb = 0, gb = 0, bb = 0, ab = 0;

			//Within the two for-loops below, colors of adjacent pixels are added up

			for (int yo = -blur_extent; yo <= blur_extent; yo++)
			{
				for (int xo = -blur_extent; xo <= blur_extent; xo++)
				{
					if (y + yo >= 0 && x + xo >= 0

					&& y + yo < surf->h && x + xo < (surf_origin->pitch / 4)
							)
					{
						Uint32 colOth = ((Uint32*)surf_origin->pixels)[((y + yo)
																		 * (surf_origin->pitch / 4)) + (x + xo)];

						Uint8 ro = 0, go = 0, bo = 0, ao = 0;
						SDL_GetRGBA(colOth, surf_origin->format, &ro, &go, &bo, &ao);

						rb += ro;
						gb += go;
						bb += bo;
						ab += ao;
					}
				}
			}

			//The sum is then, divided by the total number of
			//pixels present in a block of blur radius

			//For blur_extent 1, it will be 9
			//For blur_extent 2, it will be 25
			//and so on...

			//In this way, we are getting the average of
			//all the pixels in a block of blur radius

			//(((blur_extent * 2) + 1) * ((blur_extent * 2) + 1)) calculates
			//the total number of pixels present in a block of blur radius

			r = (Uint8)(rb / (((blur_extent * 2) + 1) * ((blur_extent * 2) + 1)));
			g = (Uint8)(gb / (((blur_extent * 2) + 1) * ((blur_extent * 2) + 1)));
			b = (Uint8)(bb / (((blur_extent * 2) + 1) * ((blur_extent * 2) + 1)));
			a = (Uint8)(ab / (((blur_extent * 2) + 1) * ((blur_extent * 2) + 1)));

			//Bit shifting color bits to form a 32 bit proper colour
			color = (r) | (g << 8) | (b << 16) | (a << 24);
			((Uint32*)surf->pixels)[(y * (surf->pitch / 4)) + x] = color;
		}
	}

	SDL_BlitSurface(surf, NULL, surf_origin, NULL);
//	SDL_FreeSurface(surf);
}

/*void update()
{
	//Putting surface onto the screen
	SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
	SDL_UpdateWindowSurface(window);
}*/

