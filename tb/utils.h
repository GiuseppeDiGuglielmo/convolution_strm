#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

template<typename T>
void print_matrix(std::ostream &out, unsigned width, unsigned height, std::string label, const T *matrix)
{
	out << "INFO: " << label << ": " << std::endl;
	for (unsigned row = 0; row < height; row++)
	{
		out << "INFO: ";
		for (unsigned col = 0; col < width; col++)
		{
			out << matrix[row * width + col] << " ";
		}
		out << std::endl;
	}
}

#endif
