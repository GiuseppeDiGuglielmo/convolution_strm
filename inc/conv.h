#ifndef __CONV_H__
#define __CONV_H__

#include <hls_stream.h>

#ifndef __SYNTHESIS__
#include "utils.h"
#endif

#define MAX_IMG_ROWS 1920
#define MAX_IMG_COLS 1080

#define data_t unsigned
#define K 5

void convolution_strm(unsigned width, unsigned height, hls::stream<data_t> &src, hls::stream<data_t> &dst, const data_t hcoeff[K], const data_t vcoeff[K]);

#endif
