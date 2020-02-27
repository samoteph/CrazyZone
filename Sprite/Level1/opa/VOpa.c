/************************************************************/
/*								 
/* Virtual Opa !!!						
/*								 
/************************************************************/

#ifndef	__VOPA
#define __VOPA

#include ".\sprite\Level1\opa\vopa.h"
#include ".\sprite\Level1\Engine\VEngine.c"
#include ".\sprite\Level1\Weapon\VWeapon.c"
#include ".\sprite\Level1\Monster\VMonster.c"

/************************************************************/
/* Init_VOpa						
/* Initialise Opa Virtuel
/************************************************************/

void Init_VOpa(UBYTE ubPosX,UBYTE ubPosY,UBYTE start)
{
	set_sprite_data(DATA_OFFSET_OPA,DATA_WIDTH_OPA,PtrOpa);

	move_sprite(SPRITE_OFFSET_OPA+0,0,0);
	move_sprite(SPRITE_OFFSET_OPA+1,0,0);
	move_sprite(SPRITE_OFFSET_OPA+2,0,0);
	move_sprite(SPRITE_OFFSET_OPA+3,0,0);

	set_sprite_tile(SPRITE_OFFSET_OPA+0,DATA_OFFSET_OPA+0);
	set_sprite_tile(SPRITE_OFFSET_OPA+1,DATA_OFFSET_OPA+1);
	set_sprite_tile(SPRITE_OFFSET_OPA+2,DATA_OFFSET_OPA+2);
	set_sprite_tile(SPRITE_OFFSET_OPA+3,DATA_OFFSET_OPA+3);

	set_sprite_prop(SPRITE_OFFSET_OPA+0,PAL0);	
	set_sprite_prop(SPRITE_OFFSET_OPA+1,PAL1);	
	set_sprite_prop(SPRITE_OFFSET_OPA+2,PAL3);	
	set_sprite_prop(SPRITE_OFFSET_OPA+3,PAL2);	

	// Bouton non presse
	ubPressA=0;
		
	VOpa.ubPosX=ubPosX;
	VOpa.ubPosY=ubPosY;

	VOpa.ubRectX=RECT_X_VOPA;
	VOpa.ubRectY=RECT_Y_VOPA;
	VOpa.ubRectW=RECT_W_VOPA;
	VOpa.ubRectH=RECT_H_VOPA;

	VOpa.ubCollision=0;

	// Puissance de feu (Opa peut être considere comme une arme)
	VOpa.ubData[0]=0;

	Init_VEngine();
	Init_VWeapon();

	if(start==START)
	{
		Init_Life();
		Show_Heart_VOpa();
		Show_Life_VOpa();
	}
}

/************************************************************/
/* Run_VOpa()												
/* Initialise Opa Virtuel
/************************************************************/

