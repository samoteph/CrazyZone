/************************************************************/
/*															*/ 
/* ROM4	: Code Monstre */
/*															*/ 
/************************************************************/

#include <gb.h>
#include ".\Sprite\Data.h"

typedef void (* ptrFunctionPtr)(void *);

typedef struct _structVSprite
{
	UBYTE		ubNbrSprite;
	UBYTE		ubPosX,ubPosY;
	UBYTE		ubRectX,ubRectY,ubRectW,ubRectH;
	UBYTE		ubOffsetSprite[4];
	UBYTE		ubTile[4];
	UBYTE		ubProp[4];
	UBYTE		ubData[4];
	UBYTE		ubCollision;

	ptrFunctionPtr	ptrRunVSprite;
}structVSprite;

void Init_VCrasher(structVSprite *ptrVInfo);
void Run_VCrasher(structVSprite *ptrVInfo);

void Init_VEater(structVSprite *ptrVInfo);
void Run_VEater(structVSprite *ptrVInfo);

void Init_VMine(structVSprite *ptrVInfo);
void Run_VMine(structVSprite *ptrVInfo);

void Init_VFlower(structVSprite *ptrVInfo);
void Run_VFlower(structVSprite *ptrVInfo);

void Init_VMissile(structVSprite *ptrVInfo);
void Run_VMissile(structVSprite *ptrVInfo);

void Init_VCanonDown(structVSprite *ptrVInfo);
void Run_VCanonDown(structVSprite *ptrVInfo);

void Init_VCanonUp(structVSprite *ptrVInfo);
void Run_VCanonUp(structVSprite *ptrVInfo);

extern UBYTE CounterVBL;

extern structVSprite VOpa;
extern structVSprite InfoMissileUR;
extern structVSprite InfoMissileUL;
extern structVSprite InfoMissileDR;
extern structVSprite InfoMissileDL;
extern structVSprite InfoMissileUp;
extern structVSprite InfoMissileDown;

/************************************************************/
/* Initialise_VCrasher()												
/* Ajoute VCrasher Virtuel courant dans la liste
/************************************************************/

void Init_VCrasher(structVSprite *ptrVInfo)
{
	ptrVInfo->ubNbrSprite=4;
	ptrVInfo->ubData[0]=1;

	ptrVInfo->ubTile[0]=DATA_OFFSET_CRASHER+2;
	ptrVInfo->ubTile[1]=DATA_OFFSET_CRASHER+3;
	ptrVInfo->ubTile[2]=DATA_OFFSET_CRASHER+2;
	ptrVInfo->ubTile[3]=DATA_OFFSET_CRASHER+3;
	
	ptrVInfo->ubRectX=RECT_X_VCRASHER;
	ptrVInfo->ubRectY=RECT_Y_VCRASHER;
	ptrVInfo->ubRectW=RECT_W_VCRASHER;
	ptrVInfo->ubRectH=RECT_H_VCRASHER;

	ptrVInfo->ubProp[0]=PAL4;
	ptrVInfo->ubProp[1]=PAL4;
	ptrVInfo->ubProp[2]=PAL4|S_FLIPX;
	ptrVInfo->ubProp[3]=PAL4|S_FLIPX;

	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VCrasher;
}

/************************************************************/
/* Run_VCrasher()												
/* Ajoute VCrasher Virtuel courant dans la liste
/************************************************************/

