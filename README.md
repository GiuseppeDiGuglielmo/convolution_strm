# A convolution algorithm with optimal data access patterns

The convolution algorithm is described in the Vivado HLS User Guide *UG902 (v2017.1)* at the pages 361-380. Xilinx provides an implementation of it with the examples of Vivado HLS. I am trying to improving as much as possible. If you are willing to contribute, I will be glad.

## Current situation
    
The original source code is confusing in the use of row, col, width, height, MAX_IMG_ROWS, and MAX_IMG_COLS. I normalized the code:
- col, width, MAX_IMG_COLS are "horizontal" variable, dimension, constant
- row, height, MAX_IMG_ROWS are "vertical" variable, dimension, constant
