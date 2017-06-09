#include "conv_orig.h"

/* See conv_orig.h */

void top_convolution_orig(unsigned height, unsigned width, unsigned *src, unsigned *dst, const unsigned hcoeff[KSIZE], const unsigned vcoeff[KSIZE])
{
	convolution_orig<unsigned, KSIZE>(height, width, src, dst, hcoeff, vcoeff);
}