void Run_VCrasher(structVSprite *ptrVInfo)
{
	// Collision avec Armes Ou Opa
	if(ptrVInfo->ubCollision>DESTRUCTION_VCRASHER)
	{
		ptrVInfo->ubCollision=0x80;
		Init_VStar(ptrVInfo);
		return;		
	}

	// Deplacement X + Destruction
	if((CounterVBL&0x03)==0)
	{
		ptrVInfo->ubPosX--;
		if(ptrVInfo->ubPosX==248)
		{
			Delete_VMonster(ptrVInfo);
			return;
		}
	}
	
	// Deplacement Y
	// Data0 =direction	
	if(ptrVInfo->ubData[0]==1)
	{
		if(GetVSpriteMap(ptrVInfo->ubPosX,ptrVInfo->ubPosY+17)>32 || GetVSpriteMap(ptrVInfo->ubPosX+8,ptrVInfo->ubPosY+17)>32 || ptrVInfo->ubPosY==SPRITE_WIN_DOWN)
		{
			ptrVInfo->ubData[0]=0;
			set_sprite_tile(ptrVInfo->ubOffsetSprite[0],DATA_OFFSET_CRASHER+2);
			set_sprite_tile(ptrVInfo->ubOffsetSprite[1],DATA_OFFSET_CRASHER+3);
			set_sprite_tile(ptrVInfo->ubOffsetSprite[2],DATA_OFFSET_CRASHER+2);
			set_sprite_tile(ptrVInfo->ubOffsetSprite[3],DATA_OFFSET_CRASHER+3);
			
		}
		else
		{
			ptrVInfo->ubPosY++;
		}
	}
	else
	{
		if(GetVSpriteMap(ptrVInfo->ubPosX,ptrVInfo->ubPosY-1)>32 || GetVSpriteMap(ptrVInfo->ubPosX+8,ptrVInfo->ubPosY-1)>32 || ptrVInfo->ubPosY==SPRITE_WIN_UP)
		{
			ptrVInfo->ubData[0]=1;
			set_sprite_tile(ptrVInfo->ubOffsetSprite[0],DATA_OFFSET_CRASHER+0);
			set_sprite_tile(ptrVInfo->ubOffsetSprite[1],DATA_OFFSET_CRASHER+1);
			set_sprite_tile(ptrVInfo->ubOffsetSprite[2],DATA_OFFSET_CRASHER+0);
			set_sprite_tile(ptrVInfo->ubOffsetSprite[3],DATA_OFFSET_CRASHER+1);
		}
		else
		{
			ptrVInfo->ubPosY--;
		}
	}

	// Affichage
	move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[1],ptrVInfo->ubPosX,ptrVInfo->ubPosY+8);
	move_sprite(ptrVInfo->ubOffsetSprite[2],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[3],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY+8);
}

/************************************************************/
/* Initialise_VEater()												
/* Ajoute VEater Virtuel courant dans la liste
/************************************************************/

void Init_VEater(structVSprite *ptrVInfo)
{
	ptrVInfo->ubNbrSprite=4;
	
	// Animation
	ptrVInfo->ubData[0]=0;
	// Deplacement X
	ptrVInfo->ubData[1]=0xFF;
	// Vie Max
	ptrVInfo->ubData[2]=0x0;
	
	ptrVInfo->ubTile[0]=DATA_OFFSET_EATER+0;
	ptrVInfo->ubTile[1]=DATA_OFFSET_EATER+1;
	ptrVInfo->ubTile[2]=DATA_OFFSET_EATER+2;
	ptrVInfo->ubTile[3]=DATA_OFFSET_EATER+3;
	
	ptrVInfo->ubRectX=RECT_X_VEATER;
	ptrVInfo->ubRectY=RECT_Y_VEATER;
	ptrVInfo->ubRectW=RECT_W_VEATER;
	ptrVInfo->ubRectH=RECT_H_VEATER;

	ptrVInfo->ubProp[0]=PAL5;
	ptrVInfo->ubProp[1]=PAL5;
	ptrVInfo->ubProp[2]=PAL5;
	ptrVInfo->ubProp[3]=PAL5;

	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VEater;
}

/************************************************************/
/* Run_VEater()												
/* Ajoute VEater Virtuel courant dans la liste
/************************************************************/

