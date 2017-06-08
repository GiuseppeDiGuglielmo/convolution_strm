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

void set_input_data(hls::stream<data_t> &stream, data_t *matrix, unsigned n_data)
{
	for (unsigned idx = 0; idx < n_data; idx++)
	{
		matrix[idx] = idx;
		stream << idx;
	}
}

void set_impulse_coefficient(data_t* coeff)
{
	for (unsigned k = 0; k < K; k++)
		coeff[k] = 0;
	coeff[K/2] = 1;
}

void run_validation(data_t *ref, data_t *imp, unsigned n_data)
{
	unsigned errors = 0;
	for (unsigned idx = 0; idx < n_data; idx++)
		if (ref[idx] != imp[idx])
			errors++;
	if (errors > 0)
		std::cout
				<< "ERROR: Reference and implementation matrices do no match! ("
				<< errors << " errors out of " << n_data
				<< " elements)" << std::endl;
	else
		std::cout
				<< "INFO: Reference and implementation perfectly match! (no errors out of "
				<< n_data << " elements)" << std::endl;
}

int main(int argc, char** argv)
{
	data_t *src = new data_t[IMG_ROWS * IMG_COLS];
	data_t *dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *orig_dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *hcoeff = new data_t[K];
	data_t *vcoeff = new data_t[K];

	hls::stream<data_t> src_stream("src_stream");
	hls::stream<data_t> dst_stream("dst_stream");

	set_input_data(src_stream, src, IMG_ROWS*IMG_COLS);
	set_impulse_coefficient(hcoeff);
	set_impulse_coefficient(vcoeff);

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
#ifdef VERBOSE
	print_matrix(std::cout, IMG_ROWS, IMG_COLS, "Implementation output matrix", dst);
#endif
	#endif

    // Validation
    convolution_orig(IMG_ROWS, IMG_COLS, K, src, orig_dst, hcoeff, vcoeff);

#ifdef VERBOSE
	print_matrix(std::cout, IMG_ROWS, IMG_COLS, "Reference output matrix", orig_dst, K, true);
#endif

	//run_validation(orig_dst, dst, IMG_ROWS*IMG_COLS);

	delete[] src;
	delete[] dst;
	delete[] orig_dst;
	delete[] hcoeff;
	delete[] vcoeff;

	return 0;
}
