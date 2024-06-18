@echo off
setlocal enabledelayedexpansion

set input_filename=input.txt
set output_filename=output.csv
set executable=huff_run.exe

g++ -o %executable% huff_test.cpp

if exist %output_filename% del %output_filename%

set encoded_string=
set decoded_string=

for /f "tokens=1,* delims=:" %%a in ('%executable%') do (
    if "%%a"=="Resultado de Codificar" (
        set "encoded_string=%%b"
    ) else if "%%a"=="Resultado de Descodificar" (
        set "decoded_string=%%b"
    )
)

echo !encoded_string! >> %output_filename%
echo. >> %output_filename%

for /l %%i in (1, 1, 20) do (
    for /f "tokens=1,* delims=:" %%a in ('%executable%') do (
        if "%%a"=="Tiempo de Codificar" (
            echo %%b >> %output_filename%
        )
    )
)

echo. >> %output_filename%
echo !decoded_string! >> %output_filename%
echo. >> %output_filename%

for /l %%i in (1, 1, 20) do (
    for /f "tokens=1,* delims=:" %%a in ('%executable%') do (
        if "%%a"=="Tiempo de Descodificar" (
            echo %%b >> %output_filename%
        )
    )
)

endlocal
