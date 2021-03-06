/************************************************************/
/*															 
/* Crazy Zone : A GBC Game by Sam 19/08/1999				
/*															 
/************************************************************/

/************************************************************/
/* Prototype															
/************************************************************/

void EndGame(void);

/************************************************************/
/* Type
/************************************************************/

typedef void (* ptrFunction)();
typedef void (* ptrFunctionPtr)(void *);

extern unsigned char PtrWindowMap[];

extern unsigned char PtrCrazyTile[];
extern unsigned char PtrCrazyMap[];
extern UWORD PtrCrazyTilePal[];

extern unsigned char PtrCrazySprite[];

extern unsigned char PtrLogoTile[];
extern unsigned char PtrLogoMap[];
extern UWORD PtrLogoTilePal[];

extern unsigned char PtrTextTile[];
extern unsigned char PtrTextMap[];
extern unsigned char PtrText2Map[];
extern UWORD PtrTextTilePal[];

extern unsigned char PtrBlankMap[];

extern void VBL_Title();
extern void HBL_Title();

UBYTE ubLevelRom;
UBYTE ubLevel;

ptrFunction ubLevelVBL;
ptrFunction ubLevelHBL;

/************************************************************/
/* DEFINE
/************************************************************/

#define START	0
#define RESET	1

void main(void);
void Show_Level(void);
void NextLevel(void);

