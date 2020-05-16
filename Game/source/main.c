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
int timereset;
int jugadores;
int dificultad;
int reset;

int main() {

	// Variables del main
	
	

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
	reset = 0;
	
	void delay(int x){ //delay = x ms
			int time = 0;

			while (x > time){
				x--;				
				//iprintf("\x1b[2;3H##########################");
			}
	}
	
	
	void Inicio () {
		reset = 0;
		MostrarJugadores();
		delay(50);
		touchRead(&PANT_DAT);

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
		delay(800); //delay para no detectar dos toques en la pantalla tactil
		MostrarDificultad();
		PANT_DAT.px = 0; //Inicializar x e y
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

	void juego1players () { //jokalari batentzako void-a
		int pushA = 1;
		/* Pushak (A, B, ARRIBA, ABAJO) tekla sakatuta mantenduz ez mugitzeko erabiltzan dira juegoren 4 voidetan 
		(juego1players,juego2players,juego3players,juego4players)*/
	
		//J1
		int j1 = 0; //finished(1) or not(0)
		int j1x = 5; //x pos of j1
		static int j1y = 40; //y pos of j1

		MostrarJuego(); //fondoa bistaratu

		//load sprites
		MostrarCar(1,j1x,j1y);
		MostrarCar(2,5,68);
		MostrarCar(3,5,96);
		MostrarCar(4,5,124);

		delay(2000); // delay bat hasteko

		//tenpZerbErrutEzarri();	
		timereset = 1; // Resetear reloj
		while (j1 == 0 && reset == 0) {
			
			
			if(TeclaPulsada() == A && DetectarTecla() == pushA){
                    		if (pushA == 1){
                        		BorrarCar(1,j1x,40);
                        		MostrarCar(1,j1x+5,40);
                        		j1x = j1x+5;
                       	 		pushA = 0;
                        		if (j1x >= 220)					
                        		{
                            			BorrarCar(1,j1x,40);
                            			j1 = 1;                            	
                        		}
                    		}
                    		else
                    		{
                       			pushA = 1;
                    		}
                    		
			}		
		}
		timereset = 0;
		estado = INICIO;
	
	}

	void juego2players () { // 2 jokalarientzako void-a
		int pushA = 1;
		int pushB = 1;
		
		//J1
		int j1 = 0; //finished(1) or not(0)
		int j1x = 5; //x pos of j1
		static int j1y = 40; //y pos of j1

		//J2
		int j2 = 0; //finished(1) or not(0)
		int j2x = 5; //x pos of j2
		static int j2y = 68; //y pos of j2

		MostrarJuego();
	
		//load sprites
		MostrarCar(1,j1x,j1y);
		MostrarCar(2,j2x,j2y);
		MostrarCar(3,5,96);
		MostrarCar(4,5,124);

		//tenpZerbErrutEzarri();
		timereset = 1;
		while ((j1 == 0 || j2 == 0)&& reset == 0) {
			
			if(TeclaPulsada() == A){
                		if(DetectarTecla() == pushA){
                    			if (pushA == 1){
                        			BorrarCar(1,j1x,40);
                        			MostrarCar(1,j1x+1,40);
                        			j1x = j1x+5;
                       	 			pushA = 0;
                        			if (j1x >= 220)					
                        			{
                            				//iprintf("\x1b[10;5HPOS: %d",j1x);
                            				BorrarCar(1,j1x,40);
                            				j1 = 1;
                            	
                        			}
                    			}
                    			else
                    			{
                       				pushA = 1;
                    			}
                    	
          		      	}	
			}

			if(TeclaPulsada() == B){
	         		if(DetectarTecla() == pushB){
	                    		if (pushB == 1){
	                        			BorrarCar(2,j2x,j2y);
	                        			MostrarCar(2,j2x+1,j2y);
	                        			j2x = j2x+5;
	                        			pushB = 0;
	                        			if (j2x >= 220)					
	                       				{
	                           				BorrarCar(2,j2x,j2y);
	                           				j2 = 1;
	                            
	                        			}
	                    		}
	                    		else
	                    		{
	                        		pushB = 1;
	                    		}
	                       	}	    		
			}
			//IA
		}
		timereset = 0;
		estado = INICIO; 

	}



void juego3players () { // 3 jokalarientzako void-a
		int pushA = 1;
		int pushB = 1;
		int pushARRIBA = 1;

		//J1
		int j1 = 0; //finished(1) or not(0)
		int j1x = 5; //x pos of j1
		static int j1y = 40; //y pos of j1

		//J2
		int j2 = 0; //finished(1) or not(0)
		int j2x = 5; //x pos of j2
		static int j2y = 68; //y pos of j2

		//J3
		int j3 = 0; //finished(1) or not(0)
		int j3x = 5; //x pos of j3
		static int j3y = 96; //y pos of j3

		MostrarJuego();

		//load sprites
		MostrarCar(1,j1x,j1y);
		MostrarCar(2,j2x,j2y);
		MostrarCar(3,j3x,j3y);
		MostrarCar(4,5,124);

	
		//tenpZerbErrutEzarri();
		timereset = 1;
		while ((j1 == 0 || j2 == 0 || j3 == 0)&& reset == 0) {
			
			if(TeclaPulsada() == A){
                		if(DetectarTecla() == pushA){
                    			if (pushA == 1){
                        			BorrarCar(1,j1x,40);
                        			MostrarCar(1,j1x+1,40);
                        			j1x = j1x+5;
                       	 			pushA = 0;
                        			if (j1x >= 220)					
                        			{
                            				//iprintf("\x1b[10;5HPOS: %d",j1x);
                            				BorrarCar(1,j1x,40);
                            				j1 = 1;
                            	
                        			}
                    			}
                    			else
                    			{
                       				pushA = 1;
                    			}
                    	
          		      	}	
			}

			if(TeclaPulsada() == B){
	         		if(DetectarTecla() == pushB){
	                    		if (pushB == 1){
	                        			BorrarCar(2,j2x,j2y);
	                        			MostrarCar(2,j2x+1,j2y);
	                        			j2x = j2x+5;
	                        			pushB = 0;
	                        			if (j2x >= 220)					
	                       				{
	                           				BorrarCar(2,j2x,j2y);
	                           				j2 = 1;
	                            
	                        			}
	                    		}
	                    		else
	                    		{
	                        		pushB = 1;
	                    		}
	                       	}	    		
			}

			if(TeclaPulsada() == ARRIBA){
	         		if(DetectarTecla() == pushARRIBA){
	                    		if (pushARRIBA == 1){
	                        		BorrarCar(3,j3x,j3y);
	                        		MostrarCar(3,j3x+1,j3y);
	                        		j3x = j3x+5;
	                        		pushARRIBA = 0;
	                        		if (j3x >= 220)					
	                        		{
	                            			BorrarCar(3,j3x,j3y);
	                            			j3 = 1;	                            
	                        		}
	                    		}
	                    		else
	                    		{
	                        		pushARRIBA = 1;
	                    		}
	                    
	                	}    		
			}
			//IA
			
		}
		timereset = 0;
		estado = INICIO;
			
	}
void juego4players () { // 4 jokalarientzako void-a
		int pushA = 1;
		int pushB = 1;
		int pushARRIBA = 1;
		int pushABAJO =1;
		
		//J1
		int j1 = 0; //finished(1) or not(0)
		int j1x = 5; //x pos of j1
		static int j1y = 40; //y pos of j1
		int j1time = 0;

		//J2
		int j2 = 0; //finished(1) or not(0)
		int j2x = 5; //x pos of j2
		static int j2y = 68; //y pos of j2

		//J3
		int j3 = 0; //finished(1) or not(0)
		int j3x = 5; //x pos of j3
		static int j3y = 96; //y pos of j3

		//J4
		int j4 = 0; //finished(1) or not(0)
		int j4x = 5; //x pos of j4
		static int j4y = 124; //y pos of j4

		MostrarJuego();

		//load sprites
		MostrarCar(1,j1x,j1y);
		MostrarCar(2,j2x,j2y);
		MostrarCar(3,j3x,j3y);
		MostrarCar(4,j4x,j4y);
		
		//tenpZerbErrutEzarri();
		timereset = 1;
		while ((j1 == 0 || j2 == 0 || j3 == 0 || j4 == 0) && reset == 0 ) {
			
			if(TeclaPulsada() == A){
                		if(DetectarTecla() == pushA){
                    			if (pushA == 1){
                        			BorrarCar(1,j1x,40);
                        			MostrarCar(1,j1x+1,40);
                        			j1x = j1x+5;
                       	 			pushA = 0;
                        			if (j1x >= 220)					
                        			{
                            				BorrarCar(1,j1x,40);
                            				j1 = 1;
                            	
                        			}
                    			}
                    			else
                    			{
                       				pushA = 1;
                    			}
                    	
          		      	}	
			}

			if(TeclaPulsada() == B){
	         		if(DetectarTecla() == pushB){
	                    		if (pushB == 1){
	                        			BorrarCar(2,j2x,j2y);
	                        			MostrarCar(2,j2x+1,j2y);
	                        			j2x = j2x+5;
	                        			pushB = 0;
	                        			if (j2x >= 220)					
	                       				{
	                           				BorrarCar(2,j2x,j2y);
	                           				j2 = 1;
	                            
	                        			}
	                    		}
	                    		else
	                    		{
	                        		pushB = 1;
	                    		}
	                       	}	    		
			}

			if(TeclaPulsada() == ARRIBA){
	         		if(DetectarTecla() == pushARRIBA){
	                    		if (pushARRIBA == 1){
	                        		BorrarCar(3,j3x,j3y);
	                        		MostrarCar(3,j3x+1,j3y);
	                        		j3x = j3x+5;
	                        		pushARRIBA = 0;
	                        		if (j3x >= 220)					
	                        		{
	                            			BorrarCar(3,j3x,j3y);
	                            			j3 = 1;	                            
	                        		}
	                    		}
	                    		else
	                    		{
	                        		pushARRIBA = 1;
	                    		}
	                    
	                	}    		
			}

			if(TeclaPulsada() == ABAJO){
	         		if(DetectarTecla() == pushABAJO){
	                    		if (pushABAJO == 1){
	                        		BorrarCar(4,j4x,j4y);
	                        		MostrarCar(4,j4x+1,j4y);
	                        		j4x = j4x+5;
	                        		pushABAJO = 0;
	                        		if (j4x >= 220)					
	                        		{
	                            			BorrarCar(4,j4x,80);
	                            			j4 = 1;
	                                       	}
	                    		}
	                    		else
	                    		{
	                      		  	pushABAJO = 1;
	                    		}
	                    
	                	}
	    		}
			
		}
		timereset = 0;
		estado = INICIO;
		
	}
	


	while(1)
	{
		switch (estado)
		{
		case INICIO:
			iprintf("\x1b[2;3H##########################");
			iprintf("\x1b[3;3H#####     INICIO     #####");
			iprintf("\x1b[4;3H##########################");
			iprintf("\x1b[10;3H                          ");
			iprintf("\x1b[12;3H                          ");
			iprintf("\x1b[20;2H   Seleccionar jugadores   ");
			Inicio();
			break;

		case CONFIG:
			iprintf("\x1b[2;3H##########################");
			iprintf("\x1b[3;3H#####   DIFICULTAD   #####");
			iprintf("\x1b[4;3H##########################");
			iprintf("\x1b[20;2H  Seleccionar Dificultad   ");
				
			Config();
			break;

		case JUEGO:
			iprintf("\x1b[2;3H##########################");
			iprintf("\x1b[3;3H#####      GAME      #####");
			iprintf("\x1b[4;3H##########################");

			iprintf("\x1b[6;3H#                        #");
			iprintf("\x1b[20;2H                           ");
			iprintf("\x1b[8;3H# J1 A      --  J2 B     #");
			iprintf("\x1b[10;3H# J3 ARRIBA --  J4 ABAJO #");
			iprintf("\x1b[12;3H#     SELECT PAUSA       #");
			iprintf("\x1b[14;3H#     START  MENU        #");
			iprintf("\x1b[16;3H##########################");

			
			if (jugadores == 1)
				juego1players();
			if (jugadores == 2)
				juego2players();
			if (jugadores == 3)
				juego3players();
			if (jugadores == 4)
				juego4players();
			break;
		default:
			break;
		}
	}
} 


