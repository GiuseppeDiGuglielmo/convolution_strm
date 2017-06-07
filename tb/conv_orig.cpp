#include "conv_orig.h"

void convolution_orig(unsigned width, unsigned height, const data_t *src, data_t *dst, const data_t *hcoeff, const data_t *vcoeff)
{
	const int conv_size = K;
	const int border_width = int(conv_size / 2);

	data_t * const local = new data_t[MAX_IMG_ROWS * MAX_IMG_COLS];

	Clear_Local: for (int i = 0; i < height * width; i++)
	{
		local[i] = 0;
	}

	// Horizontal convolution
	HconvH: for (int col = 0; col < height; col++)
	{
		HconvW: for (int row = border_width; row < width - border_width; row++) {
			int pixel = col * width + row;
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
	VconvH: for(int col = border_width; col < height - border_width; col++)
	{
		VconvW: for(int row = 0; row < width; row++)
		{
			int pixel = col * width + row;
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
	Top_Border: for(int col = 0; col < border_width; col++)
	{
		int offset = col * width;
		Top_Left_Border: for(int row = 0; row < border_width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[border_width_offset + border_width];
		}
		Top_Center_Border: for(int row = border_width; row < width - border_width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[border_width_offset + row];
		}
		Top_Right_Border: for(int row = width - border_width; row < width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[border_width_offset + width - border_width - 1];
		}
	}

	Side_Border: for(int col = border_width; col < height - border_width; col++)
	{
		int offset = col * width;
		Side_Left_Border: for(int row = 0; row < border_width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[offset + border_width];
		}
		Side_Right_Border: for(int row = width - border_width; row < width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[offset + width - border_width - 1];
		}
	}

	Bottom_Border: for(int col = height - border_width; col < height; col++)
	{
		int offset = col * width;
		Bottom_Left_Border: for(int row = 0; row < border_width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[border_height_offset + border_width];
		}
		Bottom_Center_Border: for(int row = border_width; row < width - border_width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[border_height_offset + row];
		}
		Bottom_Right_Border: for(int row = width - border_width; row < width; row++)
		{
			int pixel = offset + row;
			dst[pixel] = dst[border_height_offset + width - border_width - 1];
		}
	}
}