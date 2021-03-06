/************************************************************/
/*															*/ 
/* ROM1	: Animation et autre								*/
/*															*/ 
/************************************************************/

#include <gb.h>

/** WARNING : Les Animations doivent passer en 1er (@ multiple de 16) **/

// Animation Dime
#include ".\Animation\Level1\DimeLevel1.c"

// Animation Mountain
#include ".\Animation\Level2\FloconLevel2.c"

unsigned char *PtrDimeDataLevel1[]=
{
	DimeDataLevel1,DimeDataLevel1+64,DimeDataLevel1+128,DimeDataLevel1+192
};

unsigned char *PtrFloconDataLevel2[]=
{
	FloconDataLevel2+0x0000,
	FloconDataLevel2+0x0020,
	FloconDataLevel2+0x0040,
	FloconDataLevel2+0x0060,
	FloconDataLevel2+0x0080,
	FloconDataLevel2+0x00A0,
	FloconDataLevel2+0x00C0,
	FloconDataLevel2+0x00E0,
	FloconDataLevel2+0x0100,
	FloconDataLevel2+0x0120,
	FloconDataLevel2+0x0140,
	FloconDataLevel2+0x0160,
	FloconDataLevel2+0x0180,
	FloconDataLevel2+0x01A0,
	FloconDataLevel2+0x01C0,
	FloconDataLevel2+0x01E0,
};

// Palette
#include ".\Scroll\Level2\PaletteLevel2.h"	// Tableau de la palette scroll
#include ".\Sprite\Level1\PaletteLevel1.h"	// Tableau de la palette sprite

// Tile & Map
#include ".\Scroll\Level2\TileLevel2.c"		// Tile
#include ".\Scroll\Level2\MapLevel2.c"		// Map

// Window Map
#include ".\Window\Level2\WindowMap2.c"

// Tile Sprite
#include ".\sprite\Level1\Opa\SpriteOpa.c"	
#include ".\sprite\Level1\Engine\SpriteEngine.c"
#include ".\sprite\Level1\Weapon\SpriteWeapon.c"
#include ".\sprite\Level1\Monster\SpriteMonster.c"
#include ".\sprite\Level1\Boom\SpriteBoom.c"

// Evenement

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

extern structVSprite InfoCrasher;
extern structVSprite InfoEater;
extern structVSprite InfoMine;
extern structVSprite InfoFlower;
extern structVSprite InfoCanonUp;
extern structVSprite InfoCanonDown;
extern structVSprite InfoMissileUp;

// ** Evenement de declenchement des monstres **

UWORD EventVMonster[]=
{
	// Groupe 1
	1,
	15,
	15,
	18,
	20,

	// Groupe 2
	24,
	24,
	24,
	32,
	33,
	33,

	// Groupe 3

	40,
	50,
	51,
	52,
	55,

	// Groupe 4
	
	61,
	61,
	61,
	64,
	68,


	// Groupe 5
	
	70,
	77,
	78,
	79,
	80,

	// Groupe 6
	
	85,
	89,
	92,
	94,
	100,

	// Groupe 7
	
	110,
	111,
	118,
	125,
	130,

	// Groupe 8
	
	135,
	140,
	145,
	147,
	148,

	// Groupe 9
	
	152,
	153,
	160,
	162,
	163,

	// Groupe 10
	
	170,
	171,
	172,
	178,
	185,

	// Groupe 11
	
	190,
	193,
	194,
	200,
	201,

	// Groupe 12
	
	208,
	209,
	211,
	215,
	220,

	// Groupe 13
	
	225,
	230,
	233,
	238,
	242,

	// Groupe 14
	
	245,
	248,
	252,
	258,
	263,

	// Groupe 15
	
	264,
	268,
	272,
	273,
	280,

	// Fin du Scroll
	282,
};

