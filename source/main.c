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
	touchPosition pos_pantalla;

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
	srand (time(NULL));

    
    
// ...
	estado = PUERTA_ABIERTA;

	while(1)
	{
		if(estado == PUERTA_CERRADA){
                if(TeclaPulsada() == SELECT){
                    MostrarPuertaAbierta();
					estado == PUERTA_ABIERTA;
                }
        }
        else if(estado == PUERTA_ABIERTA){
                    touchRead(&pos_pantalla);
            		if(pos_pantalla.px!=0 && pos_pantalla.py!=0){
                    MostrarPuerta();
					estado == PUERTA_CERRADA;
                }
        }
	}
} 


