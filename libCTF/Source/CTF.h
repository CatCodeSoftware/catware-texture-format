#pragma once

#include <stdint.h>


#if defined( LIBCTF_STATIC )
#	define LIBCTF_API extern
#elif defined( LIBCTF_SHARED )
// todo: implement
#else
#	error Build type not defined
#endif

// int types
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#ifndef __cplusplus
// boolean
typedef enum
{
	false = 0,
	true = 1,
} bool;
#endif

#ifndef NULL
#	define NULL 0
#endif

typedef enum
{
	NEAREST = 0, LINEAR = 1,
} CTF_ScalingMethod;

typedef enum
{
	STRECH = 0, WRAP = 1,
} CTF_WrapMode;

typedef struct
{
	u16 width;
	u16 height;

	CTF_ScalingMethod scalingMethod;
	CTF_WrapMode wrapMode;

	u32* pixels; // rgba
} CTF_Image;

CTF_Image* CTF_Image_Load( char* filePath );
CTF_Image* CTF_Image_Create( u32* pixels, u16 width, u16 height, CTF_ScalingMethod scalingMethod, CTF_WrapMode wrapMode );
void CTF_Image_Destroy( CTF_Image* image );

void CTF_Image_WriteToDisk( char* path, CTF_Image* image );