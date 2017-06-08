############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project convolution_strm
set_top convolution_strm
add_files ../src/conv.cpp -cflags "-I../inc -I../tb -DK=3"
add_files -tb ../tb/utils.cpp -cflags "-I../inc -I../tb -DK=3"
add_files -tb ../tb/main.cpp -cflags "-I../inc -I../tb -DVERBOSE -DINPUT_SIZE_SMALL -DK=3"
add_files -tb ../tb/conv_orig.cpp -cflags "-I../inc -I../tb -DK=3"
open_solution "BASIC"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./convolution_strm/BASIC/directives.tcl"
csim_design -clean -compiler clang
csynth_design
cosim_design
export_design -format ip_catalog
