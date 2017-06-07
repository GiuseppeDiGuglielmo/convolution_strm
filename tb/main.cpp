#include <iostream>

#include "conv.h"
#include "utils.h"

#define IMG_ROWS 16
#define IMG_COLS 16

int main(int argc, char** argv)
{
	std::cout << "INFO: Testing convolution!" << std::endl;

	data_t *src = new data_t[IMG_ROWS * IMG_COLS];
	data_t *dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *hcoeff = new data_t[K];
	data_t *vcoeff = new data_t[K];

	hls::stream<data_t> src_stream;
	hls::stream<data_t> dst_stream;

	// Initialize input stream (and input matrix)
	for (unsigned row = 0; row < IMG_ROWS; row++)
	{
		for (unsigned col = 0; col < IMG_ROWS; col++)
		{
			src[row * IMG_COLS + col] = 1;
			src_stream << src[row * IMG_COLS + col];
		}
	}

	// Set the coefficients
#if 0
	// Impulse
	hcoeff[2] = 1;
	vcoeff[2] = 1;
#else
	for (unsigned k = 0; k < K; k++)
	{
		hcoeff[k] = 1;
	}

	for (unsigned k = 0; k < K; k++)
	{
		vcoeff[k] = 1;
	}
#endif

	print_matrix(std::cout, IMG_COLS, IMG_ROWS, "Input matrix", src);
	print_matrix(std::cout, K, 1, "Horizontal coefficients", src);
	print_matrix(std::cout, 1, K, "Vertical coefficients", src);

	convolution_strm(IMG_COLS, IMG_ROWS, src_stream, dst_stream, hcoeff, vcoeff);

	// Read the output stream and copy the data in the output matrix
	for (unsigned row = 0; row < IMG_ROWS; row++)
	{
		for (unsigned col = 0; col < IMG_ROWS; col++)
		{
			dst_stream.read(dst[row * IMG_COLS + col]);
		}
	}

	print_matrix(std::cout, IMG_COLS, IMG_ROWS, "Output matrix", dst);

	return 0;
}
