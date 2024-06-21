@echo off
setlocal enabledelayedexpansion

set input_filename=input.txt
set output_filename=output_lz.csv
set executable=LZ_run.exe
set num_experiments=20

g++ -o %executable% LZ_test.cpp

if exist %output_filename% del %output_filename%

%executable% %num_experiments% > %output_filename%

endlocal