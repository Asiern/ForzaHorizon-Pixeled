/*---------------------------------------------------------------------------------
Este código se ha implementado basándose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>			//librería desarrollada para la nds
#include <stdio.h>			//librería estandar de c que define las funciones estandar de entrada y salida
#include <stdlib.h>			//librería estandar de c para hacer reservas de memoria y conversión de números
#include <unistd.h>			//librería para asegurar la compatibilidad entre sistemas operativos
#include "sprites.h"
#include "defines.h"

u16* gfxRombo;
u16* gfxRomboGrande;
u16* gfxCar;


/* Inicializar la memoria de Sprites. */
void initSpriteMem() {

	//int i;
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	gfxRombo =    oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxRomboGrande = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxCar = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

}



/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
void establecerPaletaPrincipal() {
                                         // 0: TRANSPARENTE
  SPRITE_PALETTE[0] = RGB15(0,0,0);
SPRITE_PALETTE[1] = RGB15(4,0,0);
SPRITE_PALETTE[2] = RGB15(4,0,0);
SPRITE_PALETTE[3] = RGB15(4,0,0);
SPRITE_PALETTE[4] = RGB15(4,0,0);
SPRITE_PALETTE[5] = RGB15(19,17,17);
SPRITE_PALETTE[6] = RGB15(19,17,17);
SPRITE_PALETTE[7] = RGB15(4,0,0);
SPRITE_PALETTE[8] = RGB15(4,0,0);
SPRITE_PALETTE[9] = RGB15(4,0,0);
SPRITE_PALETTE[10] = RGB15(31,16,12);
SPRITE_PALETTE[11] = RGB15(6,2,1);
SPRITE_PALETTE[12] = RGB15(4,1,0);
SPRITE_PALETTE[13] = RGB15(31,16,13);
SPRITE_PALETTE[14] = RGB15(28,7,4);
SPRITE_PALETTE[15] = RGB15(0,26,26);
SPRITE_PALETTE[16] = RGB15(0,2,2);
SPRITE_PALETTE[17] = RGB15(21,31,31);
SPRITE_PALETTE[18] = RGB15(31,16,13);
SPRITE_PALETTE[19] = RGB15(0,6,6);
SPRITE_PALETTE[20] = RGB15(0,31,31);
SPRITE_PALETTE[21] = RGB15(4,0,0);
SPRITE_PALETTE[22] = RGB15(4,0,0);
SPRITE_PALETTE[23] = RGB15(4,0,0);
SPRITE_PALETTE[24] = RGB15(5,0,0);
SPRITE_PALETTE[25] = RGB15(12,0,0);
SPRITE_PALETTE[26] = RGB15(2,0,0);
SPRITE_PALETTE[27] = RGB15(4,0,0);
SPRITE_PALETTE[28] = RGB15(6,0,0);
SPRITE_PALETTE[29] = RGB15(9,4,4);
SPRITE_PALETTE[30] = RGB15(5,0,0);
SPRITE_PALETTE[31] = RGB15(5,0,0);
SPRITE_PALETTE[32] = RGB15(9,4,4);
SPRITE_PALETTE[33] = RGB15(4,0,0);
SPRITE_PALETTE[34] = RGB15(4,0,0);
SPRITE_PALETTE[35] = RGB15(3,0,0);
SPRITE_PALETTE[36] = RGB15(3,0,0);
SPRITE_PALETTE[37] = RGB15(2,0,0);
SPRITE_PALETTE[38] = RGB15(2,0,0);
SPRITE_PALETTE[39] = RGB15(2,7,7);
SPRITE_PALETTE[40] = RGB15(0,0,0);
SPRITE_PALETTE[41] = RGB15(6,0,0);
SPRITE_PALETTE[42] = RGB15(5,0,0);
SPRITE_PALETTE[43] = RGB15(5,0,0);
SPRITE_PALETTE[44] = RGB15(8,0,0);
SPRITE_PALETTE[45] = RGB15(4,0,0);
SPRITE_PALETTE[46] = RGB15(4,0,0);
SPRITE_PALETTE[47] = RGB15(4,0,0);
SPRITE_PALETTE[48] = RGB15(4,0,0);
SPRITE_PALETTE[49] = RGB15(4,0,0);
SPRITE_PALETTE[50] = RGB15(6,0,0);

}


/* Dibujado de un Sprite de 16x16 pixels */

/* Debido al funcionamiento de los bancos de memoria, las primeras cuatro filas 
 * forman el cuadrante superior izquiero, las siguientes, el cuadrante superior 
 * derecho, las siguientes el cuadrante inferior izquierdo y las últimas cuatro
 * filas, el cuadrante inferior derecho, como se muestra al lado.
 */


u8 Rombo[256] = 
{
	0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,5,	//	0,0,0,0,0,0,5,5, 5,5,0,0,0,0,0,0,
	0,0,0,0,5,5,5,5,0,0,0,5,5,5,5,5,	//	0,0,0,0,0,5,5,5, 5,5,5,0,0,0,0,0,
	0,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,	//	0,0,0,0,5,5,5,5, 5,5,5,5,0,0,0,0,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	//	0,0,0,5,5,5,5,5, 5,5,5,5,5,0,0,0,
 
	5,5,0,0,0,0,0,0,5,5,5,0,0,0,0,0,	//	0,0,5,5,5,5,5,5, 5,5,5,5,5,5,0,0,
	5,5,5,5,0,0,0,0,5,5,5,5,5,0,0,0,	//	0,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,0,
	5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,0,	//	5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	//	5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,	//	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,	//	0,0,1,1,1,1,1,1, 1,1,1,1,1,1,0,0,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//	0,0,0,1,1,1,1,1, 1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,	//	0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0,
	1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,	//	0,0,0,0,0,1,1,1, 1,1,1,0,0,0,0,0,
	1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,	//	0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,
};

