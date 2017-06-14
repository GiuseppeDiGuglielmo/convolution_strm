#include <iostream>

#include "conv_orig.h"
#include "config.h"
#include "utils.h"
#include "conv.h"

#define data_t unsigned

void set_input_data(hls::stream<data_t> &stream, data_t *matrix, unsigned n_data)
{
	for (unsigned idx = 0; idx < n_data; idx++)
	{
		matrix[idx] = idx;
		stream << idx;
	}
}

void get_output_data(data_t *matrix, hls::stream<data_t> &stream, unsigned n_data)
{
	for (unsigned idx = 0; idx < n_data; idx++)
		stream.read(matrix[idx]);
}

void set_impulse_coefficient(data_t* coeff)
{
	for (unsigned k = 0; k < KSIZE; k++)
		coeff[k] = 0;
	coeff[KSIZE/2] = 1;
}

void run_validation(data_t *ref, data_t *imp, unsigned n_data)
{
	unsigned errors = 0;
	for (unsigned idx = 0; idx < n_data; idx++)
		if (ref[idx] != imp[idx])
			errors++;
	if (errors > 0)
	{
		std::cout << "INFO: Reference and implementation matrices do no match! (";
		std::cout << errors << " errors out of " << n_data << " elements)" << std::endl;
		std::cout << "ERROR: Validation failed!" << std::endl;
	} else {
		std::cout << "INFO: Reference and implementation perfectly match! (no errors out of ";
		std::cout << n_data << " elements)" << std::endl;
		std::cout << "INFO: Validation succeeded!" << std::endl;
	}
}

int main(int argc, char** argv)
{
	data_t *src = new data_t[IMG_ROWS * IMG_COLS];
	data_t *dst = new data_t[IMG_ROWS * IMG_COLS];
	data_t *orig_dst = new data_t[IMG_ROWS * IMG_COLS];

	hls::stream<data_t> src_stream("src_stream");
	hls::stream<data_t> dst_stream("dst_stream");

	set_input_data(src_stream, src, IMG_ROWS * IMG_COLS);

#ifdef VERBOSE
	print_matrix<unsigned, KSIZE>(std::cout, IMG_ROWS, IMG_COLS, "Input matrix", src);
#endif

	filter_3x3_impulse_strm(IMG_ROWS, IMG_COLS, src_stream, dst_stream);

	get_output_data(dst, dst_stream, (IMG_ROWS * IMG_COLS));
	//get_output_data(dst, dst_stream, (IMG_ROWS * IMG_COLS) - (IMG_ROWS*(2*(KSIZE/2))) );
	//get_output_data(dst, dst_stream, ((IMG_ROWS - 2*(KSIZE/2)) * (IMG_COLS - 2*(KSIZE/2))) );

#ifdef VERBOSE
	print_matrix<unsigned, KSIZE>(std::cout, IMG_ROWS, IMG_COLS, "Implementation output matrix", dst, true);
#endif

    // Validation
	filter_3x3_impulse_orig(IMG_ROWS, IMG_COLS, src, orig_dst);

#ifdef VERBOSE
	print_matrix<unsigned, KSIZE>(std::cout, IMG_ROWS, IMG_COLS, "Reference output matrix", orig_dst, true);
#endif

	run_validation(orig_dst, dst, IMG_ROWS*IMG_COLS);

	delete[] src;
	delete[] dst;
	delete[] orig_dst;

	return(0);
}
