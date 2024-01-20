#include "CTF.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ctfError[128] = "No error";

char* CTF_GetError( )
{
	return ctfError;
}

CTF_Image* CTF_Image_Load( char* filePath )
{
	FILE* file = fopen( filePath, "rb" );
	CTF_Image* image = malloc( sizeof( CTF_Image ) );

	char header[4];
	char* desiredHeader = "CTF";
	u8 versionMajor, versionMinor;

	fread( &header, 1, 4, file );

	int diffrence = strcmp( header, desiredHeader );
	if ( diffrence != 0 )
	{
		strcpy( ctfError, "Not a CTF file!" );
		return 0;
	}

	fread( &versionMajor, 1, 1, file );
	fread( &versionMinor, 1, 1, file );

	if ( versionMajor == 1 )
	{
		if ( versionMinor == 0 )
		{
			fread( &image->width, 2, 1, file );
			fread( &image->height, 2, 1, file );

			fread( &image->scalingMethod, 1, 1, file );
			fread( &image->wrapMode, 1, 1, file );

			image->pixels = calloc( sizeof( u32 ),  image->width * image->height );
			fread( image->pixels, sizeof( u32 ), image->width * image->height, file );

			return image;
		}

		return 0;
	}

	return 0;

	fclose( file );
}

CTF_Image* CTF_Image_Create( u32* pixels, u16 width, u16 height, CTF_ScalingMethod scalingMethod, CTF_WrapMode wrapMode )
{
	CTF_Image* image = malloc( sizeof( CTF_Image ) );

	image->width = width;
	image->height = height;
	image->scalingMethod = scalingMethod;
	image->wrapMode = wrapMode;

	image->pixels = malloc( width * height * sizeof( u32 ) );
	memcpy( image->pixels, pixels, height * width * sizeof( u32 ) );

	return image;
}

void CTF_Image_Destroy( CTF_Image* image )
{
	free( image->pixels );
	free( image );
}

void CTF_Image_WriteToDisk( char* path, CTF_Image* image )
{
	FILE* file = fopen( path, "wb" );

	if ( file == NULL )
	{
		strcpy( ctfError, "Error when opening file" );
		return;
	}

	// printf( "a" );

	// header
	fwrite( "CTF", 1, 4, file );

	u8 versionMajor = 1;
	u8 versionMinor = 0;

	// version
	fwrite( &versionMajor, 1, 1, file );
	fwrite( &versionMinor, 1, 1, file );

	// size
	fwrite( &image->width, 2, 1, file );
	fwrite( &image->height, 2, 1, file );

	// render data
	fwrite( &image->scalingMethod, 1, 1, file );
	fwrite( &image->wrapMode, 1, 1, file );

	// image data
	fwrite( image->pixels, image->width * image->height, 1, file );

	fclose( file );
}
