/************************************************************/
/*								 
/* Virtual Explosion !!!						
/*								 
/************************************************************/

#ifndef __VBOOM
#define __VBOOM

#include ".\sprite\Level1\Boom\VBoom.h"

/************************************************************/
/* Init_VBoom						
/* Initialise Monster Virtuel
/************************************************************/

void Init_VBoom()
{
	set_sprite_data(DATA_OFFSET_BOOM,DATA_WIDTH_BOOM,PtrBoom);
}

/************************************************************/
/* Init_VStar						
/* Initialise Star Virtuel
/************************************************************/

void Init_VStar(structVSprite *ptrVInfo)
{
	// plus de test de collision qd monster = 0x80
	ptrVInfo->ubCollision=0x80;
	
	set_sprite_tile(ptrVInfo->ubOffsetSprite[0],DATA_OFFSET_BOOM);
	set_sprite_prop(ptrVInfo->ubOffsetSprite[0],PAL0);	
	set_sprite_tile(ptrVInfo->ubOffsetSprite[1],DATA_OFFSET_BOOM);
	set_sprite_prop(ptrVInfo->ubOffsetSprite[1],PAL0);	
	set_sprite_tile(ptrVInfo->ubOffsetSprite[2],DATA_OFFSET_BOOM);
	set_sprite_prop(ptrVInfo->ubOffsetSprite[2],PAL0);	
	set_sprite_tile(ptrVInfo->ubOffsetSprite[3],DATA_OFFSET_BOOM);
	set_sprite_prop(ptrVInfo->ubOffsetSprite[3],PAL0);	
	
	ptrVInfo->ubData[0]=8;
	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VStar;

	Run_VStar(ptrVInfo);
}

/************************************************************/
/* Run_VStar()
/* Run Star Virtuel
/************************************************************/

void Run_VStar(structVSprite *ptrVInfo)
{
	if(ptrVInfo->ubData[0]==20)
	{
		ptrVInfo->ubNbrSprite=0;

		TabMonster[ptrVInfo->ubOffsetSprite[0]-SPRITE_OFFSET_MONSTER]=0x00;
		TabMonster[ptrVInfo->ubOffsetSprite[1]-SPRITE_OFFSET_MONSTER]=0x00;
		TabMonster[ptrVInfo->ubOffsetSprite[2]-SPRITE_OFFSET_MONSTER]=0x00;
		TabMonster[ptrVInfo->ubOffsetSprite[3]-SPRITE_OFFSET_MONSTER]=0x00;

		move_sprite(ptrVInfo->ubOffsetSprite[0],0,0);
		move_sprite(ptrVInfo->ubOffsetSprite[1],0,0);
		move_sprite(ptrVInfo->ubOffsetSprite[2],0,0);
		move_sprite(ptrVInfo->ubOffsetSprite[3],0,0);
	}
	else
	{		
		move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY);
		move_sprite(ptrVInfo->ubOffsetSprite[1],ptrVInfo->ubPosX+ptrVInfo->ubData[0],ptrVInfo->ubPosY);
		move_sprite(ptrVInfo->ubOffsetSprite[2],ptrVInfo->ubPosX,ptrVInfo->ubPosY+ptrVInfo->ubData[0]);
		move_sprite(ptrVInfo->ubOffsetSprite[3],ptrVInfo->ubPosX+ptrVInfo->ubData[0],ptrVInfo->ubPosY+ptrVInfo->ubData[0]);	

		ptrVInfo->ubPosX--;
		ptrVInfo->ubPosY--;
		ptrVInfo->ubData[0]+=2;
	}
}

/************************************************************/
/* Init_VExplodeOpa						
/* Initialise explosion de opa
/************************************************************/

void Init_VExplodeOpa()
{
	// 0xFF = Indique � VRunOpa qu'il explose et qu'il doit executer ExplodeOpa
	VOpa.ubCollision=0xFF;
	
	// Charge le dessin de la destruction

	set_sprite_tile(SPRITE_OFFSET_OPA+0,DATA_OFFSET_BOOM);
	set_sprite_prop(SPRITE_OFFSET_OPA+0,PAL0);	
	set_sprite_tile(SPRITE_OFFSET_OPA+1,DATA_OFFSET_BOOM);
	set_sprite_prop(SPRITE_OFFSET_OPA+1,PAL1);	
	set_sprite_tile(SPRITE_OFFSET_OPA+2,DATA_OFFSET_BOOM);
	set_sprite_prop(SPRITE_OFFSET_OPA+2,PAL2);	
	set_sprite_tile(SPRITE_OFFSET_OPA+3,DATA_OFFSET_BOOM);
	set_sprite_prop(SPRITE_OFFSET_OPA+3,PAL3);	
	
	// Donne de l'explosion
	VOpa.ubData[0]=8;
}

/************************************************************/
/* Run_VExplodeOpa
/* Destruction de opa et appel � la routine de fin de vie
/************************************************************/

void Run_VExplodeOpa(structVSprite *ptrVInfo)
{
	UBYTE ubData;

	if(ptrVInfo->ubData[0]>200)
	{
		Dec_Life_VOpa();
		return;
	}

	if(ptrVInfo->ubData[0]>49)
	{
		move_sprite(SPRITE_OFFSET_OPA+0,0,0);
		move_sprite(SPRITE_OFFSET_OPA+1,0,0);
		move_sprite(SPRITE_OFFSET_OPA+2,0,0);
		move_sprite(SPRITE_OFFSET_OPA+3,0,0);		
	}
	else
	{		
		// efface le moteur (+ simple de le mettre ici)
		move_sprite(SPRITE_OFFSET_ENGINE,0,0);

		move_sprite(SPRITE_OFFSET_OPA+0,VOpa.ubPosX,VOpa.ubPosY);
		move_sprite(SPRITE_OFFSET_OPA+1,VOpa.ubPosX+VOpa.ubData[0],VOpa.ubPosY);
		move_sprite(SPRITE_OFFSET_OPA+2,VOpa.ubPosX,VOpa.ubPosY+VOpa.ubData[0]);
		move_sprite(SPRITE_OFFSET_OPA+3,VOpa.ubPosX+VOpa.ubData[0],VOpa.ubPosY+VOpa.ubData[0]);	

		VOpa.ubPosX--;
		VOpa.ubPosY--;
	}

	VOpa.ubData[0]+=2;
}

#endif

