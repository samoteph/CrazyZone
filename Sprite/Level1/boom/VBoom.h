/************************************************************/
/*															*/ 
/* VBoom !!!
/*															*/ 
/************************************************************/

/************************************************************/
/* Define
/************************************************************/

/************************************************************/
/* Prototype
/************************************************************/

void Init_VBoom();
void Init_VStar(structVSprite *CurrentVMonster);
void Run_VStar(structVSprite *CurrentVMonster);

void Init_VExplodeOpa();
void Run_VExplodeOpa(structVSprite *ptrVInfo);

/************************************************************/
/* Data Externe
/************************************************************/

// ROM
extern	unsigned char PtrBoom[];