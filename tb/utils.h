#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <iomanip>

#ifdef COLORIZED_OUTPUT
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
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

template<typename T>
void print_matrix(std::ostream &out, unsigned n_rows, unsigned n_cols, std::string label, const T *matrix, unsigned K = 0, bool highlight = false)
{
#ifdef COLORIZED_OUTPUT
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier def(Color::FG_DEFAULT);
#else
        std::string green = "";
        std::string def = "";
#endif
	out << def << "INFO: " << label << " [ " <<  n_rows << " x " << n_cols <<" ]" << std::endl;
	for (unsigned row = 0; row < n_rows; row++)
	{
		out << def << "INFO: ";
		for (unsigned col = 0; col < n_cols; col++)
		{
                        unsigned idx = row * n_cols + col;
                        bool is_core = true;
                        is_core &= (row >= (K/2) && row < (n_rows - (K/2))); // check rows
                        is_core &= (col >= (K/2) && col < (n_cols - (K/2))); // check cols
			out << ((is_core && highlight)?green:def) << std::setw(5) << std::right << matrix[idx] << " ";
		}
		out << std::endl;
	}
	out << def << "INFO:" << std::endl;
}


#endif
