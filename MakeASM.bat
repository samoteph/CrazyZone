@echo off

REM Crt0
..\..\bin\lcc -c -o C:\SDK\gbz80-gb\2-1-0\lib\crt0.o .\CRT0\Crt0.s

REM Scroll
..\..\bin\lcc -c -o scroll.o .\scroll\scroll.s

REM Sprite
..\..\bin\lcc -c -o sprite.o .\sprite\sprite.s

REM SpeedUP
..\..\bin\lcc -c -o cpu.o .\SpeedUP\SpeedUP.s

REM Raster
..\..\bin\lcc -c -o Title.o .\Logo\Title.s
