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

	.globl	_HBL_Title
	.globl	_VBL_Title
	
	.AREA	_DATA

; Ptr de l'animation en cours selon level

; *************************************************************************
; * BSS								  
; *************************************************************************

	.area	_BSS

_Raster1:	.ds	1
_Raster2:	.ds	1
_Raster3:	.ds	1

_CounterRaster:	.ds	1

; *************************************************************************
; * Code								  
; *************************************************************************

	.area	_CODE
	
; *************************************************************************
; * _HBL_Title
; * hbl du Titre : raster 
; *************************************************************************

_HBL_Title::

; HBL en Cours = HBL + 1
	LDH		A,(.LYC)
	LD		E,A

	LD		A,E
	CP		A,#18*8
	JR		Z,.NoRaster

	INC		A
	LDH		(.LYC),A

.NoRaster:
	
	LD		A,(_CounterRaster)
	LD		D,A

; attente du bus
9$:
	LDH		A,(0x41)
	AND		#2		
	JR		NZ,9$

	; *****************************

	LD		A,E

	CP		A,#5*8-1
	JR		NZ,$70

	; fixe la couleur 0 de la palette 2
	LD		A,#0b10000000
	LDH		(.BCPS),A

	; met la couleur � 0
	LD		A,#0xC6
	LDH		(.BCPD),A

	LD		A,#0x7C
	LDH		(.BCPD),A

$70:

	; *****************************

	LD		A,E

	CP		A,#7*8-1
	JR		NZ,$71

	; fixe la couleur 0 de la palette 2
	LD		A,#0b10000000
	LDH		(.BCPS),A

	; met la couleur � 0
	LD		A,#0xAD
	LDH		(.BCPD),A

	LD		A,#0x7D
	LDH		(.BCPD),A

$71:

	; *****************************

	LD		A,E

	CP		A,#8*8-1
	JR		NZ,$72

	; fixe la couleur 0 de la palette 2
	LD		A,#0b10000000
	LDH		(.BCPS),A

	; met la couleur � 0
	LD		A,#0x94
	LDH		(.BCPD),A

	LD		A,#0x7E
	LDH		(.BCPD),A

$72:

	; *****************************

	LD		A,E

	CP		A,#9*8-1
	JR		NZ,$73

	; fixe la couleur 0 de la palette 2
	LD		A,#0b10000000
	LDH		(.BCPS),A

	; met la couleur � 0
	LD		A,#0x7B
	LDH		(.BCPD),A

	LD		A,#0x7F
	LDH		(.BCPD),A

$73:

	; *****************************

	LD		A,E
	CP		A,#9*8
	JR		NZ,$80

	; Lit le Scroll
	LD		A,(_Raster1)
	LD		C,A

	LD		A,D
	AND		#0x03
	JR		NZ,$81

	; Scroll
	INC		C
	LD		A,C
	LD		(_Raster1),A

$81:
	LD		A,C
	LDH		(.SCX),A

$80:
	; *****************************

	LD		A,E
	CP		A,#10*8-5
	JR		NZ,$90

	; fixe la couleur 0 de la palette 2
	LD		A,#0b10000000
	LDH		(.BCPS),A

	; met la couleur � 0
	LD		A,#0x14
	LDH		(.BCPD),A

	LD		A,#0x22
	LDH		(.BCPD),A

	; met la couleur � 1
	LD		A,#0x90
	LDH		(.BCPD),A

	LD		A,#0x11
	LDH		(.BCPD),A

	; met la couleur 2
	LD		A,#0x88
	LDH		(.BCPD),A

	LD		A,#0x10
	LDH		(.BCPD),A

$90:
	; *****************************

	LD		A,E
	CP		A,#11*8-2
	JR		NZ,$100

	; Lit le Scroll
	LD		A,(_Raster2)
	LD		C,A

	LD		A,D
	AND		#0x01
	JR		NZ,$101

	; Scroll
	INC		C
	LD		A,C
	LD		(_Raster2),A

$101:
	LD		A,C
	LDH		(.SCX),A

$100:
	; ***********************

	LD		A,E
	CP		A,#14*8-4
	JR		NZ,$110

	; Lit le Scroll
	LD		A,(_Raster3)
	LD		C,A

	LD		A,D
	AND		#0x00
	JR		NZ,$111

	; Scroll
	INC		C
	LD		A,C
	LD		(_Raster3),A

$111:
	LD		A,C
	LDH		(.SCX),A

$110:
	; ***********************

	POP	HL
	POP	DE
	POP	BC
	POP	AF
	
	RETI
	
; *************************************************************************
; * _VBL_Title:
; * VBL du Scroll de niveau 1
; *************************************************************************

_VBL_Title:
	
	LD		A,#0
	LDH		(.SCX),A
	
	; fixe le debut du raster
	LD		A,#1
	LDH		(.LYC),A

	; fixe la couleur 0 de la palette 2
	LD		A,#0b10000000
	LDH		(.BCPS),A

	; met la couleur 0
	LD		A,#0
	LDH		(.BCPD),A

	LD		A,#0x7C
	LDH		(.BCPD),A

	; met la couleur 1
	LD		A,#0xFF
	LDH		(.BCPD),A

	LD		A,#0x7F
	LDH		(.BCPD),A

	; met la couleur 2
	LD		A,#0x1F
	LDH		(.BCPD),A

	LD		A,#0x00
	LDH		(.BCPD),A

	; Compteur
	LD		A,(_CounterRaster)
	INC		A
	LD		(_CounterRaster),A

	POP	HL
	POP	DE
	POP	BC
	POP	AF
	
	RETI
	
