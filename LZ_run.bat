@echo off
setlocal enabledelayedexpansion

set input_filename=input.txt
set output_filename=output_lz.csv
set executable=lz_run.exe
set num_experiments=31

g++ -o %executable% lz_test.cpp
if %ERRORLEVEL% NEQ 0 (
    echo Error en la compilacion.
    exit /b 1
)
if not exist %input_filename% (
    echo El archivo de entrada %input_filename% no existe.
    exit /b 1
)
if exist %output_filename% del %output_filename%
%executable% %num_experiments%
if %ERRORLEVEL% NEQ 0 (
    echo Error en la ejecucion del programa.
    exit /b 1
)

endlocal
