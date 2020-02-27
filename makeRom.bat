@echo off

REM Rom1 : Level 1
..\..\bin\lcc -Wf-bo1 -c -o R1.o .\Rom\Rom1.c

REM Rom3 : Title
..\..\bin\lcc -Wf-bo3 -c -o R3.o .\Rom\Rom3.c

REM Rom4 : Code Monster
..\..\bin\lcc -Wf-bo4 -c -o R4.o .\Rom\Rom4.c

REM Rom5 : Level 2
..\..\bin\lcc -Wf-bo5 -c -o R5.o .\Rom\Rom5.c
