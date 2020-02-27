/************************************************************/
/*															*/ 
/* VWeapon !!!
/*															*/ 
/************************************************************/

/************************************************************/
/* Define
/************************************************************/

#define MAX_VWEAPON	6
#define MAX_WEAPON	SPRITE_WIDTH_WEAPON

#define POWER_VTWINSHOT	1

/************************************************************/
/* Prototype
/************************************************************/

void Init_VWeapon(void);
void Run_VWeapon(void);

void Init_VTwinShot(void);
void Run_VTwinShot(structVSprite *ptrVInfo);

/************************************************************/
/* Data Interne
/************************************************************/

ptrFunction 	fctTypeOfWeapon;
structVSprite	CurrentVWeapon;

structVSprite	TabVWeapon[MAX_VWEAPON];
UBYTE		TabWeapon[MAX_WEAPON];
UBYTE		ubOffsetFindWeapon;

/************************************************************/
/* Data Externe
/************************************************************/

// ROM
extern	unsigned char PtrWeapon[];
