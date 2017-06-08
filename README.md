# Algorithm With Optimal Data Access Patterns

The source code is from the Vivado HLS User Guide *UG902 (v2017.1)*. It is under development, if you are willing to contribute I will be glad. For a complete description see UG902 pages 361-380.

## Current situation
    
The original source code at page 362 of *UG902 (v2017.1)* is confusing in the use of row, col, width, height, MAX_IMG_ROWS, and MAX_IMG_COLS. I normalized the code:
- col, width, MAX_IMG_COLS are "horizontal" variable, dimension, constant
- row, height, MAX_IMG_ROWS are "vertical" variable, dimension, constant

At the moment, the synthesizable code is functionally correct but the co-simulation stucks (there is a deadlock somewhere).
