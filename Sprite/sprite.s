; *************************************************************************
; *
; * Declaration des Variables Globales 
; *
; *************************************************************************

; *************************************************************************
; * Define								  
; *************************************************************************

; *************************************************************************
; * Include								  
; *************************************************************************

	.include	"C:\SDK\gbz80-gb\2-1-0\lib\global.s"

; *************************************************************************
; * Global								  
; *************************************************************************

	.globl		_GetVSpriteMap
	.globl		_Set2x2VSpriteMap

; *************************************************************************
; * DATA								  
; *************************************************************************

	.AREA	_DATA

; *************************************************************************
; * BSS								  
; *************************************************************************

	.area	_BSS


; *************************************************************************
; * CODE								  
; *************************************************************************

	.area	_CODE
	
; *************************************************************************
; * _GetVSpriteMap								  
; * Obtenir un block de la Map
; *************************************************************************

_GetVSpriteMap::
	
	; A=X C=Y
	LDHL	SP,#3
	; X=E
	LD		E,A
	; X+=SCX
	LDH		A,(.SCX)
	ADD		A,E
	; X=X-8	
	SUB		A,#8
	LD		E,A

	; Y = A
	LD		A,(HL)
	; Y = Y-16
	SUB		A,#16

	; X=X/8
	SRL		E
	SRL		E
	SRL		E
	
	; Y=Y/8
	SRL		A
	SRL		A
	SRL		A
	
	; X*32
	SWAP	A
	RLC		A
	LD		C,A

	; Y=0x98+MSB of X
	AND		#0x03
	ADD		A,#0x98
	LD		H,A
	; X
	LD		A,#0xE0
	AND		C
	LD		C,A
	; Y
	LD		A,E
	ADD		A,C	
	LD		L,A

	; attente du bus
9$:
	LDH		A,(0x41)
	AND		#2		
	JR		NZ,9$

	LD		E,(HL)

	RET

; *************************************************************************
; * _Set2x2VSpriteMap								  
; * fixer un carree de 2x2 de 0 sur la Map
; * Attention l'emplacement ne peut être multiple de 32 -1 pour
; * debut de piece sinon bugs
; *************************************************************************

_Set2x2VSpriteMap::

	; A=X C=Y
	LDHL	SP,#3
	; X=E
	LD		E,A
	; X+=SCX
	LDH		A,(.SCX)
	ADD		A,E
	; X=X-8	
	SUB		A,#8
	LD		E,A

	; Y = A
	LD		A,(HL)
	; Y = Y-16
	SUB		A,#16

	; X=X/8
	SRL		E
	SRL		E
	SRL		E
	
	; Y=Y/8
	SRL		A
	SRL		A
	SRL		A
	
	; X*32
	SWAP	A
	RLC		A
	LD		C,A

	; Y=0x98+MSB of X
	AND		#0x03
	ADD		A,#0x98
	LD		H,A
	; X
	LD		A,#0xE0
	AND		C
	LD		C,A
	; Y
	LD		A,E
	ADD		A,C	
	LD		L,A

	; attente du bus
9$:
	LDH		A,(0x41)
	AND		#2		
	JR		NZ,9$

	; 1er block
	XOR		A,A
	LD		(HLI),A
	
	; 2em block
	LD		(HL),A
	
	; 3em block
	LD		BC,#32
	ADD		HL,BC
	LD		(HLD),A

	; 4em block	
	LD		(HL),A
	
	RET

