#include <iostream>

#include "conv.h"
#include "conv_orig.h"
#include "utils.h"

#ifdef INPUT_SIZE_SMALL
#define IMG_ROWS 4
#define IMG_COLS 6
#else
#define IMG_ROWS 1080
#define IMG_COLS 1920
#endif
#define K 3

int main(int argc, char** argv)
{
	data_t *src = new data_t[IMG_ROWS * IMG_COLS];
	data_t *dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *orig_dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *hcoeff = new data_t[K];
	data_t *vcoeff = new data_t[K];

#if 0
	unsigned errors = 0;
	hls::stream<data_t> src_stream("src_stream");
	hls::stream<data_t> dst_stream("dst_stream");
#endif

	// Initialize input stream (and input matrix)
	for (unsigned row = 0; row < IMG_ROWS; row++)
	{
		for (unsigned col = 0; col < IMG_COLS; col++)
		{
			unsigned idx = row * IMG_COLS + col;
			src[idx] = idx;
#if 0
			src_stream << idx;
#endif
		}
	}

	// Set the coefficients
#if 1
	// Impulse
	for (unsigned k = 0; k < K; k++)
		hcoeff[k] = 0;
	for (unsigned k = 0; k < K; k++)
		vcoeff[k] = 0;
	hcoeff[K/2] = 1;
	vcoeff[K/2] = 1;
#else
	for (unsigned k = 0; k < K; k++)
		hcoeff[k] = 1;
	for (unsigned k = 0; k < K; k++)
		vcoeff[k] = 1;
#endif

#ifdef VERBOSE
	print_matrix(std::cout, IMG_ROWS, IMG_COLS, "Input matrix", src);
	print_matrix(std::cout, K, 1, "Horizontal coefficients", hcoeff);
	print_matrix(std::cout, 1, K, "Vertical coefficients", vcoeff);
#endif
#if 0
	convolution_strm(IMG_COLS, IMG_ROWS, src_stream, dst_stream, hcoeff, vcoeff);

	// Read the output stream and copy the data in the output matrix
	for (unsigned row = 0; row < IMG_ROWS; row++)
	{
		for (unsigned col = 0; col < IMG_ROWS; col++)
		{
			dst_stream.read(dst[row * IMG_COLS + col]);
		}
	}
#endif
#ifdef VERBOSE
	print_matrix(std::cout, IMG_ROWS, IMG_COLS, "Implementation output matrix", dst);
#endif

        // Validation
        convolution_orig(IMG_ROWS, IMG_COLS, K, src, orig_dst, hcoeff, vcoeff);

#ifdef VERBOSE
	print_matrix(std::cout, IMG_ROWS, IMG_COLS, "Reference output matrix", orig_dst, K, true);
#endif

#if 0
	errors = 0;
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
#endif

	delete[] src;
	delete[] dst;
	delete[] orig_dst;
	delete[] hcoeff;
	delete[] vcoeff;

	return 0;
}
