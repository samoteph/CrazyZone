/************************************************************/
/*								 
/* Virtual Weapon !!!						
/*								 
/************************************************************/

#ifndef	__VWEAPON
#define __VWEAPON

#include ".\sprite\Level1\Weapon\VWeapon.h"

/************************************************************/
/* Init_VWeapon						
/* Initialise Weapon Virtuel
/************************************************************/

void Init_VWeapon()
{
	UBYTE y;
	
	for(y=0;y<MAX_WEAPON;y++)
	{
		move_sprite(SPRITE_OFFSET_WEAPON+y,0,0);
	}

	set_sprite_data(DATA_OFFSET_WEAPON,DATA_WIDTH_WEAPON,PtrWeapon);

	for(y=0;y<MAX_VWEAPON;y++)
	{
		TabVWeapon[y].ubNbrSprite=0;
	}

	ubOffsetFindWeapon=0;

	// Arme par defaut
	Init_VTwinShot();
}

/************************************************************/
/* Run_VWeapon()
/* Run Weapon Virtuel
/************************************************************/

void Run_VWeapon()
{
	UBYTE ubPosVWeapon;
	structVSprite *ptrVWeapon=TabVWeapon;
	
	ubPosVWeapon=0;
	
	while(ubPosVWeapon<MAX_VWEAPON)
	{
		if(ptrVWeapon->ubNbrSprite!=0)
		{
			Run_VCollision(ptrVWeapon);						
			ptrVWeapon->ptrRunVSprite(ptrVWeapon);
		}
		
		ubPosVWeapon++;
		ptrVWeapon++;
	}
}

/************************************************************
 * Find_VWeapon()												
 * Trouve Weapon Virtuel disponible et renvoi un
 * un pointeur sur celui ci sinon NULL
 ************************************************************/

structVSprite *Find_VWeapon()
{
	UBYTE ubPosVWeapon=0;
	structVSprite *ptrVWeapon=TabVWeapon;
	
	while(ubPosVWeapon<MAX_VWEAPON)
	{
		// Emplacement trouvé ?
		if(ptrVWeapon->ubNbrSprite==0)
		{
			return ptrVWeapon;
		}
		ubPosVWeapon++;
		ptrVWeapon++;
	}
	return NULL;
}

/************************************************************
 * Find_Weapon()												
 * Trouve un sprites disponible
 * renvoi un offset sur celui ci
 ************************************************************/

BYTE Find_Weapon()
{
	UBYTE ubWidth=0;

	while(ubWidth<MAX_WEAPON)
	{
		ubOffsetFindWeapon++;

		if(ubOffsetFindWeapon==MAX_WEAPON)
		{
			ubOffsetFindWeapon=0;
		}

		// Emplacement trouvé ?
		if(TabWeapon[ubOffsetFindWeapon]==0)
		{	
			return ubOffsetFindWeapon;
		}
		
		ubWidth++;		
	}
	return -1;
}

/************************************************************/
/* Add_VWeapon()												
/* Ajoute Weapon Virtuel courant dans la liste
/************************************************************/

