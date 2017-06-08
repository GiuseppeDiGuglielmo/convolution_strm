#include "conv.h"

#include <cassert>

void convolution_strm(unsigned height, unsigned width, hls::stream<data_t> &src, hls::stream<data_t> &dst, const data_t hcoeff[K], const data_t vcoeff[K])
{
#pragma HLS INTERFACE s_axilite depth=K port=vcoeff bundle=CTRLS
#pragma HLS INTERFACE s_axilite depth=K port=hcoeff bundle=CTRLS
#pragma HLS INTERFACE s_axilite port=height bundle=CTRLS
#pragma HLS INTERFACE s_axilite port=width bundle=CTRLS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRLS
#pragma HLS INTERFACE axis register both port=dst
#pragma HLS INTERFACE axis register both port=src

#pragma HLS DATAFLOW

	// Local streams and buffers
	hls::stream<data_t> hconv("hconv");
	hls::stream<data_t> vconv("vconv");
	unsigned hwin[K];
	unsigned borderbuf[MAX_IMG_COLS];
	unsigned linebuf[K-1][(MAX_IMG_COLS-(K/2))];
#pragma HLS ARRAY_PARTITION variable=linebuf dim=1 complete

	const unsigned conv_size = K;
	const unsigned border_width = int(conv_size / 2);
	const unsigned vconv_xlim = width - (K - 1);

	// These assertions let HLS know the upper bounds of loops
	assert(height < MAX_IMG_ROWS);
	assert(width < MAX_IMG_COLS);
	assert(vconv_xlim < MAX_IMG_COLS - (K - 1));

	// Horizontal convolution
	HconvH: for (unsigned row = 0; row < height; row++)
	{
		HconvW: for(unsigned col = 0; col < width; col++)
		{
#pragma HLS PIPELINE
			data_t in_val = src.read();
			data_t out_val = 0;
			HConv: for(unsigned i = 0; i < K; i++)
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
	VconvH: for(int row = 0; row < height; row++)
	{
		VconvW: for(int col = 0; col < vconv_xlim; col++)
		{
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=linebuf inter false
			data_t in_val = hconv.read();
			data_t out_val = 0;
			Vconv: for(int i = 0; i < K; i++)
			{
				data_t vwin_val = i < K - 1 ? linebuf[i][col] : in_val;
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

	BorderRow: for (int row = 0; row < height; row++)
	{
		BorderCol: for (int col = 0; col < width; col++)
		{
			data_t pix_in, l_edge_pix, r_edge_pix, pix_out;
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
			} else if (col >= width - border_width - 1)
			{
				pix_out = r_edge_pix;
			} else {
				pix_out = borderbuf[col - border_width];
			}
			dst << pix_out;
		}
	}
}