void Run_VOpa()
{

	UBYTE joy=joypad();
	UBYTE data;
	UBYTE startx,starty;
	UBYTE OldScroll;

	// Opa En Cours d'explosion
	if(VOpa.ubCollision==0xFF)
	{
		// 0xFF = En cours de destruction
		Run_VExplodeOpa(&VOpa);
		return;
	}

	// Collision avec monstre
	if(Run_VCollision(&VOpa)!=0)
	{
		// sinon on paume un coeur
		Dec_Heart_VOpa();
	}						

	// ** Detection des objets sous Opa ** //

	data=GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA/2),VOpa.ubPosY+(RECT_Y_VOPA+RECT_H_VOPA/2)); 
	
	// si out alors prochain level
	
	if(data>12 && data<17)
	{
		NextLevel();
	}

	// si Pic alors destruction de Opa
	
	if(data==11 || data==12)
	{
		Dec_Heart_VOpa();
	}

	// si Dime alors Opa Ramasse

	if(data>27 && data<32)
	{
		startx=VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA/2);
		starty=VOpa.ubPosY+(RECT_Y_VOPA+RECT_H_VOPA/2);
		
		if(data==29)
		{
			starty-=8;
		}
		else if(data==30)
		{
			startx-=8;
		}
		else if(data==31)
		{
			startx-=8;
			starty-=8;
		}

		Set2x2VSpriteMap(startx,starty);
		Add_Money();

	}

	// ** Recule en cas de collision à droite avec le décor **

	if(GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA),VOpa.ubPosY+RECT_Y_VOPA)>=32 || GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA),VOpa.ubPosY+(RECT_Y_VOPA+RECT_H_VOPA))>=32)
	{
		VOpa.ubPosX=VOpa.ubPosX-1;
		if(VOpa.ubPosX<8)
		{
			// Passe a la vie suivante
			ubHeart=1;
			Dec_Heart_VOpa();
		}
	}

	// ** collision en haut **

	if(joy&J_UP)
	{
		if(GetVSpriteMap(VOpa.ubPosX+RECT_X_VOPA,VOpa.ubPosY+(RECT_Y_VOPA-ubSpeedEngineY))<32 && GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA),VOpa.ubPosY+(RECT_Y_VOPA-ubSpeedEngineY))<32)
		{
			VOpa.ubPosY-=ubSpeedEngineY;
		}

	}

	// ** collision en bas **

	else if(joy&J_DOWN)
	{
		if(GetVSpriteMap(VOpa.ubPosX+RECT_X_VOPA,VOpa.ubPosY+(RECT_Y_VOPA+RECT_H_VOPA+ubSpeedEngineY))<32 && GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA),VOpa.ubPosY+(RECT_Y_VOPA+RECT_H_VOPA+ubSpeedEngineY))<32)
		{
			VOpa.ubPosY+=ubSpeedEngineY;
		}
	}
	
	// ** collision a gauche **

	if(joy&J_LEFT)
	{
		if(GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA-ubSpeedEngineX),VOpa.ubPosY+RECT_Y_VOPA)<32 && GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA-ubSpeedEngineX),VOpa.ubPosY+(RECT_Y_VOPA+RECT_H_VOPA))<32)
		{
			VOpa.ubPosX-=ubSpeedEngineX;
		}
	}

	// ** collision a droite **

	else if(joy&J_RIGHT)
	{
		if(GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA+ubSpeedEngineX),VOpa.ubPosY+RECT_Y_VOPA)<32 && GetVSpriteMap(VOpa.ubPosX+(RECT_X_VOPA+RECT_W_VOPA+ubSpeedEngineX),VOpa.ubPosY+(RECT_Y_VOPA+RECT_H_VOPA))<32)
		{
			VOpa.ubPosX+=ubSpeedEngineX;
		}
	}
		
	// ** fixe le cadre de Opa ** //
	
	if(VOpa.ubPosX<SPRITE_WIN_LEFT)
	{
		VOpa.ubPosX=SPRITE_WIN_LEFT;
	}
	
	if(VOpa.ubPosX>(SPRITE_WIN_RIGHT-8))
	{
		VOpa.ubPosX=(SPRITE_WIN_RIGHT-8);
	}

	if(VOpa.ubPosY<SPRITE_WIN_UP)
	{
		VOpa.ubPosY=SPRITE_WIN_UP;
	}

	if(VOpa.ubPosY>(SPRITE_WIN_DOWN-4))
	{
		VOpa.ubPosY=(SPRITE_WIN_DOWN-4);
	}

	// ** deplacement **

	if(ubVanished==0)
	{
		// Affichage Opa
		move_sprite(SPRITE_OFFSET_OPA+0,VOpa.ubPosX,VOpa.ubPosY);
		move_sprite(SPRITE_OFFSET_OPA+2,VOpa.ubPosX+8,VOpa.ubPosY);
		move_sprite(SPRITE_OFFSET_OPA+1,VOpa.ubPosX,VOpa.ubPosY+8);
		move_sprite(SPRITE_OFFSET_OPA+3,VOpa.ubPosX+8,VOpa.ubPosY+8);
	}
	else
	{
		if((ubTimeVanished&0x02)==0)
		{
			move_sprite(SPRITE_OFFSET_OPA+0,0,0);
			move_sprite(SPRITE_OFFSET_OPA+2,0,0);
			move_sprite(SPRITE_OFFSET_OPA+1,0,0);
			move_sprite(SPRITE_OFFSET_OPA+3,0,0);
		}
		else
		{
			move_sprite(SPRITE_OFFSET_OPA+0,VOpa.ubPosX,VOpa.ubPosY);
			move_sprite(SPRITE_OFFSET_OPA+2,VOpa.ubPosX+8,VOpa.ubPosY);
			move_sprite(SPRITE_OFFSET_OPA+1,VOpa.ubPosX,VOpa.ubPosY+8);
			move_sprite(SPRITE_OFFSET_OPA+3,VOpa.ubPosX+8,VOpa.ubPosY+8);
			Run_VEngine();	
		}
		
		ubTimeVanished--;
		if(ubTimeVanished==0)
		{
			ubVanished=0;
		}
	}

	// ** Il Fonctionne le Moteur... **
	Run_VEngine();	


	// ** Gestion des boutons ** 

	// Bouton Fire
	if(!(joy&J_A))
	{
			ubPressA=0;
	}
	else
	{
		if(ubPressA==0)
		{
			ubPressA=1;
			
			Add_VWeapon();
		}
	}

	// Bouton Select
	
	// ** PAUSE **

	if(joy&J_START)
	{
		// Pause le Scroll
		
		OldScroll=StartScroll;
		StartScroll=0;
				
		waitpadup();
		
		// All Sound Off
	  	NR52_REG = 0x00;

		while(!(joypad()&J_START));
		waitpadup();

		// All Sound On
	  	NR52_REG = 0x80;
 	 	NR50_REG = 0x77;				//  %01110111
  		NR51_REG = 0xff;				//  %11111111

		StartScroll=OldScroll;

		return;
	}

	// Changement de Moteur

	if((joy&J_B))
	{
		Init_VSmallEngine();
	}

}

