/************************************************************/
/*															*/ 
/* Sprite !!!												*/
/*															*/ 
/************************************************************/

// Tile Sprite

/************************************************************/
/* Define													*/
/************************************************************/

// Taille des datas des sprites

#include ".\Sprite\Data.h"

// Bound

#define SPRITE_MAX_SPRITE	40

// Offset Area Sprite

#define SPRITE_OFFSET_ENGINE	0
#define SPRITE_OFFSET_OPA	2
#define SPRITE_OFFSET_WEAPON	8
#define SPRITE_OFFSET_SHIELD	14
#define SPRITE_OFFSET_MONSTER	16

// Longueur Area Sprite

#define SPRITE_WIDTH_ENGINE	SPRITE_OFFSET_OPA-SPRITE_OFFSET_ENGINE
#define SPRITE_WIDTH_OPA	SPRITE_OFFSET_WEAPON-SPRITE_OFFSET_OPA
#define SPRITE_WIDTH_WEAPON	SPRITE_OFFSET_SHIELD-SPRITE_OFFSET_WEAPON
#define SPRITE_WIDTH_SHIELD	SPRITE_OFFSET_MONSTER-SPRITE_OFFSET_SHIELD
#define	SPRITE_WIDTH_MONSTER	SPRITE_MAX_SPRITE-SPRITE_OFFSET_MONSTER

/************************************************************/
/* Data														*/
/************************************************************/

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

/************************************************************/
/* Prototype												*/
/************************************************************/

void Init_Sprite(void);
//void Set_Bkg_MapAttribut(UWORD uwWidth,UWORD uwHeight,unsigned char *ptrMap);
BYTE Run_VCollision(structVSprite *ptrVInfo);

/************************************************************/
/* Extern													*/
/************************************************************/

// ASM

extern UBYTE GetVSpriteMap(UBYTE ubPosX,UBYTE ubPosY);
extern UBYTE Set2x2VSpriteMap(UBYTE ubPosX,UBYTE ubPosY);
//extern void Show_Money(UBYTE ubPosX,UBYTE ubPosY);

