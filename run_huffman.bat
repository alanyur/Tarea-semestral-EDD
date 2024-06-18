@echo off
setlocal enabledelayedexpansion

set input_filename=input.txt
set output_filename=output.csv
set executable=run_huff.exe

g++ -o %executable% huff_test.cpp

if exist %output_filename% del %output_filename%

set encoded_string=
set time=

for /f "tokens=1,2" %%a in ('%executable%') do (
    set "encoded_string=%%a"
    set "time=%%b"
)

rem Escribir el string codificado en el archivo CSV
echo %encoded_string% >> %output_filename%
echo ,%time% >> %output_filename%

for /l %%i in (1, 1, 19) do (
    for /f "tokens=2" %%a in ('%executable%') do (
        echo ,%%a >> %output_filename%
    )
)

endlocal
