/************************************************************/
/*								 
/* Virtual Monster !!!						
/*								 
/************************************************************/

#ifndef	__VMONSTER
#define __VMONSTER

#include ".\sprite\Level1\Monster\VMonster.h"
#include ".\sprite\Level1\Boom\VBoom.c"

/************************************************************/
/* Init_VMonster						
/* Initialise Monster Virtuel
/************************************************************/

void Init_VMonster()
{
	UBYTE y;
	
	for(y=0;y<MAX_MONSTER;y++)
	{
		move_sprite(SPRITE_OFFSET_MONSTER+y,0,0);
		TabMonster[y]=0;
	}

	set_sprite_data(DATA_OFFSET_MONSTER,DATA_WIDTH_MONSTER,PtrMonster);

	for(y=0;y<MAX_VMONSTER;y++)
	{
		TabVMonster[y].ubNbrSprite=0;
		TabVMonster[y].ubCollision=0;
	}

	ubCurrentEvent=0;
	
	PtrEvent=EventVMonster;
	PtrEventPos=EventVMonsterPos;
	PtrEventType=EventVMonsterType;
	
	ubOffsetFindMonster=0;
	
	SWITCH_ROM_MBC1(4);

	Init_VCrasher(&InfoCrasher);
	Init_VEater(&InfoEater);
	Init_VMine(&InfoMine);
	Init_VFlower(&InfoFlower);
	// Missile Up & Right
	Init_VMissile(&InfoMissileUR);
	InfoMissileUR.ubData[0]=0x02;
	InfoMissileUR.ubData[1]=0xFE;
	InfoMissileUR.ubData[2]=0x01;
	// Missile Up & Left
	Init_VMissile(&InfoMissileUL);
	InfoMissileUL.ubData[0]=0xFE;
	InfoMissileUL.ubData[1]=0xFE;
	InfoMissileUL.ubData[2]=0x01;
	// Missile Down & Right
	Init_VMissile(&InfoMissileDR);
	InfoMissileDR.ubData[0]=0x02;
	InfoMissileDR.ubData[1]=0x02;	
	InfoMissileDR.ubData[2]=0x01;
	// Missile Down & Left
	Init_VMissile(&InfoMissileDL);
	InfoMissileDL.ubData[0]=0xFE;
	InfoMissileDL.ubData[1]=0x02;
	InfoMissileDL.ubData[2]=0x01;
	// Missile Up
	Init_VMissile(&InfoMissileUp);
	InfoMissileUp.ubData[0]=0xFF;
	InfoMissileUp.ubData[1]=0xFC;
	InfoMissileUp.ubData[2]=0x03;
	// Missile Down
	Init_VMissile(&InfoMissileDown);
	InfoMissileDown.ubData[0]=0xFF;
	InfoMissileDown.ubData[1]=0x02;
	InfoMissileDown.ubData[2]=0x03;

	// Canon
	Init_VCanonUp(&InfoCanonUp);
	Init_VCanonDown(&InfoCanonDown);
	
	SWITCH_ROM_MBC1(ubLevelRom);

	Init_VBoom();
}

/************************************************************/
/* Run_VMONSTER()
/* Run MONSTER Virtuel
/************************************************************/

void Run_VMonster()
{
	UBYTE ubPosVMonster=0;

	structVSprite *PtrVMonster=TabVMonster;

	// Ajout des nouveaux Monstres toutes les 8 pixels
	
	if((CounterVBL&0x1F)==0)
	{
		while(*PtrEvent==ubCurrentEvent)
		{
			// Evenement d'arret de scroll = NULL
			if((*PtrEventType)==NULL)
			{
				// Pause le Scroll
				StartScroll=0;
				// mais continu a executer les monstres
				break;
			}
			else
			{
			// Monster			
				(*PtrEventType)->ubPosX=*PtrEventPos;
				(*PtrEventType)->ubPosY=*(PtrEventPos+1);
				Add_VMonster(*PtrEventType);

				PtrEventType++;
				PtrEventPos+=2;
				PtrEvent++;
			}					
		}
	
		ubCurrentEvent++;
	}

	// Execution des nouveaux Monstres
	
	SWITCH_ROM_MBC1(4);

	while(ubPosVMonster<MAX_VMONSTER)
	{
		if(PtrVMonster->ubNbrSprite!=0)
		{
			PtrVMonster->ptrRunVSprite(PtrVMonster);
		}
		
		PtrVMonster++;
		ubPosVMonster++;
	}

	SWITCH_ROM_MBC1(ubLevelRom);
}

/************************************************************
 * Find_VMONSTER()												
 * Trouve MONSTER Virtuel disponible et renvoi un
 * un pointeur sur celui ci sinon NULL
 ************************************************************/

