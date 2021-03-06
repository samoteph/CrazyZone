/************************************************************/
/*															*/ 
/* Scrolling !!!											*/
/*															*/ 
/************************************************************/

#include ".\Scroll\Level1\MapLevel1.h"

/************************************************************/
/* Prototype												*/
/************************************************************/

void Init_Scroll(UBYTE);
void Set_Bkg_MapAttribut(UWORD uwWidth,UWORD uwHeight,unsigned char *ptrMap,UBYTE *PtrScreen);

// ASM
extern void Draw_Map(UBYTE,UBYTE *);
extern void VBL_Level1();
extern void HBL_Level1();

extern void VBL_Level2();
extern void HBL_Level2();

/************************************************************/
/* Extern													*/
/************************************************************/

// ASM
extern	UBYTE ScrollRaster1;
extern	UBYTE CounterVBL;
extern	UBYTE ScrollScreen;
extern	unsigned char *ScrollMap;
extern	UBYTE StartScroll;

// ROM
extern	UWORD PtrTileLevel1CGBPal[];
extern unsigned char PtrTileLevel1[];

extern void FixHBL(ptrFunction);
extern void FixVBL(ptrFunction);
