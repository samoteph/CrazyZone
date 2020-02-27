; *************************************************************************
; *
; * Declaration des Variables Globales 
; *
; *************************************************************************

; *************************************************************************
; * Define								  
; *************************************************************************

ScrollWidth		=	(304+1)*2
NUM_MOUNTAIN		=	2
NUM_FLOCON		=	0

NUM_DIME		=	28
NUM_SATAN		=	12

; *************************************************************************
; * Include								  
; *************************************************************************

	.include	"C:\SDK\gbz80-gb\2-1-0\lib\global.s"

; *************************************************************************
; * Global								  
; *************************************************************************

	.globl	_Draw_Map

	.globl	.vbl

	.globl	.int_0x40
	.globl	.int_0x48
	.globl	_HBL_Level1
	.globl	_VBL_Level1

	.globl	_VBL_Level2
	.globl	_HBL_Level2

	.globl	_FixHBL
	.globl	_FixVBL

	; ** Compteur par VBL **
	.globl	_CounterVBL

	; ** Raster **
	.globl	_ScrollRaster1	

	.globl	_PtrMapLevel1
	.globl	_ScrollScreen
	.globl	_ScrollMap

	.globl	_StartScroll

	; Animation

	.globl	_DimeDataLevel1
	.globl	_MountainDataLevel1

	.globl	_PtrDimeDataLevel1
	.globl	_PtrMountainDataLevel1

	.AREA	_DATA

; Ptr de l'animation en cours selon level

; *************************************************************************
; * BSS								  
; *************************************************************************

	.area	_BSS

; Offset de l'animation du Level 1
OffsetDimeDataLevel1:		.ds	1
OffsetMountainDataLevel1:	.ds	1

; emplacement des scrolls en pixels
_ScrollRaster1:		.ds		1

; Compteur VBL
_CounterVBL:		.ds		1

; Pointeur sur l'ecran � afficher (poids faible)
_ScrollScreen:			.ds		1
; Pointeur sur la Map � afficher
_ScrollMap:		.ds		2

; Demarrage du scroll si 1
_StartScroll:		.ds		1

; *************************************************************************
; * Code								  
; *************************************************************************

	.area	_CODE
	

; *************************************************************************
; * FixHBL
; * HBL (crt0.s) 
; *************************************************************************

_FixHBL::

	LD	HL,#.int_0x48
	LD	(HL),E
	INC	L
	LD	(HL),D
	
	RET

; *************************************************************************
; * FixVBL
; * VL (crt0.s) 
; *************************************************************************

_FixVBL::

	LD	HL,#.int_0x40
	LD	(HL),E
	INC	L
	LD	(HL),D
	
	RET

; *************************************************************************
; * _anHBL
; * HBL (crt0.s) 
; *************************************************************************

_anHBL::

	PUSH	AF
	PUSH	BC
	PUSH	DE
	PUSH	HL

	LD	DE,#.int_0x48
	LD	A,(DE)
	LD	L,A
	INC	E
	LD	A,(DE)
	LD	H,A

	JP	(HL)

; *************************************************************************
; * _anVBL
; * VBL (crt0.s) 
; *************************************************************************

_anVBL::

	PUSH	AF
	PUSH	BC
	PUSH	DE
	PUSH	HL

	CALL	.vbl

	LD	DE,#.int_0x40
	LD	A,(DE)
	LD	L,A
	OR	A
	JR	Z,.Jump

	INC	E
	LD	A,(DE)
	LD	H,A

	JP	(HL)

.Jump:
	INC	E
	LD	A,(DE)
	LD	H,A

	OR	A
	JR	Z,.NoVBL

	JP	(HL)

.NoVBL:
	POP	HL
	POP	DE
	POP	BC
	POP	AF
	
	RETI

; *************************************************************************
; * _HBL_Level1
; * hbl du level1 : raster , scroll...
; *************************************************************************

_HBL_Level1::

; HBL en Cours = HBL + 4
	LDH		A,(.LYC)
	CP		A,#14*8-1
	JR		Z,.StopRaster
	ADD		A,#4
	LDH		(.LYC),A

