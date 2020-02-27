/************************************************************/
/*															*/ 
/* Crazy Zone : A GBC Game by Sam 19/08/1999				*/
/*															*/ 
/************************************************************/

#include <gb.h>

#include "main.h"
#include ".\scroll\scroll.c"
#include ".\sprite\sprite.c"
#include ".\SpeedUp\SpeedUp.h"

UWORD	PtrPal[4]={0,0x1F,0,0};
UBYTE	ubReset;
UWORD	PtrPalBlack[4*8]={	0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,};


/************************************************************/
/*	Main													*/ 
/************************************************************/

void main(void)
{	

	UBYTE ubRun;

	// IT en cours
	ubLevelVBL=VBL_Level1;
	ubLevelHBL=HBL_Level1;

	// Invincible !!!
	
	ubInvincible=0;

	// Initialisation selon la GameBoy

	if(_cpu==CGB_TYPE)
	{	
		// Double la vitesse du CPU
		
		if(ubReset==0)
		{
			SpeedUp();
			ubReset=1;
		}


		// Registre Video Bank
		VBK_REG = 1;
		VBK_REG = 0;
	}
	else
	{
		while(1);
	}

	// Init Level
	ubLevelRom=1;
	ubLevel=1;

	// ** LCDC Register **
	DISPLAY_ON;
	HIDE_WIN;
	SHOW_BKG;
	SCX_REG=0;

	FixVBL(NULL);
  	set_interrupts(VBL_IFLAG);	// Enable VBL Interrupt
  	enable_interrupts();			// Start Interrupts
	
	move_win(7,144);
	SHOW_WIN;
			
	// Rom 3
	SWITCH_ROM_MBC1(3);
	
	// ** Bung ** //
	
	// met en place la palette bkg noir
	set_bkg_palette(0,8,&PtrPalBlack[0]);	

	// Met en place les tiles
	set_bkg_data(0,89,PtrLogoTile);

	// Affiche la Map du titre
	Set_Bkg_MapAttribut(32,18,PtrLogoMap,(UBYTE *)(0x9C00));

	// Affiche la Map du titre
	Set_Bkg_MapAttribut(32,18,PtrBlankMap,(UBYTE *)(0x9800));

	// met en place la palette bkg et sprite
	set_bkg_palette(0,8,&PtrLogoTilePal[0]);

	// Attente
	
	for(ubRun=144;ubRun>0;ubRun--)
	{
		wait_vbl_done();
		move_win(7,ubRun);
	}
	
	delay(4000);

	
	// ** Text 1

	move_win(7,144);

	// met en place la palette bkg noir
	set_bkg_palette(0,8,&PtrPalBlack[0]);	

	// Met en place les tiles
	set_bkg_data(0,89,PtrTextTile);

	// Affiche la Map du titre
	Set_Bkg_MapAttribut(20,18,PtrTextMap,(UBYTE *)(0x9800));

	// met en place la palette bkg et sprite
	set_bkg_palette(0,8,&PtrTextTilePal[0]);

	delay(8000);

	// ** Push Start To Play ** //

	SWITCH_ROM_MBC1(3);

	SHOW_BKG;

	// HBL Data
	STAT_REG=0x40U;
	LYC_REG=0;

	// met en place la palette bkg noir
	set_bkg_palette(0,8,&PtrPalBlack[0]);	

	// Met en place les tiles
	set_bkg_data(0,200,PtrCrazyTile);

	// Affiche la Map du titre
	Set_Bkg_MapAttribut(32,18,PtrCrazyMap,(UBYTE *)(0x9800));
		
	// met en place la palette bkg et sprite
	set_bkg_palette(0,8,&PtrCrazyTilePal[0]);	

	SHOW_SPRITES;
	SPRITES_8x8;

	// Sprite "PUSH DATA"
	set_sprite_data(0,7,PtrCrazySprite);
	
	// met en place la palette bkg et sprite
	set_sprite_palette(0,1,&PtrPal[0]);	

	set_sprite_tile(0,0);	// P
	set_sprite_tile(1,1);	// U
	set_sprite_tile(2,2);	// S
	set_sprite_tile(3,3);	// H
	set_sprite_tile(4,2);	// S
	set_sprite_tile(5,4);	// T
	set_sprite_tile(6,5);	// A
	set_sprite_tile(7,6);	// R
	set_sprite_tile(8,4);	// T

	move_sprite(0,50+8*0,120); 
	move_sprite(1,50+8*1,120);
	move_sprite(2,50+8*2,120);
	move_sprite(3,50+8*3,120);
	move_sprite(4,50+8*5,120);
	move_sprite(5,50+8*6,120);
	move_sprite(6,50+8*7,120);
	move_sprite(7,50+8*8,120);
	move_sprite(8,50+8*9,120);

	for(ubRun=0;ubRun<9;ubRun++)
	{
		set_sprite_prop(ubRun,PAL0);
	}

	// Efface les autres sprite
	for(ubRun=9;ubRun<40;ubRun++)
	{
		move_sprite(ubRun,0,0);
	}

	FixVBL(VBL_Title);
	FixHBL(HBL_Title);

  	set_interrupts(VBL_IFLAG|LCD_IFLAG);	// Enable VBL Interrupt
  	enable_interrupts();			// Start Interrupts

	waitpadup();	
	while(!(joypad()&J_START))
	{
		wait_vbl_done();
	}
	
	SWITCH_ROM_MBC1(ubLevelRom);
	
	waitpadup();

	disable_interrupts();
	
	// detruit les sprites utilisés
	for(ubRun=0;ubRun<9;ubRun++)
	{
		move_sprite(ubRun,0,0);
	}

	HIDE_SPRITES;
	
	// Window
	SHOW_WIN;

	// met en place la palette bkg noir
	set_bkg_palette(0,8,&PtrPalBlack[0]);	

	// Initialise l'argent
	Init_Money();

	// Affiche le Level en cours
	Show_Level();
	
	// Fixe la valeur de depart de l'IT HBL
	STAT_REG=0x40U;
	LYC_REG=0;
	
	// Initialisation
	Init_Sprite();
	Init_VMonster();
	Init_VOpa(10,70,START);
	Init_VWeapon();
	
	// Lance le Scroll
	Init_Scroll(START);

	// Attente d'une touche
	waitpadup();
	while(!(joypad()&J_START));
	waitpadup();

	// Positionne la fenetre
	move_win(7,144-8);
	
	// Sprite
	SHOW_SPRITES;
	SPRITES_8x8;
			
	// Authorise les ITs
	set_interrupts(VBL_IFLAG |LCD_IFLAG);
	enable_interrupts();

	while(1)
	{
		wait_vbl_done();
				
		Run_VOpa();
		Run_VWeapon();
		Run_VMonster();
	}
}