void Run_VEater(structVSprite *ptrVInfo)
{
	UBYTE ubAnim,ubSpeed;
	ubSpeed=ptrVInfo->ubData[1];

	// Collision avec Opa
	if(ptrVInfo->ubCollision>DESTRUCTION_VEATER)
	{
		ptrVInfo->ubCollision=0x80;
		Init_VStar(ptrVInfo);
		return;		
	}

	// Deplacement X + Collision à droite & gauche : on change de sens
	
	if((CounterVBL&0x1F)==0)
	{

		// Vie Max du Eater

		if(ptrVInfo->ubData[2]<15)
		{
			ptrVInfo->ubData[2]++;

			if(ptrVInfo->ubPosX<VOpa.ubPosX)
			{
				ptrVInfo->ubData[1]=0x01;
			}
			else
			{
				ptrVInfo->ubData[1]=0xFF;
			}
		}		
	}
	
	// Animation
	if((CounterVBL&0x0F)==0)
	{
		ptrVInfo->ubData[0]++;
		ubAnim=(ptrVInfo->ubData[0]&3)<<2;
		set_sprite_tile(ptrVInfo->ubOffsetSprite[0],DATA_OFFSET_EATER+0+ubAnim);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[1],DATA_OFFSET_EATER+1+ubAnim);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[2],DATA_OFFSET_EATER+2+ubAnim);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[3],DATA_OFFSET_EATER+3+ubAnim);
		
	}
	
	ubSpeed=ptrVInfo->ubData[1];
	
	// Deplacement Y
	if((CounterVBL&0x03)==0)
	{
		if(VOpa.ubPosY>ptrVInfo->ubPosY)
		{
				ptrVInfo->ubPosY++;
		}
		else if(VOpa.ubPosY<ptrVInfo->ubPosY)
		{
				ptrVInfo->ubPosY--;
		}
		else
		{
			// Speed = Speed *2
			ubSpeed=ptrVInfo->ubData[1]<<1;
		}
	}

	// Destruction
	if((CounterVBL&0x01)==0)
	{
		ptrVInfo->ubPosX+=ubSpeed;
		
		if(ptrVInfo->ubPosX<248 && ptrVInfo->ubPosX>180)
		{
			Delete_VMonster(ptrVInfo);
			
			return;
		}
	}
	
	move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[1],ptrVInfo->ubPosX,ptrVInfo->ubPosY+8);
	move_sprite(ptrVInfo->ubOffsetSprite[2],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[3],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY+8);
}

/************************************************************/
/* Initialise_VMine()												
/* Ajoute VMine Virtuel courant dans la liste
/************************************************************/

void Init_VMine(structVSprite *ptrVInfo)
{
	ptrVInfo->ubNbrSprite=4;
	ptrVInfo->ubData[0]=0xFF;

	ptrVInfo->ubTile[0]=DATA_OFFSET_MINE+0;
	ptrVInfo->ubTile[1]=DATA_OFFSET_MINE+1;
	ptrVInfo->ubTile[2]=DATA_OFFSET_MINE+0;
	ptrVInfo->ubTile[3]=DATA_OFFSET_MINE+1;
	
	ptrVInfo->ubRectX=RECT_X_VMINE;
	ptrVInfo->ubRectY=RECT_Y_VMINE;
	ptrVInfo->ubRectW=RECT_W_VMINE;
	ptrVInfo->ubRectH=RECT_H_VMINE;

	ptrVInfo->ubProp[0]=PAL4;
	ptrVInfo->ubProp[1]=PAL4;
	ptrVInfo->ubProp[2]=PAL4|S_FLIPX;
	ptrVInfo->ubProp[3]=PAL4|S_FLIPX;

	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VMine;
}

/************************************************************/
/* Run_VMine()												
/* Ajoute VMine Virtuel courant dans la liste
/************************************************************/

void Run_VMine(structVSprite *ptrVInfo)
{
	// Collision avec Armes Ou Opa
	if(ptrVInfo->ubCollision>DESTRUCTION_VMINE)
	{
		ptrVInfo->ubCollision=0x80;
		Init_VStar(ptrVInfo);
		return;		
	}

	// Deplacement X + Destruction
	if((CounterVBL&0x01)==0)
	{
		ptrVInfo->ubPosX+=ptrVInfo->ubData[0];
		
		if(ptrVInfo->ubData[0]==1)
		{
			if(GetVSpriteMap(ptrVInfo->ubPosX+17,ptrVInfo->ubPosY)>32 || GetVSpriteMap(ptrVInfo->ubPosX+17,ptrVInfo->ubPosY+8)>32)
			{
				ptrVInfo->ubData[0]=0xFF;
			}
		}
		else
		{
			if(GetVSpriteMap(ptrVInfo->ubPosX-1,ptrVInfo->ubPosY)>32 ||GetVSpriteMap(ptrVInfo->ubPosX-1,ptrVInfo->ubPosY+8)>32)
			{
				ptrVInfo->ubData[0]=1;
			}
		}
			
		if(ptrVInfo->ubPosX==248)
		{
			Delete_VMonster(ptrVInfo);			
			return;
		}
	}
	
	// Affichage
	move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[1],ptrVInfo->ubPosX,ptrVInfo->ubPosY+8);
	move_sprite(ptrVInfo->ubOffsetSprite[2],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[3],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY+8);
}

