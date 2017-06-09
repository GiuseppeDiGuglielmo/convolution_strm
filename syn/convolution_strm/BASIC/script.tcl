############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project convolution_strm
set_top top_convolution_strm
add_files ../src/conv.cpp -cflags "-I../inc -I../tb"
add_files -tb ../tb/utils.cpp -cflags "-I../inc -I../tb"
add_files -tb ../tb/main.cpp -cflags "-DVERBOSE -DINPUT_SIZE_SMALL -I../inc -I../tb"
add_files -tb ../tb/conv_orig.cpp -cflags "-I../inc -I../tb"
open_solution "BASIC"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./convolution_strm/BASIC/directives.tcl"
csim_design -clean -compiler clang
csynth_design
cosim_design -tool modelsim
export_design -rtl verilog -format ip_catalog
