# Algorithm With Optimal Data Access Patterns

The source code is from the Vivado HLS User Guide *UG902 (v2017.1)*. It is under development, if you are willing to contribute I will be glad. For a complete description see UG902 pages 361-380.

## Errors

### C++ simulatiom
```
ERROR: Reference and implementation matrices do no match! (256 errors out of 256 elements)
```
### Co-simulation
```
//////////////////////////////////////////////////////////////////////////////
// ERROR!!! DEADLOCK DETECTED at 4680000 ns! SIMULATION WILL BE STOPPED! //
//////////////////////////////////////////////////////////////////////////////
/////////////////////////
// Dependence circle 1:
// (1): Process: convolution_strm.Loop_VConvH_proc_U0
//      Channel: convolution_strm.vconv_V_U, FULL
// (2): Process: convolution_strm.Loop_Border_proc_U0
//      Channel: convolution_strm.col_cast_loc_channel_U, EMPTY
////////////////////////////////////////////////////////////////////////
// Totally 1 circles detected!
////////////////////////////////////////////////////////////////////////
```
