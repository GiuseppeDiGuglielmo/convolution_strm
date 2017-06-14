#include "conv.h"

template<typename T, int K>
static void convolution_strm(int height, int width, hls::stream<T> &src, hls::stream<T> &dst, const T *hcoeff, const T *vcoeff)
{
	// The border width is half the convolution window - rounded down
	const int border_width = int(K / 2);
	const int vconv_xlim = width - (K - 1);

	// Local streams
	hls::stream<T> hconv("hconv");
	hls::stream<T> vconv("vconv");

	// Horizontal pixel window (cache)
	T hwin[K];

	// Line-buffer for border pixel replication
	T borderbuf[MAX_IMG_COLS - (K - 1)];

	// Line-buffers allowing full pixel reuse in vertical pass
	static T linebuf[K-1][MAX_IMG_COLS];
#pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1
#pragma HLS INLINE // Into a DATAFLOW region

	// These assertions let HLS know the upper bounds of loops
	assert(height <= MAX_IMG_ROWS);
	assert(width <= MAX_IMG_COLS);
	assert(vconv_xlim <= MAX_IMG_COLS - (K - 1));

	// Horizontal convolution
	HconvH: for (int row = 0; row < height; row++)
	{
		HconvW: for (int col = 0; col < width; col++)
		{
#pragma HLS PIPELINE
			T in_val = src.read();

			T out_val = 0;
			HConv: for (int i = 0; i < K; i++)
			{
				hwin[i] = i < K - 1 ? hwin[i + 1] : in_val;
				out_val += hwin[i] * hcoeff[i];
			}
			if (col >= K - 1)
			{
                hconv << out_val;
			}
		}
	}

	// Vertical convolution
	VconvH: for (int row = 0; row < height; row++)
	{
		VconvW: for (int col = 0; col < vconv_xlim; col++)
		{
#pragma HLS DEPENDENCE variable=linebuf inter true
#pragma HLS PIPELINE
			T in_val = hconv.read();

			T out_val = 0;
			Vconv: for (int i = 0; i < K; i++)
			{
				T vwin_val = i < K - 1 ? linebuf[i][col] : in_val;
				out_val += vwin_val * vcoeff[i];
				if (i > 0)
					linebuf[i - 1][col] = vwin_val;
			}
			if (row >= K - 1)
			{
				vconv << out_val;
			}
		}
	}

	// Handle the borders
	BorderRow: for (int row = 0; row < height; row++)
	{
		BorderCol: for (int col = 0; col < width; col++)
		{
			T pix_in, l_edge_pix, r_edge_pix, pix_out;
#pragma HLS PIPELINE
			if (row == 0 || (row > border_width && row < height - border_width))
			{
				if (col < width - (K - 1))
				{
					pix_in = vconv.read();
					borderbuf[col] = pix_in;
				}
				if (col == 0)
				{
					l_edge_pix = pix_in;
				}
				if (col == width - K)
				{
					r_edge_pix = pix_in;
				}
			}
			if (col <= border_width)
			{
				pix_out = l_edge_pix;
			} else if (col >= width - border_width - 1) {
				pix_out = r_edge_pix;
			} else {
				pix_out = borderbuf[col - border_width];
			}
			dst << pix_out;
		}
	}
}

void filter_3x3_impulse_strm(int height, int width, hls::stream<data_t> &src, hls::stream<data_t> &dst)
{
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst

#pragma HLS DATAFLOW
#pragma HLS INLINE region // bring loops in sub-functions to this DATAFLOW region

	const data_t coeff[KSIZE] = {0, 1, 0};

	convolution_strm<data_t, KSIZE>(height, width, src, dst, coeff, coeff);
}