void Show_Level(void)
{
	move_win(7,0);

	Set_Bkg_MapAttribut(20,18,PtrWindowMap,(UBYTE *)(0x9C00));
	Show_Heart_Vopa();
	Show_Life_VOpa();
	Show_Money();
}

void Congratulation()
{		
	UBYTE ubRun;

	FixVBL(NULL);
	FixHBL(NULL);

	set_interrupts(VBL_IFLAG);

	SCX_REG=0;

	HIDE_SPRITES;
	SWITCH_ROM_MBC1(3);

	// ** Text 1
	move_win(167,0);

	// met en place la palette bkg noir
	set_bkg_palette(0,8,&PtrPalBlack[0]);	

	// Met en place les tiles
	set_bkg_data(0,89,PtrTextTile);

	// Affiche la Map du titre
	Set_Bkg_MapAttribut(20,18,PtrText2Map,(UBYTE *)(0x9C00));

	// Affiche la Map du titre
	Set_Bkg_MapAttribut(32,18,PtrBlankMap,(UBYTE *)(0x9800));

	// met en place la palette bkg et sprite
	set_bkg_palette(0,8,&PtrTextTilePal[0]);

	// Attente
	
	for(ubRun=167;ubRun>6;ubRun--)
	{
		wait_vbl_done();
		move_win(ubRun,0);
	}

	waitpadup();
	while(!(joypad()&J_START));
	waitpadup();
}

void NextLevel(void)
{
	ubLevel++;

	switch(ubLevel)
	{
		case 2:		
			ubLevelRom=5;
			ubLevelVBL=VBL_Level2;
			ubLevelHBL=HBL_Level2;
			break;
		case 3:		
			Congratulation();
			main();
			break;
	}

	SWITCH_ROM_MBC1(ubLevelRom);

	Stop_Scroll();
	HIDE_SPRITES;

	// met en place la palette bkg noir
	set_bkg_palette(0,8,&PtrPalBlack[0]);	
	Init_Scroll(RESET);
	Show_Level();
	// Charge la Palette 
	set_bkg_palette(0,8,&PtrTileLevel1CGBPal[0]);	

	// Attente d'une touche
	waitpadup();
	while(!(joypad()&J_START));
	waitpadup();
	
	set_interrupts(VBL_IFLAG|LCD_IFLAG);
	Init_Sprite();
	Init_VMonster();
	Init_VOpa(10,70,RESET);
	Init_VWeapon();
			
	// Window Remise a neuf
	move_win(7,144-8);

	SHOW_SPRITES;
}
