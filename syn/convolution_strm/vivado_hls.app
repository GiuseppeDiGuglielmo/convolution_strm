<project xmlns="com.autoesl.autopilot.project" name="convolution_strm" top="convolution_strm">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" clean="true" csimMode="0" lastCsimMode="0" compiler="true" compilerChoices="clang"/>
    </Simulation>
    <files xmlns="">
        <file name="../../../tb/conv_orig.cpp" sc="0" tb="1" cflags=" -I../../../inc  -I../../../tb  -DK=3"/>
        <file name="../../../tb/main.cpp" sc="0" tb="1" cflags=" -I../../../inc  -I../../../tb  -DVERBOSE -DINPUT_SIZE_SMALL -DK=3"/>
        <file name="../../../tb/utils.cpp" sc="0" tb="1" cflags=" -I../../../inc  -I../../../tb  -DK=3"/>
        <file name="../src/conv.cpp" sc="0" tb="false" cflags="-I../inc -I../tb -DK=3"/>
    </files>
    <solutions xmlns="">
        <solution name="BASIC" status="active"/>
    </solutions>
</project>