/************************************************************/
/* Initialise_VFlower()												
/* Ajoute VFlower Virtuel courant dans la liste
/************************************************************/

void Init_VFlower(structVSprite *ptrVInfo)
{
	ptrVInfo->ubNbrSprite=4;
	// sens de l'animation
	ptrVInfo->ubData[0]=0;

	ptrVInfo->ubTile[0]=DATA_OFFSET_FLOWER+0;
	ptrVInfo->ubTile[1]=DATA_OFFSET_FLOWER+1;
	ptrVInfo->ubTile[2]=DATA_OFFSET_FLOWER+2;
	ptrVInfo->ubTile[3]=DATA_OFFSET_FLOWER+3;
	
	ptrVInfo->ubRectX=RECT_X_VFLOWER;
	ptrVInfo->ubRectY=RECT_Y_VFLOWER;
	ptrVInfo->ubRectW=RECT_W_VFLOWER;
	ptrVInfo->ubRectH=RECT_H_VFLOWER;

	ptrVInfo->ubProp[0]=PAL6;
	ptrVInfo->ubProp[1]=PAL6;
	ptrVInfo->ubProp[2]=PAL6;
	ptrVInfo->ubProp[3]=PAL6;

	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VFlower;
}

/************************************************************/
/* Run_VFlower()												
/* Ajoute Flower Virtuel courant dans la liste
/************************************************************/

UBYTE ubAnimFlower[16]=
{
	DATA_OFFSET_FLOWER+4*0,
	DATA_OFFSET_FLOWER+4*1,
	DATA_OFFSET_FLOWER+4*2,
	DATA_OFFSET_FLOWER+4*3,
	DATA_OFFSET_FLOWER+4*3,
	DATA_OFFSET_FLOWER+4*3,
	DATA_OFFSET_FLOWER+4*2,
	DATA_OFFSET_FLOWER+4*1,

	DATA_OFFSET_FLOWER+4*0,
	DATA_OFFSET_FLOWER+4*4,
	DATA_OFFSET_FLOWER+4*5,
	DATA_OFFSET_FLOWER+4*6,
	DATA_OFFSET_FLOWER+4*6,
	DATA_OFFSET_FLOWER+4*6,
	DATA_OFFSET_FLOWER+4*5,
	DATA_OFFSET_FLOWER+4*4,
};

void Run_VFlower(structVSprite *ptrVInfo)
{
	UBYTE ubAnim;
	UBYTE ubData;
	UBYTE ubX,ubY;
	
	// Collision avec Armes Ou Opa ou Sol
	ubData=GetVSpriteMap(ptrVInfo->ubPosX+(RECT_X_VEATER+RECT_W_VEATER/2),ptrVInfo->ubPosY+17); 

	if(ptrVInfo->ubCollision>DESTRUCTION_VFLOWER || ubData>32)
	{

		ubX=ptrVInfo->ubPosX;
		ubY=ptrVInfo->ubPosY;
		
		Delete_VMonster(ptrVInfo);

		// Lance les Missiles

		InfoMissileUR.ubPosX=ubX+8;
		InfoMissileUR.ubPosY=ubY;
		Add_VMonster(&InfoMissileUR);

		InfoMissileUL.ubPosX=ubX;
		InfoMissileUL.ubPosY=ubY;
		Add_VMonster(&InfoMissileUL);

		InfoMissileDR.ubPosX=ubX+8;
		InfoMissileDR.ubPosY=ubY+8;
		Add_VMonster(&InfoMissileDR);

		InfoMissileDL.ubPosX=ubX;
		InfoMissileDL.ubPosY=ubY+8;
		Add_VMonster(&InfoMissileDL);

		return;		
	}

	// Deplacement X + Destruction
	if((CounterVBL&0x03)==0)
	{
		ptrVInfo->ubPosX--;
	}

	if((CounterVBL&0x07)==0)
	{
		ptrVInfo->ubPosY++;
		
		ubData=++(ptrVInfo->ubData[0]);
		ubAnim=ubAnimFlower[ubData&0x0F];

		set_sprite_tile(ptrVInfo->ubOffsetSprite[0],ubAnim+0);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[1],ubAnim+1);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[2],ubAnim+2);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[3],ubAnim+3);
	}
			
	if(ptrVInfo->ubPosX==248 || ptrVInfo->ubPosY==144)
	{
		Delete_VMonster(ptrVInfo);
		return;
	}
	
	// Affichage

	move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[1],ptrVInfo->ubPosX,ptrVInfo->ubPosY+8);
	move_sprite(ptrVInfo->ubOffsetSprite[2],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[3],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY+8);
}

