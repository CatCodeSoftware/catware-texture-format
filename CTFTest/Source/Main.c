#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <CTF.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main( int argc, char** argv )
{
	{
		int width;
		int height;
		u32* pixels = stbi_load( "testImage.tga", &width, &height, NULL, 4 );

		CTF_Image* image = CTF_Image_Create( pixels, width, height, NEAREST, WRAP );

		CTF_Image_WriteToDisk( "testImage2.ctf", image );
	}

	CTF_Image* image = CTF_Image_Load( "testImage2.ctf" );
	SDL_Window* window = SDL_CreateWindow( "CTF Test", 30, 30, image->width * 4, image->height * 4, SDL_WINDOW_SHOWN );
	bool close = false;

	if ( !window )
		printf( "%s", SDL_GetError( ) );

	SDL_Event e;

	SDL_Surface* surface = SDL_GetWindowSurface( window );

	while ( !close )
	{
		while ( SDL_PollEvent( &e ) )
		{
			if ( e.type == SDL_QUIT )
				close = true;
		}

		for ( u16 y = 0; y < image->height; y++ )
			for ( u16 x = 0; x < image->width; x++ )
			{
				for ( u8 offset = 0; offset < 4; offset++ )
					( ( u32* ) surface->pixels )[y * 4 * image->width + x * 4 + offset] = image->pixels[y * image->width + x];
			}

		SDL_UpdateWindowSurface( window );
	}

	return 0;
}
