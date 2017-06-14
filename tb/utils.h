#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <iomanip>

#ifdef COLORIZED_OUTPUT
namespace Color {
	enum Code {
		FG_DEFAULT = 39,
		FG_BLACK = 30,
		FG_RED = 31,
		FG_GREEN = 32,
		FG_YELLOW = 33,
		FG_BLUE = 34,
		FG_MAGENTA = 35,
		FG_CYAN = 36,
		FG_LIGHT_GRAY = 37,
		FG_DARK_GRAY = 90,
		FG_LIGHT_RED = 91,
		FG_LIGHT_GREEN = 92,
		FG_LIGHT_YELLOW = 93,
		FG_LIGHT_BLUE = 94,
		FG_LIGHT_MAGENTA = 95,
		FG_LIGHT_CYAN = 96,
		FG_WHITE = 97,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_BLUE = 44,
		BG_DEFAULT = 49
	};
	class Modifier {
		Code code;
	public:
		Modifier(Code pCode) : code(pCode) {}
		friend std::ostream&
		operator<<(std::ostream& os, const Modifier& mod) {
			return os << "\033[" << mod.code << "m";
		}
	};
}
#endif

template<typename T, unsigned K>
void print_matrix(std::ostream &out, unsigned n_rows, unsigned n_cols, std::string label, const T *matrix, bool highlight = false) {
#ifdef COLORIZED_OUTPUT
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier red(Color::FG_RED);
	Color::Modifier yellow(Color::FG_YELLOW);
	Color::Modifier def(Color::FG_DEFAULT);
#else
	std::string def = "";
#endif
	out << def << "INFO: " << label << " [ " << n_rows << " x " << n_cols
			<< " ]" << std::endl;
	if (n_rows < 128 && n_cols < 64)
	{
		for (unsigned row = 0; row < n_rows; row++)
		{
			out << def << "INFO: ";
			for (unsigned col = 0; col < n_cols; col++)
			{
				unsigned idx = row * n_cols + col;
#ifdef COLORIZED_OUTPUT
				bool is_core = true;
				is_core &= (row >= (K / 2) && row < (n_rows - (K / 2))); // check rows
				is_core &= (col >= (K / 2) && col < (n_cols - (K / 2)));// check cols
				bool is_corner = true;
				is_corner &= (row < (K / 2) | row >= (n_rows - (K / 2)));// check rows
				is_corner &= (col < (K / 2) | col >= (n_cols - (K / 2)));// check cols
				Color::Modifier color = def;
				if (highlight)
				{
					if (is_core) color = green;
					else if (is_corner) color = red;
					else color = yellow;
				}

#else
				std::string color = "";
#endif
				out << color << std::setw(5) << std::right << matrix[idx]
						<< " ";
			}
			out << std::endl;
		}
#ifdef COLORIZED_OUTPUT
		if (highlight)
		{
			out << def << "INFO: Color legend: " << std::endl;
			out << def << "INFO:   " << green << "core" << std::endl;
			out << def << "INFO:   " << red << "corners" << std::endl;
			out << def << "INFO:   " << yellow << "borders" << std::endl;
		}
#endif
	}
	out << def << "INFO:" << std::endl;
}

#endif
