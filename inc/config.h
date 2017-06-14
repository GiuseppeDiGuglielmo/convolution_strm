#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>

#define INPUT_SIZE_4KUHD

typedef uint32_t data_t;

// Max 8K Ultra-HD
#define MAX_IMG_COLS 7680
#define MAX_IMG_ROWS 4320

#if defined(INPUT_SIZE_TINY)
#define IMG_COLS 6
#define IMG_ROWS 4

#elif defined(INPUT_SIZE_CGA)
#define IMG_COLS 320
#define IMG_ROWS 240

#elif defined(INPUT_SIZE_VGA)
#define IMG_COLS 640
#define IMG_ROWS 480

#elif defined(INPUT_SIZE_WXGA)
#define IMG_COLS 1280
#define IMG_ROWS 720

#elif defined(INPUT_SIZE_HD)
#define IMG_COLS 1360
#define IMG_ROWS 768

#elif defined(INPUT_SIZE_HDPLUS)
#define IMG_COLS 1600
#define IMG_ROWS 900

#elif defined(INPUT_SIZE_FHD)
#define IMG_COLS 1920
#define IMG_ROWS 1080

#elif defined(INPUT_SIZE_4KUHD)
#define IMG_COLS 3840
#define IMG_ROWS 2160

#elif defined(INPUT_SIZE_8KUHD)
#define IMG_COLS 7680
#define IMG_ROWS 4320

#endif

#define KSIZE 3

#endif
