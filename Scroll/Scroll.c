/************************************************************/
/*															*/ 
/* Scrolling !!!											*/
/*															*/ 
/************************************************************/

#ifndef	__SCROLL
#define __SCROLL

#include ".\scroll\scroll.h"

/************************************************************/
/* Init_Scroll												*/ 
/* Initialise le scrolling couleur : Charge les couleurs,	*/
/* affiche les tiles...										*/
/************************************************************/

void Init_Scroll(UBYTE start)
{
	SWITCH_ROM_MBC1(ubLevelRom);

	// Met en place les tiles
	set_bkg_data(0,127,PtrTileLevel1);

	// Met en place la map + attribut
	Set_Bkg_MapAttribut(PtrMapLevel1Width,PtrMapLevel1Height,PtrMapLevel1,(UBYTE *)0x9800);

	// initialise les info du scroll
	ScrollRaster1=8;
	CounterVBL=0;
	// Offset de l'ecran
	ScrollScreen=31;
	// MapLevel1 contient aussi les couleurs donc (31-1)*2=60
	ScrollMap=(unsigned char *)(PtrMapLevel1+60);

	// Demarrage du Scroll
	StartScroll=1;

	if(start==START)
	{
		set_bkg_palette(0,8,&PtrTileLevel1CGBPal[0]);	
	}

	FixVBL(ubLevelVBL);
	FixHBL(ubLevelHBL);
}

void Stop_Scroll()
{
	// Plus D'interruption
	set_interrupts(0);
}

/************************************************************/
/* Set_Bkg_MapAttribut										*/ 
/* Charge les couleurs,et les Map en 0x9800	32*18 tiles		*/
/************************************************************/

void Set_Bkg_MapAttribut(UWORD uwWidth,UWORD uwHeight,unsigned char *ptrMap,UBYTE *ptrScreen)
{
	UWORD x,y;
	UWORD v,w;	
	UWORD a;	
	UBYTE n;

	for(x=0;x<32;x++)
	{
		// VRAM en mode Attributs
		VBK_REG=1;

		// initialise les variables
		a=0;
		w=(x<<1);
		
		// les map verticaux
		for(y=0;y<18;y++)
		{
			v=x+(y<<5);
			n=*(ptrMap+w+a);

			// Affiche les maps
			Draw_Map(n,ptrScreen+v);

			a+=(uwWidth<<1);
		}

		// VRAM en mode Map
		VBK_REG=0;
		
		// initialise les variables
		a=0;
		w+=1;
		
		for(y=0;y<18;y++)
		{
			v=x+(y<<5);
			n=*(ptrMap+w+a);
			Draw_Map(n,ptrScreen+v);
			a+=(uwWidth<<1);
		}
	}	
}

#endif

