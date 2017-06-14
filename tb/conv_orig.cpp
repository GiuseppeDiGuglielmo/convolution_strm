#include "conv_orig.h"

/* See conv_orig.h */

void filter_3x3_impulse_orig(unsigned height, unsigned width, unsigned *src, unsigned *dst)
{
	unsigned hcoeff[KSIZE];
	unsigned vcoeff[KSIZE];

	InitHCoeff: for (unsigned k = 0; k < KSIZE; k++)
	{
		hcoeff[k] = 0;
	}
	hcoeff[KSIZE/2] = 1;

	InitVCoeff: for (unsigned k = 0; k < KSIZE; k++)
	{
		vcoeff[k] = 0;
	}
	vcoeff[KSIZE/2] = 1;

	convolution_orig<unsigned, KSIZE>(height, width, src, dst, hcoeff, vcoeff);
}