/************************************************************/
/* Initialise_VMissile()												
/* Ajoute VMissile Virtuel courant dans la liste
/************************************************************/

void Init_VMissile(structVSprite *ptrVInfo)
{
	ptrVInfo->ubNbrSprite=1;
	// direction du missile dans ubData[0] & ubData[1]

	ptrVInfo->ubTile[0]=DATA_OFFSET_MISSILE;
	ptrVInfo->ubProp[0]=PAL5;
	
	ptrVInfo->ubRectX=RECT_X_VMISSILE;
	ptrVInfo->ubRectY=RECT_Y_VMISSILE;
	ptrVInfo->ubRectW=RECT_W_VMISSILE;
	ptrVInfo->ubRectH=RECT_H_VMISSILE;


	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VMissile;
}

/************************************************************/
/* Run_VMissile()												
/* Ajoute VMine Virtuel courant dans la liste
/************************************************************/

void Run_VMissile(structVSprite *ptrVInfo)
{
	// Deplacement X + Destruction
	if((CounterVBL&(ptrVInfo->ubData[2]))==0)
	{
		ptrVInfo->ubPosX+=ptrVInfo->ubData[0];
		ptrVInfo->ubPosY+=ptrVInfo->ubData[1];
		
		if(ptrVInfo->ubPosX<248 && ptrVInfo->ubPosX>180)
		{
			Delete_VMonster(ptrVInfo);
			return;
		}

		if(ptrVInfo->ubPosY<8 || ptrVInfo->ubPosY>160)
		{
			Delete_VMonster(ptrVInfo);
			return;
		}
		// Affichage
		move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY);
	}	
}

/************************************************************/
/* Initialise_VCanonDown()												
/* Ajoute VCanon Virtuel courant dans la liste
/************************************************************/

void Init_VCanonDown(structVSprite *ptrVInfo)
{
	ptrVInfo->ubNbrSprite=4;
	// direction du missile dans ubData[0]

	ptrVInfo->ubTile[0]=DATA_OFFSET_CANON+0;
	ptrVInfo->ubTile[1]=DATA_OFFSET_CANON+1;
	ptrVInfo->ubTile[2]=DATA_OFFSET_CANON+2;
	ptrVInfo->ubTile[3]=DATA_OFFSET_CANON+3;

	ptrVInfo->ubProp[0]=PAL0;
	ptrVInfo->ubProp[1]=PAL4;
	ptrVInfo->ubProp[2]=PAL0;
	ptrVInfo->ubProp[3]=PAL4;
	
	ptrVInfo->ubRectX=RECT_X_VCANON;
	ptrVInfo->ubRectY=RECT_Y_VCANON;
	ptrVInfo->ubRectW=RECT_W_VCANON;
	ptrVInfo->ubRectH=RECT_H_VCANON;

	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VCanonDown;
}

/************************************************************/
/* Run_VCanon()												
/* Ajoute VCanon Virtuel courant dans la liste
/************************************************************/


