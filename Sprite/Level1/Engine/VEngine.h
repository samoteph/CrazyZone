/************************************************************/
/*															*/ 
/* VEngine !!!
/*															*/ 
/************************************************************/

/************************************************************/
/* Define
/************************************************************/

/************************************************************/
/* Prototype
/************************************************************/

void Init_VEngine(void);
void Run_VEngine(void);

void Init_VSmallWing(void);
void Run_VSmallWing(void);

void Init_VSmallEngine(void);
void Run_VSmallEngine(void);

/************************************************************/
/* Data Interne
/************************************************************/

ptrFunction fctTypeOfEngine;

UBYTE	ubSpeedEngineX;
UBYTE	ubSpeedEngineY;

/************************************************************/
/* Data Externe
/************************************************************/

// ROM
extern	unsigned char PtrEngine[];