/* Dibujado de un Sprite de 32x32 pixels */

u8 RomboGrande[1024] = 
{
	0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,5,0,0,0,0,5,5,5,5,0,0,0,5,5,5,5,5,0,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	
 
	5,5,0,0,0,0,0,0,5,5,5,0,0,0,0,0,5,5,5,5,0,0,0,0,5,5,5,5,5,0,0,0,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,

	0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,0,0,0,5,5,5,5,5,0,0,0,0,5,5,5,5,0,0,0,0,0,5,5,5,0,0,0,0,0,0,5,5,	

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,0,0,5,5,5,5,5,0,0,0,5,5,5,5,0,0,0,0,5,5,5,0,0,0,0,0,5,5,0,0,0,0,0,0,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,	
};

u8 Car[1024] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,1,3,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,1,5,6,2,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,3,3,1,1,2,1,1,3,1,2,2,1,8,9,9,9,9,9,9,9,9,10,10,10,10,11,10,9,9,10,10,10,10,12,9,10,9,13,10,14,14,9,10,10,9,10,14,14,14,9,10,14,9,14,14,14,9,10,14,14,9,14,14,14,9,14,14,14,9,9,9,9,9,9,9,9,15,15,15,15,16,15,15,17,16,16,16,16,16,16,15,15,10,10,10,10,10,10,16,16,14,14,14,14,14,14,10,18,14,14,14,14,14,14,14,10,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,9,9,9,9,9,9,9,9,15,19,16,16,16,10,10,10,15,16,20,20,16,10,10,10,16,20,17,17,20,16,10,14,10,16,17,20,20,16,10,14,10,16,20,20,20,20,16,14,10,16,20,20,20,20,16,14,14,16,20,20,20,20,16,14,21,9,9,9,9,22,3,1,10,10,10,9,10,9,23,7,10,10,10,9,10,10,9,24,14,14,14,10,9,14,10,9,14,14,14,14,10,9,14,21,14,14,14,14,10,9,14,9,14,14,14,14,14,9,14,9,14,14,14,14,14,9,14,9,9,14,14,14,9,14,14,14,9,14,14,14,9,25,14,14,9,25,14,14,14,9,25,14,9,25,25,14,14,9,25,25,9,25,25,25,25,26,9,25,27,25,25,25,25,28,25,9,29,9,9,9,9,30,30,31,32,33,34,33,35,36,37,38,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,25,14,14,14,14,14,14,25,25,25,25,25,25,25,25,16,16,16,16,16,16,16,16,15,17,15,15,15,15,16,15,15,15,21,9,9,9,9,9,9,9,14,16,20,20,20,20,16,14,25,16,20,20,20,20,16,14,25,16,20,20,20,20,16,14,25,16,20,20,20,16,25,14,16,20,20,20,20,16,25,14,15,16,20,20,16,25,25,25,15,39,16,16,40,25,25,25,9,41,42,9,9,9,9,9,14,14,14,14,14,9,14,9,14,14,14,14,14,9,14,9,14,14,14,14,25,9,14,9,14,14,14,14,25,9,14,9,14,14,14,25,9,14,25,9,25,25,25,9,25,25,9,43,25,25,44,9,25,9,45,3,9,9,9,9,46,47,3,1,32,33,33,33,35,35,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,48,49,2,3,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,50,1,2,2,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/* Para cada Sprite que se quiera llevar a pantalla hay que hacer una de estas funciones. */

void BorrarRombo(int indice, int x, int y) {
oamSet(&oamMain, //main graphics engine context
	indice,  //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRombo,//+16*16/2, 	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	true,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain); 
}

void MostrarRombo (int indice, int x, int y){ 
oamSet(&oamMain, //main graphics engine context
	indice,  //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRombo,//+16*16/2, 	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	false,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain);  
}

void BorrarRomboGrande(int x, int y){
oamSet(&oamMain, //main graphics engine context
	127,     //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRomboGrande,//+16*16/2,	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	true,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain); 
}

void MostrarRomboGrande (int x, int y){
oamSet(&oamMain, //main graphics engine context
	127,     //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRomboGrande,//+16*16/2,	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	false,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain);  
}

void MostrarCar (int indice, int x, int y){
oamSet(&oamMain, //main graphics engine context
	indice,     //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_32x32,     
	SpriteColorFormat_256Color, 
	gfxCar,//+16*16/2,	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	false,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain);  
}
void BorrarCar(int indice, int x, int y){
oamSet(&oamMain, //main graphics engine context
	indice,     //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_32x32,     
	SpriteColorFormat_256Color, 
	gfxCar,//+16*16/2,	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	true,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain); 
}

void guardarSpritesEnMemoria(){ 
	
int i;
	//para sprites de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxRombo[i] = Rombo[i*2] | (Rombo[(i*2)+1]<<8);				
	}
	//para sprites de 32*32
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxRomboGrande[i] = RomboGrande[i*2] | (RomboGrande[(i*2)+1]<<8);				
	}

	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxCar[i] = Car[i*2] | (Car[(i*2)+1]<<8);				
	}
}