UBYTE ubAnimCanon[16]=
{
	DATA_OFFSET_CANON+4*0,
	DATA_OFFSET_CANON+4*0,
	DATA_OFFSET_CANON+4*0,
	DATA_OFFSET_CANON+4*1,
	DATA_OFFSET_CANON+4*1,
	DATA_OFFSET_CANON+4*2,
	DATA_OFFSET_CANON+4*2,
	DATA_OFFSET_CANON+4*3,

	DATA_OFFSET_CANON+4*3,
	DATA_OFFSET_CANON+4*2,
	DATA_OFFSET_CANON+4*2,
	DATA_OFFSET_CANON+4*3,
	DATA_OFFSET_CANON+4*3,
	DATA_OFFSET_CANON+4*2,
	DATA_OFFSET_CANON+4*2,
	DATA_OFFSET_CANON+4*0,
};

void Run_VCanonDown(structVSprite *ptrVInfo)
{
	UBYTE ubAnim;
	UBYTE ubData;
	
	if(ptrVInfo->ubCollision>DESTRUCTION_VCANON)
	{
		ptrVInfo->ubCollision=0x80;
		Init_VStar(ptrVInfo);
		return;		
	}

	// Deplacement X + Destruction
	if((CounterVBL&0x03)==0)
	{
		ptrVInfo->ubPosX--;
	}

	if((CounterVBL&0x07)==0)
	{
		ubData=++(ptrVInfo->ubData[0]);
		ubAnim=ubAnimCanon[ubData&0x0F];

		set_sprite_tile(ptrVInfo->ubOffsetSprite[0],ubAnim+0);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[1],ubAnim+1);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[2],ubAnim+2);
		set_sprite_tile(ptrVInfo->ubOffsetSprite[3],ubAnim+3);

		// Lance le Missile
		if((ubData&0x0F)==0x0F)
		{
			// Droite
			if(VOpa.ubPosX>(ptrVInfo->ubPosX+30))
			{
				InfoMissileUR.ubPosX=ptrVInfo->ubPosX+4;
				InfoMissileUR.ubPosY=ptrVInfo->ubPosY-5;
				Add_VMonster(&InfoMissileUR);
			}
			// gauche
			else if(VOpa.ubPosX<(ptrVInfo->ubPosX-30))
			{
				InfoMissileUL.ubPosX=ptrVInfo->ubPosX+4;
				InfoMissileUL.ubPosY=ptrVInfo->ubPosY-5;
				Add_VMonster(&InfoMissileUL);
			}
			// centre
			else
			{
				InfoMissileUp.ubPosX=ptrVInfo->ubPosX+4;
				InfoMissileUp.ubPosY=ptrVInfo->ubPosY-5;
				Add_VMonster(&InfoMissileUp);
			}
		}
	}
			
	if(ptrVInfo->ubPosX==248)
	{
		Delete_VMonster(ptrVInfo);
		return;
	}
	
	// Affichage

	move_sprite(ptrVInfo->ubOffsetSprite[0],ptrVInfo->ubPosX,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[1],ptrVInfo->ubPosX,ptrVInfo->ubPosY+8);
	move_sprite(ptrVInfo->ubOffsetSprite[2],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY);
	move_sprite(ptrVInfo->ubOffsetSprite[3],ptrVInfo->ubPosX+8,ptrVInfo->ubPosY+8);
}

/************************************************************/
/* Initialise_VCanonDown()												
/* Ajoute VCanon Virtuel courant dans la liste
/************************************************************/

void Init_VCanonUp(structVSprite *ptrVInfo)
{
	ptrVInfo->ubNbrSprite=4;
	// direction du missile dans ubData[0]

	ptrVInfo->ubTile[0]=DATA_OFFSET_CANON+1;
	ptrVInfo->ubTile[1]=DATA_OFFSET_CANON+0;
	ptrVInfo->ubTile[2]=DATA_OFFSET_CANON+3;
	ptrVInfo->ubTile[3]=DATA_OFFSET_CANON+2;

	ptrVInfo->ubProp[0]=PAL4|S_FLIPY;
	ptrVInfo->ubProp[1]=PAL0|S_FLIPY;
	ptrVInfo->ubProp[2]=PAL4|S_FLIPY;
	ptrVInfo->ubProp[3]=PAL0|S_FLIPY;
	
	ptrVInfo->ubRectX=RECT_X_VCANON;
	ptrVInfo->ubRectY=RECT_Y_VCANON;
	ptrVInfo->ubRectW=RECT_W_VCANON;
	ptrVInfo->ubRectH=RECT_H_VCANON;

	ptrVInfo->ptrRunVSprite=(ptrFunctionPtr)Run_VCanonUp;
}

