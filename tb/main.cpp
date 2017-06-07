#include <iostream>

#include "conv.h"
#include "conv_orig.h"
#include "utils.h"

#define IMG_ROWS 16
#define IMG_COLS 16

//#define VERBOSE

int main(int argc, char** argv)
{
	data_t *src = new data_t[IMG_ROWS * IMG_COLS];
	data_t *dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *orig_dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *hcoeff = new data_t[K];
	data_t *vcoeff = new data_t[K];

	unsigned errors = 0;

	hls::stream<data_t> src_stream;
	hls::stream<data_t> dst_stream;

	// Initialize input stream (and input matrix)
	for (unsigned row = 0; row < IMG_ROWS; row++)
	{
		for (unsigned col = 0; col < IMG_ROWS; col++)
		{
			unsigned idx = col * IMG_COLS + col;
			src[idx] = idx;
			src_stream << idx;
		}
	}

	// Set the coefficients
#if 0
	// Impulse
	hcoeff[2] = 1;
	vcoeff[2] = 1;
#else
	for (unsigned k = 0; k < K; k++)
		hcoeff[k] = 1;
	for (unsigned k = 0; k < K; k++)
		vcoeff[k] = 1;
#endif

#ifdef VERBOSE
	print_matrix(std::cout, IMG_COLS, IMG_ROWS, "Input matrix", src);
	print_matrix(std::cout, K, 1, "Horizontal coefficients", hcoeff);
	print_matrix(std::cout, 1, K, "Vertical coefficients", vcoeff);
#endif

	convolution_strm(IMG_COLS, IMG_ROWS, src_stream, dst_stream, hcoeff, vcoeff);

	// Read the output stream and copy the data in the output matrix
	for (unsigned row = 0; row < IMG_ROWS; row++)
	{
		for (unsigned col = 0; col < IMG_ROWS; col++)
		{
			dst_stream.read(dst[row * IMG_COLS + col]);
		}
	}

#ifdef VERBOSE
	print_matrix(std::cout, IMG_COLS, IMG_ROWS, "Implementation output matrix", dst);
#endif

        // Validation
        convolution_orig(IMG_COLS, IMG_ROWS, src, orig_dst, hcoeff, vcoeff);

#ifdef VERBOSE
	print_matrix(std::cout, IMG_COLS, IMG_ROWS, "Reference output matrix", orig_dst);
#endif

	errors++;
	for (unsigned row = 0; row < IMG_ROWS; row++) {
		for (unsigned col = 0; col < IMG_ROWS; col++) {
			if (dst[row * IMG_COLS + col] != orig_dst[row * IMG_COLS + col])
				errors++;
		}
	}
	if (errors > 0)
		std::cout
				<< "ERROR: Reference and implementation matrices do no match! ("
				<< errors << " errors out of " << (IMG_ROWS * IMG_COLS)
				<< " elements)" << std::endl;
	else
		std::cout
				<< "INFO: Reference and implementation perfectly match! (no errors out of "
				<< (IMG_ROWS * IMG_COLS) << " elements)" << std::endl;


	delete[] src;
	delete[] dst;
	delete[] orig_dst;
	delete[] hcoeff;
	delete[] vcoeff;

	return 0;
}