structVSprite *Find_VMonster()
{
	UBYTE ubPosVMonster=0;

	structVSprite *PtrVMonster=TabVMonster;

	while(ubPosVMonster<MAX_VMONSTER)
	{
		// Emplacement trouv� ?
		if(PtrVMonster->ubNbrSprite==0)
		{
			return PtrVMonster;
		}
		PtrVMonster++;
		ubPosVMonster++;
	}

	return NULL;
}

/************************************************************
 * Find_MONSTER()												
 * Trouve un sprites disponible
 * renvoi un offset sur celui ci
 ************************************************************/

UBYTE j;
UBYTE i;

UBYTE Find_Monster()
{
	UBYTE ubWidth=0;

	while(ubWidth<MAX_MONSTER)
	{

		ubOffsetFindMonster++;
		
		if(ubOffsetFindMonster==MAX_MONSTER)
		{
			ubOffsetFindMonster=0;
		}

		// Emplacement trouv� ?
		if(TabMonster[ubOffsetFindMonster]==0)
		{	
			// Reserve le
			TabMonster[ubOffsetFindMonster]=0xFF;
			return ubOffsetFindMonster;
		}
		
		ubWidth++;		
	}
	
	return 0xFF;
}

/************************************************************/
/* Add_VMONSTER()												
/* Ajoute MONSTER Virtuel courant dans la liste
/************************************************************/

UBYTE ubOffset[4];

void Add_VMonster(structVSprite *CurrentVMonster)
{
	structVSprite *ptrVMonster;
	UBYTE ubNextSprite;
	UBYTE ubRun;
	
	// ** Trouve un emplacement pour sprite Virtuel **

	ptrVMonster=Find_VMonster();
	if(ptrVMonster==NULL)
	{
		return;
	}

	// ** Cherche des sprites libres **
	
	ubNextSprite=0;
	while(ubNextSprite<CurrentVMonster->ubNbrSprite)
	{
		ubOffset[ubNextSprite]=Find_Monster();
		if(ubOffset[ubNextSprite]==0xFF)
		{			
			ubRun=0;
			{
				// libere
				TabMonster[ubOffset[ubRun]]=0x00;
			}while(++ubRun!=ubNextSprite);
		
			return;
		}
		
		ubNextSprite++;
	}

	// Reserve les sprites Hard
	ubNextSprite=0;
	
	while(ubNextSprite<CurrentVMonster->ubNbrSprite)
	{
		ptrVMonster->ubOffsetSprite[ubNextSprite]=ubOffset[ubNextSprite]+SPRITE_OFFSET_MONSTER;
		//TabMonster[ubOffset[ubNextSprite]]=0xFF;
		set_sprite_tile(ptrVMonster->ubOffsetSprite[ubNextSprite],CurrentVMonster->ubTile[ubNextSprite]);
		set_sprite_prop(ptrVMonster->ubOffsetSprite[ubNextSprite],CurrentVMonster->ubProp[ubNextSprite]);	

		ubNextSprite++;
	}
		
	// Tout est trouve donc on le reserve
	ptrVMonster->ubNbrSprite=CurrentVMonster->ubNbrSprite;
	// On fixe le rectangle de collision
	ptrVMonster->ubRectX=CurrentVMonster->ubRectX;
	ptrVMonster->ubRectY=CurrentVMonster->ubRectY;
	ptrVMonster->ubRectW=CurrentVMonster->ubRectW;
	ptrVMonster->ubRectH=CurrentVMonster->ubRectH;
	// On fixe la position courante
	ptrVMonster->ubPosX=CurrentVMonster->ubPosX;
	ptrVMonster->ubPosY=CurrentVMonster->ubPosY;
	// Collision
	ptrVMonster->ubCollision=0;	
	// Data
	ptrVMonster->ubData[0]=CurrentVMonster->ubData[0];
	ptrVMonster->ubData[1]=CurrentVMonster->ubData[1];
	ptrVMonster->ubData[2]=CurrentVMonster->ubData[2];
	ptrVMonster->ubData[3]=CurrentVMonster->ubData[3];
	// et la fonction � execut�
	ptrVMonster->ptrRunVSprite=CurrentVMonster->ptrRunVSprite;

	j++;

}

/************************************************************/
/* Delete_VMonster()												
/* Detruit un Monstre Virtuel dans la liste
/************************************************************/

void Delete_VMonster(structVSprite *ptrVInfo)
{
	UBYTE ubRun;
	UBYTE *ptr=ptrVInfo->ubOffsetSprite;

	// Libere le Sprite Virtuel
	
	ubRun=ptrVInfo->ubNbrSprite;
	ptrVInfo->ubNbrSprite=0;

	while(ubRun!=0)
	{
		// Libere les Sprites Hard 			
		
		TabMonster[*ptr-SPRITE_OFFSET_MONSTER]=0x00;
		
		// Efface les Sprites Hard 			
		
		move_sprite(*ptr,0,0);
	
		ptr++;
		ubRun--;
	}
}

#endif