/************************************************************/
/* Run_VCanonUp()												
/* Ajoute VCanon Virtuel courant dans la liste
/************************************************************/

void Run_VCanonUp(structVSprite *ptrVInfo)
{

	UBYTE ubAnim;
	UBYTE ubData;
	UBYTE ubPosX,ubPosY;
	UBYTE *ptr=ptrVInfo->ubOffsetSprite;
	
	if(ptrVInfo->ubCollision>DESTRUCTION_VCANON)
	{
		ptrVInfo->ubCollision=0x80;
		Init_VStar(ptrVInfo);
		return;		
	}

	// Deplacement X + Destruction
	if((CounterVBL&0x03)==0)
	{
		ptrVInfo->ubPosX--;
	}

	ubPosX=ptrVInfo->ubPosX;
	ubPosY=ptrVInfo->ubPosY;
	
	if((CounterVBL&0x07)==0)
	{
		ubData=++(ptrVInfo->ubData[0]);
		ubAnim=ubAnimCanon[ubData&0x0F];

		set_sprite_tile(*(ptr),ubAnim+1);
		set_sprite_tile(*(ptr+1),ubAnim+0);
		set_sprite_tile(*(ptr+2),ubAnim+3);
		set_sprite_tile(*(ptr+3),ubAnim+2);

		// Lance le Missile
		if((ubData&0x0F)==0x0F)
		{
			// Droite
			if(VOpa.ubPosX>(ubPosX+30))
			{
				InfoMissileDR.ubPosX=ubPosX+4;
				InfoMissileDR.ubPosY=ubPosY+16;
				Add_VMonster(&InfoMissileDR);
			}
			// gauche
			else if(VOpa.ubPosX<(ubPosX-30))
			{
				InfoMissileDL.ubPosX=ubPosX+4;
				InfoMissileDL.ubPosY=ubPosY+16;
				Add_VMonster(&InfoMissileDL);
			}
			// centre
			else
			{
				InfoMissileDown.ubPosX=ubPosX+4;
				InfoMissileDown.ubPosY=ubPosY+16;
				Add_VMonster(&InfoMissileDown);
			}
		}
	}
			
	if(ubPosX==248)
	{
		Delete_VMonster(ptrVInfo);
		return;
	}
	
	// Affichage

	move_sprite(*ptr,ubPosX,ubPosY);
	move_sprite(*(ptr+1),ubPosX,ubPosY+8);
	move_sprite(*(ptr+2),ubPosX+8,ubPosY);
	move_sprite(*(ptr+3),ubPosX+8,ubPosY+8);
}

TabSin[]={
	25,27,29,32,34,
	36,38,40,42,44,
	45,46,47,48,49,
	49,49,49,49,48,
	47,46,45,43,42,
	40,38,36,34,31,
	29,27,25,22,20,
	18,16,14,12,10,
	8,7,6,5,4,3,
	3,3,3,3,4,4,
	5,6,7,9,10,12,
	13,15,17,19,21,
	23,25,26,28,30,
	32,33,35,36,37,
	38,39,40,40,40,
	41,41,41,40,40,
	39,39,38,37,36,
	35,33,32,31,30,28,
	27,26,25,23,22,21,
	20,19,18,18,17,17,
	16,16,16,16,16,16,
	16,16,17,17,18,18,
	19,19,20,21,21,22,
	22,23,24,24,24,25,
	25,26,26,26,26,26,
	26,26,26,26,26,25,
	25,25,25,24,24,24,
	23,23,23,23,23,23,
	23,23,23,23,24,24};
