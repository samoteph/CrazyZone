@echo off

REM ..\..\bin\lcc -Wa-l -Wl-m -Wl-yt2 -Wl-yo4 -o crazy.gb main.c scroll.o Rom1.o Rom2.o SpeedUP.o sprite.o

c:\sdk\gbz80-gb\2-1-0\bin\lcc -Wl-m -Wl-yt2 -Wl-yo8 -o crazy.gb main.c scroll.o rom.o Title.o cpu.o sprite.o asm.o R1.o R2.o R3.o R4.o
rbank crazy.gb 5 ghxbank.gb
rgbfix95.exe -p -r -v crazy.gb
