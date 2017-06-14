#ifndef __CONV_ORIG_H__
#define __CONV_ORIG_H__

#include "config.h"
#include "utils.h"

template <typename T, unsigned K>
void convolution_orig(unsigned height, unsigned width, const T *src, T *dst, const T *hcoeff, const T *vcoeff)
{
	const int conv_size = K;
	const int border_width = int(conv_size / 2);

	T * const local = new T[MAX_IMG_ROWS * MAX_IMG_COLS];

	Clear_Local: for (int i = 0; i < height * width; i++)
	{
		local[i] = 0;
	}

	// Horizontal convolution
	HconvH: for (int row = 0; row < height; row++)
	{
		HconvW: for (int col = border_width; col < width - border_width; col++) {
			int pixel = row * width + col;
			Hconv: for (int i = -border_width; i <= border_width; i++)
			{
				local[pixel] += src[pixel + i] * hcoeff[i + border_width];
			}
		}
	}

	Clear_Dst: for(int i = 0; i < height * width; i++)
	{
		dst[i]=0;
	}

	// Vertical convolution
	VconvH: for(int row = border_width; row < height - border_width; row++)
	{
		VconvW: for(int col = 0; col < width; col++)
		{
			int pixel = row * width + col;
			Vconv: for(int i = - border_width; i <= border_width; i++)
			{
				int offset = i * width;
				dst[pixel] += local[pixel + offset] * vcoeff[i + border_width];
			}
		}
	}

	int border_width_offset = border_width * width;
	int border_height_offset = (height - border_width - 1) * width;

	// Border pixels
	TopBorder: for(int row = 0; row < border_width; row++)
	{
		int offset = row * width;
		TopLeftBorder: for(int col = 0; col < border_width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[border_width_offset + border_width];
		}
		TopCenterBorder: for(int col = border_width; col < width - border_width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[border_width_offset + col];
		}
		TopRightBorder: for(int col = width - border_width; col < width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[border_width_offset + width - border_width - 1];
		}
	}
	Side_Border: for(int row = border_width; row < height - border_width; row++)
	{
		int offset = row * width;
		Side_Left_Border: for(int col = 0; col < border_width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[offset + border_width];
		}
		Side_Right_Border: for(int col = width - border_width; col < width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[offset + width - border_width - 1];
		}
	}
	BottomBorder: for(int row = height - border_width; row < height; row++)
	{
		int offset = row * width;
		BottomLeftBorder: for(int col = 0; col < border_width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[border_height_offset + border_width];
		}
		BottomCenterBorder: for(int col = border_width; col < width - border_width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[border_height_offset + col];
		}
		BottomRightBorder: for(int col = width - border_width; col < width; col++)
		{
			int pixel = offset + col;
			dst[pixel] = dst[border_height_offset + width - border_width - 1];
		}
	}
}

void filter_3x3_impulse_orig(unsigned height, unsigned width, unsigned *src, unsigned *dst);

#endif
