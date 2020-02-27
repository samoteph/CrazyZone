/************************************************************/
/*															*/ 
/* VMonster !!!
/*															*/ 
/************************************************************/

/************************************************************/
/* Define
/************************************************************/

/************************************************************/
/* Prototype
/************************************************************/

void Init_VMonster(void);
void Run_VMonster(void);
void Add_VMonster(structVSprite *CurrentVMonster);

/** Monstre */

extern void Init_VCrasher(structVSprite *ptrVInfo);
extern void Run_VCrasher(structVSprite *ptrVInfo);

extern void Init_VEater(structVSprite *ptrVInfo);
extern void Run_VEater(structVSprite *ptrVInfo);

extern void Init_VMine(structVSprite *ptrVInfo);
extern void Run_VMine(structVSprite *ptrVInfo);

extern void Init_VFlower(structVSprite *ptrVInfo);
extern void Run_VFlower(structVSprite *ptrVInfo);

extern void Init_VMissile(structVSprite *ptrVInfo);
extern void Run_VMissile(structVSprite *ptrVInfo);

extern void Init_VCanonDown(structVSprite *ptrVInfo);
extern void Run_VCanonDown(structVSprite *ptrVInfo);

extern void Init_VCanonUp(structVSprite *ptrVInfo);
extern void Run_VCanonUp(structVSprite *ptrVInfo);

/************************************************************/
/* Data Interne
/************************************************************/

structVSprite	TabVMonster[MAX_VMONSTER];
UBYTE		TabMonster[MAX_MONSTER];

structVSprite	InfoCrasher;
structVSprite	InfoEater;
structVSprite	InfoMine;
structVSprite	InfoFlower;

structVSprite	InfoCanonUp;
structVSprite	InfoCanonDown;

structVSprite	InfoMissileUR;
structVSprite	InfoMissileUL;
structVSprite	InfoMissileDR;
structVSprite	InfoMissileDL;
structVSprite	InfoMissileUp;
structVSprite	InfoMissileDown;

/** Evenement de declenchement **/

UWORD	*PtrEvent;
UBYTE	*PtrEventPos;
structVSprite **PtrEventType;

UWORD ubCurrentEvent;
UBYTE ubOffsetFindMonster;

// ** Evenement de declenchement des monstres **

extern UWORD EventVMonster[];
extern structVSprite *EventVMonsterType[];
extern UBYTE EventVMonsterPos[];

/************************************************************/
/* Data Externe
/************************************************************/

// ROM
extern	unsigned char PtrMonster[];