; attente du bus
9$:
	LDH		A,(0x41)
	AND		#2		
	JR		NZ,9$

	LD		DE,#0xFF00+.BCPS
	LD		HL,#0xFF00+.BCPD

	; obtenir + fixe la couleur 0 de la palette 2
	LD		A,#0b00010000
	LD		(DE),A
	LD		C,(HL)
	INC		C
	LD		(HL),C	
	
	; fixe la couleur 0 de la palette 3
	LD		A,#0b00011000
	LD		(DE),A
	LD		(HL),C	

	; fixe la couleur 0 de la palette 6
	LD		A,#0b00110000
	LD		(DE),A
	LD		(HL),C	

.StopRaster:

	POP	HL
	POP	DE
	POP	BC
	POP	AF
	
	RETI
	
; *************************************************************************
; * _VBL_Level1:
; * VBL du Scroll de niveau 1
; *************************************************************************

_VBL_Level1:
	
	; ** Fixe le 1er Scroll **

	; Charge le scroll en cours
	LD		HL,#_ScrollRaster1
	LD		C,(HL)

	; Vitesse du Scroll du haut
	LD		DE,#_CounterVBL
	LD		A,(DE)
	INC		A
	LD		(DE),A

	LD		B,A

	LD		DE,#_StartScroll
	LD		A,(DE)
	CP		A,#0
	JP		Z,.NoScroll

	LD		A,B

	; Scroll tout les 4 VBLs
	AND		#0x03
	JR		NZ,$1

	; Avance le Scroll
	INC		C
$1:
	LD		A,C
	; Fixe le Scroll
	LDH		(.SCX),A
	; puis sauvegarde
	LD		(HL),C
	
	; ** Scrolling **

	; Counter_VBL = multiple de 4 * 8
	LD		DE,#_CounterVBL
	LD		A,(DE)
	AND		#0x1F
	JR		NZ,.NoScroll
	
	CALL		Draw_Complete_Line_Scroll

.NoScroll:

	; ** Animation et scroll differentiel par GDMA **

	; ** Animation : Dime

	LD		DE,#_CounterVBL
	LD		A,(DE)
	AND		#0x07
	JR		NZ,.NoDime
	
	LD		HL,#_PtrDimeDataLevel1
	LD		A,(OffsetDimeDataLevel1)
	ADD		A,#2
	AND		#0x07
	LD		(OffsetDimeDataLevel1),A
	ADD		A,L		
	LD		L,A

	LD		A,(HLI)
	LD		C,A
	LD		B,(HL)
 
	LD		A,B
	LDH		(.HDMA1),A
	LD		A,C
	LDH		(.HDMA2),A
	LD		A,#0x90+(NUM_DIME>>0x04)
	LDH		(.HDMA3),A
	LD		A,#(NUM_DIME<<0x04)
	LDH		(.HDMA4),A

	LD		A,#0x03
	LDH		(.HDMA5),A

.NoDime:

	; ** Animation : Mountain

	LD		DE,#_CounterVBL
	LD		A,(DE)
	AND		#0x07
	JR		NZ,.NoMountain
	
	LD		HL,#_PtrMountainDataLevel1
	LD		A,(OffsetMountainDataLevel1)
	ADD		A,#2
	AND		#0x1F
	LD		(OffsetMountainDataLevel1),A
	ADD		A,L		
	LD		L,A

	LD		A,(HLI)
	LD		C,A
	LD		B,(HL)
 
	LD		A,B
	LDH		(.HDMA1),A
	LD		A,C
	LDH		(.HDMA2),A
	LD		A,#0x90+(NUM_MOUNTAIN>>0x04)
	LDH		(.HDMA3),A
	LD		A,#(NUM_MOUNTAIN<<0x04)
	LDH		(.HDMA4),A

	LD		A,#0x01
	LDH		(.HDMA5),A

