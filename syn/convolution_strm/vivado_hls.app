<project xmlns="com.autoesl.autopilot.project" name="convolution_strm" top="convolution_strm">
    <files>
        <file name="../src/conv.cpp" sc="0" tb="false" cflags="-I../inc -I../tb"/>
        <file name="../../../tb/conv_orig.cpp" sc="0" tb="1" cflags="-I../../../inc -I../../../tb"/>
        <file name="../../../tb/main.cpp" sc="0" tb="1" cflags="-DVERBOSE -DINPUT_SIZE_SMALL -I../../../inc -I../../../tb"/>
        <file name="../../../tb/utils.cpp" sc="0" tb="1" cflags="-I../../../inc -I../../../tb"/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" clean="true" csimMode="0" lastCsimMode="0" compiler="true" compilerChoices="clang"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="BASIC" status="active"/>
    </solutions>
</project>

