#include "conv.h"

//#include <hls_video.h>
#include <cassert>

#if 0
void convolution_strm(unsigned width, unsigned height, hls::stream<data_t> &src, hls::stream<data_t> &dst, const data_t hcoeff[K], const data_t vcoeff[K])
{
#pragma HLS INTERFACE s_axilite depth=5 port=vcoeff bundle=CTRLS
#pragma HLS INTERFACE s_axilite depth=5 port=hcoeff bundle=CTRLS
#pragma HLS INTERFACE s_axilite port=height bundle=CTRLS
#pragma HLS INTERFACE s_axilite port=width bundle=CTRLS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRLS
#pragma HLS INTERFACE axis register both port=dst
#pragma HLS INTERFACE axis register both port=src

#pragma HLS DATAFLOW

	hls::stream<data_t> hconv("hconv");
	hls::stream<data_t> vconv("vconv");
	unsigned hwin[K];

	const unsigned conv_size = K;
	const unsigned border_width = int(conv_size / 2);
	const unsigned vconv_xlim = width - (K - 1);

	//hls::LineBuffer<K-1, (MAX_IMG_COLS-(K/2)), data_t> linebuf;
	unsigned linebuf[K-1][(MAX_IMG_COLS-(K/2))];
#pragma HLS ARRAY_PARTITION variable=linebuf dim=1 complete

	unsigned borderbuf[MAX_IMG_COLS];

	// These assertions let HLS know the upper bounds of loops
	assert(height < MAX_IMG_ROWS);
	assert(width < MAX_IMG_COLS);
	assert(vconv_xlim < MAX_IMG_COLS - (K - 1));

	// Horizontal convolution
	HConvW: for(unsigned row = 0; row < width; row++)
	{
		HconvW:for(unsigned row = border_width; row < width - border_width; row++)
		{
#pragma HLS PIPELINE
			data_t in_val = src.read();
			data_t out_val = 0;
			HConv: for(unsigned i = 0; i < K; i++)
			{
				hwin[i] = i < K - 1 ? hwin[i + 1] : in_val;
				out_val += hwin[i] * hcoeff[i];
			}
			if (row >= K - 1)
				hconv << out_val;
		}
	}

	// Vertical convolution
	VConvH: for(int col = 0; col < height; col++)
	{
		VConvW: for(int row = 0; row < vconv_xlim; row++)
		{
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=linebuf inter false
			data_t in_val = hconv.read();
			data_t out_val = 0;
			VConv: for(int i = 0; i < K; i++)
			{
				data_t vwin_val = i < K - 1 ? linebuf[i][row] : in_val;
				out_val += vwin_val * vcoeff[i];
				if (i > 0)
					linebuf[i - 1][row] = vwin_val;
			}
			if (col >= K - 1)
				vconv << out_val;
		}
	}

	Border: for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data_t pix_in, l_edge_pix, r_edge_pix, pix_out;
#pragma HLS PIPELINE
			if (i == 0 || (i > border_width && i < height - border_width))
			{
				if (j < width - (K - 1))
				{
					pix_in = vconv.read();
					borderbuf[j] = pix_in;
				}
				if (j == 0)
				{
					l_edge_pix = pix_in;
				}
				if (j == width - K)
				{
					r_edge_pix = pix_in;
				}
			}
			if (j <= border_width)
			{
				pix_out = l_edge_pix;
			} else if (j >= width - border_width - 1)
			{
				pix_out = r_edge_pix;
			} else {
				pix_out = borderbuf[j - border_width];
			}
			dst << pix_out;
		}
	}
}
#endif