void Add_VWeapon()
{
	structVSprite *ptrVWeapon;
	BYTE ubOffset[4];
	UBYTE ubNextSprite;
	
	// ** Trouve un emplacement pour sprite Virtuel **

	ptrVWeapon=Find_VWeapon();
	if(ptrVWeapon==NULL)
	{
		return;
	}

	// ** Cherche des sprites libres **
	
	ubNextSprite=0;
	while(ubNextSprite<CurrentVWeapon.ubNbrSprite)
	{
		ubOffset[ubNextSprite]=Find_Weapon();
		if(ubOffset[ubNextSprite]==-1)
		{
			return;
		}
		
		ubNextSprite++;
	}

	// Reserve les sprites Hard
	ubNextSprite=0;
	
	while(ubNextSprite<CurrentVWeapon.ubNbrSprite)
	{
		ptrVWeapon->ubOffsetSprite[ubNextSprite]=ubOffset[ubNextSprite]+SPRITE_OFFSET_WEAPON;
		TabWeapon[ubOffset[ubNextSprite]]=0xFF;
		set_sprite_tile(ptrVWeapon->ubOffsetSprite[ubNextSprite],CurrentVWeapon.ubTile[ubNextSprite]);
		set_sprite_prop(ptrVWeapon->ubOffsetSprite[ubNextSprite],CurrentVWeapon.ubProp[ubNextSprite]);	

		ubNextSprite++;
	}
		
	// Tout est trouve donc on le reserve
	ptrVWeapon->ubNbrSprite=CurrentVWeapon.ubNbrSprite;
	// On fixe le rectangle de collision
	ptrVWeapon->ubRectX=CurrentVWeapon.ubRectX;
	ptrVWeapon->ubRectY=CurrentVWeapon.ubRectY;
	ptrVWeapon->ubRectW=CurrentVWeapon.ubRectW;
	ptrVWeapon->ubRectH=CurrentVWeapon.ubRectH;
	// On fixe la position courante
	ptrVWeapon->ubPosX=VOpa.ubPosX;
	ptrVWeapon->ubPosY=VOpa.ubPosY;
	// Collision = Destruction des armes
	ptrVWeapon->ubCollision=0;
	// Data
	ptrVWeapon->ubData[0]=CurrentVWeapon.ubData[0];
	ptrVWeapon->ubData[1]=CurrentVWeapon.ubData[1];
	ptrVWeapon->ubData[2]=CurrentVWeapon.ubData[2];
	ptrVWeapon->ubData[3]=CurrentVWeapon.ubData[3];
	// et la fonction à executé
	ptrVWeapon->ptrRunVSprite=CurrentVWeapon.ptrRunVSprite;
}

/************************************************************/
/* Init_VTwinShot()
/* Initialise TwinShot
/************************************************************/

void Init_VTwinShot()
{
	CurrentVWeapon.ubNbrSprite=1;
	CurrentVWeapon.ubRectX=0;
	CurrentVWeapon.ubRectY=0;
	CurrentVWeapon.ubRectW=8;
	CurrentVWeapon.ubRectH=8;
	CurrentVWeapon.ubTile[0]=DATA_OFFSET_WEAPON;
	CurrentVWeapon.ubProp[0]=PAL4;
	// Data 0 = Power
	CurrentVWeapon.ubData[0]=POWER_VTWINSHOT;

	CurrentVWeapon.ptrRunVSprite=(ptrFunctionPtr)Run_VTwinShot;
	fctTypeOfWeapon=(ptrFunctionPtr)Run_VTwinShot;
}

/************************************************************/
/* Run_VTwinShot()												
/* Run TwinShot
/************************************************************/

void Run_VTwinShot(structVSprite *ptrVInfo)
{	
	if(ptrVInfo->ubPosX>168 || ptrVInfo->ubCollision==0x80)
	{
		// destruction
		ptrVInfo->ubNbrSprite=0;
		TabWeapon[ptrVInfo->ubOffsetSprite[0]-SPRITE_OFFSET_WEAPON]=0;
		move_sprite(ptrVInfo->ubOffsetSprite[0],0,0);
		return;
	}
	else
	{
		ptrVInfo->ubPosX+=6;
	}

	// Collision Fond
	if(GetVSpriteMap(ptrVInfo->ubPosX,ptrVInfo->ubPosY+6)>32)
	{
		// destruction
		ptrVInfo->ubNbrSprite=0;
		TabWeapon[ptrVInfo->ubOffsetSprite[0]-SPRITE_OFFSET_WEAPON]=0;
		move_sprite(ptrVInfo->ubOffsetSprite[0],0,0);
		return;
	}
	else
	{
		move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY+3);
	}
}

#endif

