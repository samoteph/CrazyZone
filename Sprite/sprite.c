/************************************************************/
/*															*/ 
/* Sprite !!!												*/
/*															*/ 
/************************************************************/

#ifndef	__SPRITE
#define __SPRITE

#include ".\sprite\sprite.h"
#include ".\sprite\Level1\opa\vopa.c"

/************************************************************/
/* Init_Sprite												*/ 
/* Initialise les sprite couleur : Charge les couleurs...	*/
/************************************************************/

void Init_Sprite(void)
{
	UBYTE y;

	// met en place la palette sprite
	set_sprite_palette(0,8,&PtrOpaCGBPal[0]);
}

/************************************************************/
/* Run_VCollision					    */ 
/* Verifie les collisions entre VSprite et VMonster	    */ 
/************************************************************/

BYTE Run_VCollision(structVSprite *ptrVInfo)
{
	UBYTE ubNextVSprite=0;
	UBYTE ubX,ubY,ubW,ubH;
	UBYTE ubXMonster,ubYMonster,ubWMonster,ubHMonster;
	BYTE bCollision=0;
	
	structVSprite *ptrVMonster=TabVMonster;
	
	ubX=ptrVInfo->ubPosX+ptrVInfo->ubRectX;
	ubY=ptrVInfo->ubPosY+ptrVInfo->ubRectY;
	ubW=ptrVInfo->ubRectW;
	ubH=ptrVInfo->ubRectH;

	// Parcours la liste des monstres

	while(ubNextVSprite<MAX_VMONSTER)
	{
		if(ptrVMonster->ubNbrSprite!=0x0 && ptrVMonster->ubCollision!=0x80)
		{
			ubXMonster=ptrVMonster->ubPosX+ptrVMonster->ubRectX;
			ubYMonster=ptrVMonster->ubPosY+ptrVMonster->ubRectY;

			// Collision en X
			if(ubX<ubXMonster)			
			{
				if(ubW>(ubXMonster-ubX))
				{					
					// Collision en Y
					if(ubY<ubYMonster)			
					{
						if(ubH>(ubYMonster-ubY))
						{
							// data 0 = Power Weapon
							ptrVMonster->ubCollision+=ptrVInfo->ubData[0];
							ptrVInfo->ubCollision=0x80;
							bCollision=-1;
						}
					}
					else
					{
						if(ubH>(ubY-ubYMonster))
						{
							ptrVMonster->ubCollision+=ptrVInfo->ubData[0];
							ptrVInfo->ubCollision=0x80;
							bCollision=-1;
						}				
					}
				}
			}
			else
			{
				if(ubW>(ubX-ubXMonster))
				{
					// Collision en Y
					if(ubY<ubYMonster)			
					{
						if(ubH>(ubYMonster-ubY))
						{
							ptrVMonster->ubCollision+=ptrVInfo->ubData[0];
							ptrVInfo->ubCollision=0x80;
							bCollision=-1;
						}
					}
					else
					{
						if(ubH>(ubY-ubYMonster))
						{
							ptrVMonster->ubCollision+=ptrVInfo->ubData[0];
							ptrVInfo->ubCollision=0x80;
							bCollision=-1;
						}				
					}
				}				
			}		
		}

		ubNextVSprite++;
		ptrVMonster++;
	}

	return bCollision;

}

#endif

