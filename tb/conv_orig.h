#ifndef __CONV_ORIG_H__
#define __CONV_ORIG_H__

#include "utils.h"

#define MAX_IMG_ROWS 1920
#define MAX_IMG_COLS 1080

#define data_t unsigned

void convolution_orig(unsigned width, unsigned height, unsigned K, const data_t *src, data_t *dst, const data_t *hcoeff, const data_t *vcoeff);

#endif
