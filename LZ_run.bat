@echo off
setlocal enabledelayedexpansion

set input_filename=input.txt
set output_filename=output_lz.txt
set executable=LZ_run.exe

g++ -o %executable% LZ_test.cpp

if exist %output_filename% del %output_filename%

set encoded_string=
set decoded_string=

:: Ejecutar el programa una vez para capturar los resultados iniciales
for /f "tokens=1,* delims=:" %%a in ('%executable%') do (
    if "%%a"=="Resultado de Codificar" (
        set "encoded_string=%%b"
    ) else if "%%a"=="Resultado de Descodificar" (
        set "decoded_string=%%b"
    )
)

:: Guardar el resultado de la compresión
echo Resultado de Codificar: !encoded_string! >> %output_filename%
echo. >> %output_filename%

:: Ejecutar el programa 20 veces para la compresión y capturar los tiempos
for /l %%i in (1, 1, 20) do (
    for /f "tokens=1,* delims=:" %%a in ('%executable%') do (
        if "%%a"=="Tiempo de Codificar" (
            echo %%b >> %output_filename%
        )
    )
)

:: Guardar el resultado de la descompresión
echo. >> %output_filename%
echo Resultado de Descodificar: !decoded_string! >> %output_filename%
echo. >> %output_filename%

:: Ejecutar el programa 20 veces para la descompresión y capturar los tiempos
for /l %%i in (1, 1, 20) do (
    for /f "tokens=1,* delims=:" %%a in ('%executable%') do (
        if "%%a"=="Tiempo de Descodificar" (
            echo %%b >> %output_filename%
        )
    )
)

endlocal