structVSprite *EventVMonsterType[]=
{


	// Groupe 1
	&InfoMine,
	&InfoFlower,
	&InfoMine,
	&InfoEater,
	&InfoEater,
	
	// Groupe 2
	&InfoCrasher,
	&InfoEater,
	&InfoEater,
	&InfoMine,
	&InfoCanonDown,
	&InfoCanonUp,

	// Groupe 3
	&InfoCrasher,
	&InfoMine,
	&InfoEater,
	&InfoEater,
	&InfoEater,

	// Groupe 4
	&InfoFlower,
	&InfoFlower,
	&InfoFlower,
	&InfoEater,
	&InfoMine,

	// Groupe 5
	&InfoCrasher,
	&InfoCrasher,
	&InfoMine,
	&InfoEater,
	&InfoCanonUp,


	// Groupe 6
	&InfoEater,
	&InfoEater,
	&InfoEater,
	&InfoEater,
	&InfoEater,

	// Groupe 7
	&InfoEater,
	&InfoEater,
	&InfoEater,
	&InfoCrasher,
	&InfoFlower,

	// Groupe 8
	&InfoCrasher,
	&InfoEater,
	&InfoMine,
	&InfoEater,
	&InfoFlower,

	// Groupe 9
	&InfoEater,
	&InfoEater,
	&InfoFlower,
	&InfoFlower,
	&InfoFlower,

	// Groupe 10
	&InfoEater,
	&InfoEater,
	&InfoMine,
	&InfoEater,
	&InfoCrasher,

	// Groupe 11
	&InfoFlower,
	&InfoEater,
	&InfoMine,
	&InfoEater,
	&InfoEater,

	// Groupe 12
	&InfoFlower,
	&InfoFlower,
	&InfoMine,
	&InfoEater,
	&InfoEater,

	// Groupe 13
	&InfoFlower,
	&InfoCrasher,
	&InfoMine,
	&InfoEater,
	&InfoFlower,

	// Groupe 14
	&InfoCrasher,
	&InfoCrasher,
	&InfoMine,
	&InfoEater,
	&InfoEater,

	// Groupe 15
	&InfoEater,
	&InfoEater,
	&InfoMine,
	&InfoEater,
	&InfoEater,

	// Fin du Scroll
	NULL,
};

// ** Evenement de declenchement des position des monstres **

UBYTE EventVMonsterPos[]=
{
	// Groupe 1
	170,9*8,
	170,0,
	170,50,
	170,30,
	170,0,

	// Groupe 2
	170,110,
	170,80,
	170,100,
	170,24,
	170,77,
	170,35,

	// Groupe 3
	170,110,
	170,80,
	170,100,
	170,20,
	165,85,

	// Groupe 4
	100,0,
	170,80,
	170,100,
	170,20,
	165,85,

	// Groupe 5
	170,110,
	170,80,
	170,4*8,
	170,20,
	170,0,

	// Groupe 6
	170,110,
	170,80,
	170,15*8-5,
	170,15*8-5,
	170,50,

	// Groupe 7
	170,110,
	170,80,
	170,4*8,
	178,4*8,
	170,9*8-3,

	// Groupe 8
	168,80,
	185,80,
	170,15*8-7,
	170,15*8-5,
	177,51,

	// Groupe 9
	170,110,
	170,80,
	170,20,
	170,10,
	170,0,

	// Groupe 10
	16,0,
	20,0,
	170,14*8,
	170,15*8-5,
	170,50,

	// Groupe 11
	170,0,
	170,80,
	170,8*7,
	170,20,
	170,15*8-5,

	// Groupe 12
	170,139,
	178,80,
	170,15*8,
	170,15*8-5,
	170,50,

	// Groupe 13
	170,110,
	170,80,
	170,4*8,
	170,20,
	170,139,

	// Groupe 14
	170,110,
	170,80,
	170,15*8-5,
	170,15*8-5,
	170,50,

	// Groupe 15
	170,110,
	170,80,
	170,4*8,
	170,20,
	170,15*8-5,

};

