/*---------------------------------------------------------------------------------
Este código se ha implementado basándose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>       	// time 

#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutservs.h"
#include "teclado.h"
#include "temporizadores.h"

//-----------------------------------------------------
// Variables globales
//-----------------------------------------------------

int estado;



int main() {

	// Variables del main
	//touchPosition pos_pantalla;

	//  Poner en marcha el motor gráfico 2D.
    	powerOn(POWER_ALL_2D);

     	// Establecer la pantalla inferior como principal, inicializar el sistema gráfico
     	// y configurar el sistema de fondos.
    	lcdMainOnBottom();
    	initVideo();
    	initFondos();

    	// Mostrar fondos en pantalla. 
    	MostrarPuerta();

	// Inicializar memoria de sprites y guardar en ella los sprites 
	initSpriteMem();
	guardarSpritesEnMemoria();

	// Establecer las paletas para los sprites 
	establecerPaletaPrincipal();

	// Para poder imprimir en pantalla (hacer trazas) 
	consoleDemoInit();
	
 	// Para inicializar el generador de números aleatorios en función de una semilla,
	// en este caso time(NULL). 
	// srand() sólo se suele activar una vez por ejecución y no devuelve ningún valor 
	//srand (time(NULL));
	interrupciones();

    
    
	void jugadores() {	
		erakutsijokalariak(); //fondoa bistaratu
		delay(50); //delay bat ukimen pantaila erabiltzerakoan bi ukimen ez irakurtzeko
		touchRead(&PANT_DAT); // pantaila irakurri

		//1 jokalari
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			jkop = 1;
			jokoa01(1); // Zailtasun egoera			
		}

		//2 jokalari
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			jkop = 2;
			jokoa01(1); // Zailtasun egoera			
		}
			
		//3 jokalari
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			jkop = 3;
			jokoa01(1); // Zailtasun egoera
		}
			
		//4 jokalari
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			jkop = 4;
			jokoa01(1); // Zailtasun egoera
		}
	
	}	
	estado = INICIO;

	while(1)
	{
		switch (estado)
		{
		case INICIO:
			iprintf("\x1b[20;2H   Seleccionar jugadores   ");		
			//void
			break;
		case CONFIG:

			break;
		case JUEGO:
			break;
		case PAUSA:
			break;	
		default:
			break;
		}
	}
} 