/************************************************************/
/* Dec_Heart_VOpa()												
/* 
/************************************************************/

UBYTE ubLifeMap[1];
UBYTE ubHeartMap[5];

void Init_Life()
{
	// Nombre de Coeur

		ubHeart=2;
		ubMaxHeart=2;
		ubVanished=0;
		
		// Nombre de Vie
		ubLife=1;
}

void Dec_Heart_VOpa()
{
	if(ubInvincible==1 || ubVanished==1)
	{
		return;
	}
	
	ubHeart--;
	Show_Heart_VOpa();

	if(ubHeart!=0x00)
	{
		// Clignote
		ubVanished=1;
		ubTimeVanished=4*20;
	}
	else
	{
		// 1 vie en moins donc explosion ( qui renvoi à Dec_Life_VOpa)
		ubVanished=0;
		
		Init_VExplodeOpa();
	}
}

UBYTE GetReady[]={79,77,92,70,90,77,73,76,97,99};
UBYTE GameOver[]={79,73,85,77,70,87,93,77,90,99};
UBYTE BlankLine[]={70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70};

void Dec_Life_VOpa()
{
	if(ubLife!=0x00)
	{
		// Affiche La Vie en moins
		ubLife--;
		
		Show_Life_VOpa();
				
		// Puis Arrêt des Hostilités

		Stop_Scroll();

		HIDE_SPRITES;

		// 2em ecran "Get Ready"
		
		ubHeart=ubMaxHeart;		
		Show_Heart_Vopa();
		Show_Life_VOpa();
		
		move_win(7,0);

		// Attente d'une touche
		waitpadup();
		while(!(joypad()&J_START));
		waitpadup();
		
		Init_Scroll(RESET);
		set_interrupts(VBL_IFLAG |LCD_IFLAG);
		Init_Sprite();
		Init_VMonster();
		Init_VOpa(10,70,RESET);
		Init_VWeapon();
				
		// Window Remise a neuf
		move_win(7,144-8);

		SHOW_SPRITES;
		
	}
	else
	{
		Stop_Scroll();

		HIDE_SPRITES;

		// 2em ecran "Game Over!"
		
		set_win_tiles(0,3,20,1,(unsigned char *)BlankLine);
		set_win_tiles(0,5,20,1,(unsigned char *)BlankLine);
		set_win_tiles(5,9,10,1,(unsigned char *)GameOver);

		ubHeart=ubMaxHeart;		
		Show_Heart_Vopa();
		Show_Life_VOpa();

		move_win(7,0);

		// Attente d'une touche

		waitpadup();
		while(!(joypad()&J_START));
		waitpadup();

		// GameOver puis redemarrage
		main();		
	}
}

void Show_Heart_VOpa()
{
	UBYTE ubRun=0;
	
	// Les coeur pleins
	while(ubRun<ubHeart)
	{
		ubHeartMap[ubRun]=47;
		ubRun++;
	}
	
	// Les coeur Vides
	
	while(ubRun<ubMaxHeart)
	{
		ubHeartMap[ubRun]=48;
		ubRun++;
	}

	while(ubRun<5)
	{
		ubHeartMap[ubRun]=70;
		ubRun++;
	}

	set_win_tiles(1,0,5,1,(unsigned char *)ubHeartMap);
}

void Show_Life_VOpa()
{
	ubLifeMap[0]=51+ubLife;
	set_win_tiles(17,0,1,1,(unsigned char *)ubLifeMap);
}

/************************************************************/
/* Init_Money()												
/* Ajoute 1 Piece au compteur
/************************************************************/

void Init_Money()
{
	UBYTE ubRun;
	
	for(ubRun=0;ubRun<5;ubRun++)
	{
		ubMoney[ubRun]=51;
	}

	uwMoneyValue=0;
}

/************************************************************/
/* Show_Money()												
/* Affiche les Piece au compteur
/************************************************************/

void Show_Money()
{
	set_win_tiles(8,0,4,1,(unsigned char *)ubMoney);
}

/************************************************************/
/* Add_Money()												
/* Ajoute 1 Piece au compteur
/************************************************************/

void Add_Money()
{
	BYTE bRun;	

	ubMoney[3]++;
	uwMoneyValue++;
	
	for(bRun=3;bRun>0;bRun--)
	{
		if(ubMoney[bRun]==51+10)
		{
			ubMoney[bRun]=51;
			ubMoney[bRun-1]++;
		}
		else
		{
			break;
		}
	}

	Show_Money();

	// Ajoute 1 vie au bout de 99 pieces
	
	if(ubMoney[3]==51+9 && ubMoney[2]==51+9)
	{
		if(ubLife<9)
		{
			ubLife++;
			Show_Life_VOpa();
		}
	}

}

#endif


