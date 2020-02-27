@echo off

REM CrazyZone

c:\sdk\gbz80-gb\2-1-0\bin\lcc -Wl-m -Wl-yt2 -Wl-yo8 -Wl-yp0x143=0x80 -o crazy.gb main.c scroll.o Title.o cpu.o sprite.o asm.o R1.o R3.o R4.o R5.o
