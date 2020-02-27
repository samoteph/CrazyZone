; ****************************************
; * SpeedUP : Change la Frequence du Z80 * 
; ****************************************

	.include	"C:\SDK\gbz80-gb\2-1-0\lib\global.s"

	.globl	_SpeedUp

; *************************************************************************
; BSS
; *************************************************************************

	.area	_BSS

; *************************************************************************
; Code
; *************************************************************************

	.area	_CODE

; *************************************************************************
; Speed Up
; *************************************************************************

_SpeedUp::

	DI
	LDH		A,(.IE)
	PUSH	AF
	LDH		A,(.IF)
	PUSH	AF
	
	XOR		A,A
	LDH		(.IE),A	; Disable IT
	LDH		(.IF),A
	LD		A,#0x30	; declenche le double Speed
	LDH		(.P1),A
	LD		A,#1
	LDH		(.KEY1),A
	STOP

	POP		AF
	LDH		(.IF),A	
	POP		AF
	LDH		(.IE),A
	EI
	
	RET		

