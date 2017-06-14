#ifndef __CONV_H__
#define __CONV_H__

#include <hls_stream.h>
#include <cassert>

#include "config.h"

void filter_3x3_impulse_strm(int height, int width, hls::stream<data_t> &src, hls::stream<data_t> &dst);

#endif
