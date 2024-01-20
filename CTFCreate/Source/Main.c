#include <CTF.h>

#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main( int argc, char** argv )
{
	int width;
	int height;
	u32* pixels = stbi_load( argv[1], &width, &height, NULL, 4 );

	CTF_Image* image = CTF_Image_Create( pixels, width, height, NEAREST, WRAP );

	CTF_Image_WriteToDisk( argv[2], image );
	return 0;
}