.NoMountain:

	; ** Fixe les Rasters et autres **

	; fixe le debut du raster
	LD		A,#4*8-1
	LDH		(.LYC),A

	; fixe la couleur 0 de la palette 2
	LD		A,#0b00010000
	LDH		(.BCPS),A

	; met la couleur � 0
	XOR		A,A
	LDH		(.BCPD),A

	; fixe la couleur 0 de la palette 3
	LD		A,#0b00011000
	LDH		(.BCPS),A

	; met la couleur � 0
	XOR		A,A
	LDH		(.BCPD),A

	; fixe la couleur 0 de la palette 6
	LD		A,#0b00110000
	LDH		(.BCPS),A

	; met la couleur � 0
	XOR		A,A
	LDH		(.BCPD),A

	POP	HL
	POP	DE
	POP	BC
	POP	AF
	
	RETI
	
; *************************************************************************
; * _VBL_Level2:
; * VBL du Scroll de niveau 2
; *************************************************************************

_VBL_Level2:
	
	; ** Fixe le 1er Scroll **

	; Charge le scroll en cours
	LD		HL,#_ScrollRaster1
	LD		C,(HL)

	; Vitesse du Scroll du haut
	LD		DE,#_CounterVBL
	LD		A,(DE)
	INC		A
	LD		(DE),A

	LD		B,A

	LD		DE,#_StartScroll
	LD		A,(DE)
	CP		A,#0
	JP		Z,.NoScroll2

	LD		A,B

	; Scroll tout les 4 VBLs
	AND		#0x03
	JR		NZ,$11

	; Avance le Scroll
	INC		C
$11:
	LD		A,C
	; Fixe le Scroll
	LDH		(.SCX),A
	; puis sauvegarde
	LD		(HL),C
	

	; ** Scrolling **

	; Counter_VBL = multiple de 4 * 8
	LD		DE,#_CounterVBL
	LD		A,(DE)
	AND		#0x1F
	JR		NZ,.NoScroll2
	
	CALL		Draw_Complete_Line_Scroll

.NoScroll2:

	; ** Animation et scroll differentiel par GDMA **

	; ** Animation : Dime

	LD		DE,#_CounterVBL
	LD		A,(DE)
	AND		#0x07
	JR		NZ,.NoDime2
	
	LD		HL,#_PtrDimeDataLevel1
	LD		A,(OffsetDimeDataLevel1)
	ADD		A,#2
	AND		#0x07
	LD		(OffsetDimeDataLevel1),A
	ADD		A,L		
	LD		L,A

	LD		A,(HLI)
	LD		C,A
	LD		B,(HL)
 
	LD		A,B
	LDH		(.HDMA1),A
	LD		A,C
	LDH		(.HDMA2),A
	LD		A,#0x90+(NUM_DIME>>0x04)
	LDH		(.HDMA3),A
	LD		A,#(NUM_DIME<<0x04)
	LDH		(.HDMA4),A

	LD		A,#0x03
	LDH		(.HDMA5),A

.NoDime2:

	; ** Animation : Snow

	LD		DE,#_CounterVBL
	LD		A,(DE)
	AND		#0x07
	JR		NZ,.NoSnow
	
	LD		HL,#_PtrMountainDataLevel1
	LD		A,(OffsetMountainDataLevel1)
	ADD		A,#2
	AND		#0x1F
	LD		(OffsetMountainDataLevel1),A
	ADD		A,L		
	LD		L,A

	LD		A,(HLI)
	LD		C,A
	LD		B,(HL)
 
	LD		A,B
	LDH		(.HDMA1),A
	LD		A,C
	LDH		(.HDMA2),A
	LD		A,#0x90+(NUM_FLOCON>>0x04)
	LDH		(.HDMA3),A
	LD		A,#(NUM_FLOCON<<0x04)
	LDH		(.HDMA4),A

	LD		A,#0x01
	LDH		(.HDMA5),A

.NoSnow:

	; ** Fixe les Rasters et autres **

	; fixe le debut du raster
	LD		A,#4*8
	LDH		(.LYC),A

	; fixe la couleur 0 de la palette 0
	LD		A,#0b00000000
	LDH		(.BCPS),A

	; met la couleur � 0
	XOR		A,A
	LDH		(.BCPD),A

	; fixe la couleur 0 de la palette 5
	LD		A,#0b00101000
	LDH		(.BCPS),A

	; met la couleur � 0
	XOR		A,A
	LDH		(.BCPD),A

	; fixe la couleur 0 de la palette 6
	LD		A,#0b00110000
	LDH		(.BCPS),A

	; met la couleur � 0
	XOR		A,A
	LDH		(.BCPD),A

	POP	HL
	POP	DE
	POP	BC
	POP	AF
	
	RETI

