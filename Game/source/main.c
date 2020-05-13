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
	int jugadores;
	int dificultad;

	//  Poner en marcha el motor gráfico 2D.
    	powerOn(POWER_ALL_2D);

     	// Establecer la pantalla inferior como principal, inicializar el sistema gráfico
     	// y configurar el sistema de fondos.
    	lcdMainOnBottom();
    	initVideo();
    	initFondos();

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
  

	estado = INICIO;
	
	
	
	void Inicio () {	

		//erakutsijokalariak();
		delay(50);
		//touchRead(&PANT_DAT);

		//1 jugador
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			jugadores = 1;
			estado = CONFIG;		
		}

		//2 jugadores
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			jugadores = 2;
			estado = CONFIG;	
		}
			
		//3 jugadores
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			jugadores = 3;
			estado = CONFIG;
		}
			
		//4 jugadores
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			jugadores = 4;
			estado = CONFIG;
		}
	
	}

	void Config() {
		delay(800); //delay bat ukimen pantaila erabiltzerakoan bi ukimen ez irakurtzeko
		//Mostrar fondo
		PANT_DAT.px = 0; //Inicia;izar x e y
		PANT_DAT.py = 0;

		//iprintf("\x1b[23;5HAukeratu zailtasuna"); //Fix Height
		
		while (PANT_DAT.px == 0 && PANT_DAT.py == 0){
			touchRead(&PANT_DAT); //Leer panalla
		}
			
			
		//Facil
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 90 && PANT_DAT.py <= 111)){
			dificultad = 1;	
			estado = JUEGO;					
		}

		//Normal
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 124 && PANT_DAT.py <= 145)){
			dificultad = 2;
			estado = JUEGO;	
		}
			
		//Dificil
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 158 && PANT_DAT.py <= 179)){
			dificultad = 3;
			estado = JUEGO;
			
		}
	}


	void delay (int x){ //delay = x ms
			int time = 0;

			while (x > time){
				x--;				
				iprintf("\x1b[2;3H##########################");
			}
	}


	while(1)
	{
		switch (estado)
		{
		case INICIO:
			iprintf("\x1b[20;2H   Seleccionar jugadores   ");
			Inicio();
			break;

		case CONFIG:
			iprintf("\x1b[20;2H  Seleccionar Dificultad   ");	
			Config();
			break;

		case JUEGO:
			iprintf("\x1b[20;2H                                ");
			if (jugadores == 1)
				jokoa1players();
			if (jugadore == 2)
				jokoa2players();
			if (jugadore == 3)
				jokoa3players();
			if (jugadore == 4)
				jokoa4players();
			break;

		case PAUSA:
			break;	
		default:
			break;
		}
	}
} 


