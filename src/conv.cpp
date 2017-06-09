#include "conv.h"

/* See conv.h */

void top_convolution_strm(unsigned height, unsigned width, hls::stream<unsigned> &src, hls::stream<unsigned> &dst, const unsigned hcoeff[KSIZE], const unsigned vcoeff[KSIZE])
{
	convolution_strm<unsigned, KSIZE>(height, width, src, dst, hcoeff, vcoeff);
}