; *************************************************************************
; * _HBL_Level2
; * hbl du level2 : raster , scroll...
; *************************************************************************

_HBL_Level2::

; HBL en Cours = HBL + 8
	LDH		A,(.LYC)
	CP		A,#17*8
	JR		Z,.StopRaster2
	ADD		A,#8
	LDH		(.LYC),A

; attente du bus
19$:
	LDH		A,(0x41)
	AND		#2		
	JR		NZ,19$

	LD		DE,#0xFF00+.BCPS
	LD		HL,#0xFF00+.BCPD

	; obtenir + fixe la couleur 0 de la palette 0
	LD		A,#0b00000000
	LD		(DE),A
	LD		C,(HL)
	INC		C
	INC		C
	LD		(HL),C	
	
	; fixe la couleur 0 de la palette 5
	LD		A,#0b00101000
	LD		(DE),A
	LD		(HL),C	

	; fixe la couleur 0 de la palette 6
	LD		A,#0b00110000
	LD		(DE),A
	LD		(HL),C	

.StopRaster2:

	POP	HL
	POP	DE
	POP	BC
	POP	AF
	
	RETI

; *************************************************************************
; * Draw_Line_Scroll
; * Dessine une ligne de scroll (attribut | character)
; *	HL=Map
; *	DE=Ecran
; * ScrollWidth = longeur de la Map * 2 
; *************************************************************************

Draw_Line_Scroll:

	; Adresse en 0x98??	

	; Map
	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	; Affichage
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	; Passage � 0x99??
	LD		D,#0x99
	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

	; Passage � 0x9A??
	LD		D,#0x9A
	LD		A,(HL)
	LD		BC,#ScrollWidth
	ADD		HL,BC
	LD		(DE),A
	LD		A,E
	ADD		A,#0x20
	LD		E,A

;	LD		A,(HL)
;	LD		(DE),A

	RET
	
; *************************************************************************
; * Draw_Complete_Line_Scroll
; * Dessine une ligne de scroll complete (attribut & character)
; *************************************************************************

Draw_Complete_Line_Scroll:

	; ** Pointeur Ecran dans DE **
	LD		HL,#_ScrollScreen
	; poids faible
	LD		A,(HL)
	LD		E,A
	; Ajoute 1 � l'adresse Courante de l'ecran (9800 -> 981F)
	INC		A
	; @ multiple de 32
	AND		#0x1F
	; puis sauvegarde le poids faible
	LD		(HL),A
	; poids fort :
	LD		D,#0x98

	; ** Pointeur sur map � afficher dans HL **
	LD		HL,#_ScrollMap
	; poids faible 
	LD		A,(HLI)
	LD		C,A
	LD		B,(HL)
	; Ajoute 2 � l'adresse Courante du Map (pour passer les attributs)
	INC		BC
	INC		BC
	; Sauvegarde _ScrollMap
	LD		A,B
	LD		(HLD),A
	LD		(HL),C
	LD		H,B
	LD		L,C
	
	; Chargement des Attributs (VBK=1)
	LD		A,#1
	LDH		(.VBK),A
		
	PUSH	DE		; puis sauvegarde
	PUSH	HL
	CALL	Draw_Line_Scroll

	; Chargement des Map (VBK=0)
	XOR		A,A
	LDH		(.VBK),A

	POP		HL
	POP		DE
	INC		HL
	CALL	Draw_Line_Scroll
	
	RET
	
; *************************************************************************
; * Draw_Map
; * Dessine un Map � l'ecran (n'importe quand)
; *************************************************************************

_Draw_Map::

	;DE=UBYTE *ptrScreen
	;A=Data

	LD		C,A

1$:
	LDH		A,(0x41)
	AND		#2		
	JR		NZ,1$

	LD		A,C
	LD		(DE),A

	RET
