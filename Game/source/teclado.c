/*-------------------------------------
 teclado.c
-------------------------------------*/

// Añadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

int reset;
int timereset;
int jugadores;
int dificultad;

//Esta función tiene que devolver si una tecla ha sido pulsada
int DetectarTecla() 
{
	if ((~TECLAS_DAT & 0x03FF)!=0) return 1;
	else return 0;
}

// Esta funcion tiene que devolver el valor de la tecla pulsada
int  TeclaPulsada() {
   // Devuelve el valor asociado a la tecla pulsada: 
   // A=0; B=1; Select=2; Start=3; Der=4; Izq=5;
   // Arriba=6; Abajo=7; R=8; L=9;
   // -1 en otros casos
   int tecla = (~TECLAS_DAT & 0x03FF);
        switch (tecla)
        {       case 1:
                        return A;
                case 2:
                        return B;
                case 4:
                        return SELECT;
                case 8:
                        return START;
                case 16:
                        return DCHA;
                case 32:
                        return IZDA;
                case 64:
                        return ARRIBA;
                case 128:
                        return ABAJO;
                case 256:
                        return R;
                case 512:
                        return L;
                default:
                        return -1;
        }

}


// Rutina de atencion a la interrupcion del teclado
void IntTec() {
        int stop = 0; //Se utiliza para salir de while
        if (TeclaPulsada() == START) //MENU
        {	
		iprintf("\x1b[2;3H##########################");
		iprintf("\x1b[3;3H#####      MENU      #####");
		iprintf("\x1b[4;3H##########################");
		iprintf("\x1b[6;3H                          ");
		iprintf("\x1b[20;2H                           ");
		iprintf("\x1b[8;3H                          ");
		iprintf("\x1b[10;3H  PULSA A PARA CONTINUAR  ");
		iprintf("\x1b[12;3H  PULSA B PARA REINICIAR  ");
		iprintf("\x1b[14;3H                          ");
		iprintf("\x1b[16;3H                          ");
                BorrarCar(1,0,0);
                BorrarCar(2,0,0);
                BorrarCar(3,0,0);
                BorrarCar(4,0,0);
                MostrarPausa();
                while (stop == 0){
                        if(TeclaPulsada() == A){
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
                                MostrarJuego();				
                                stop = 1;
                        }	
                        if(TeclaPulsada() == B){
                                timereset = 0;
				reset = 1;
				jugadores = 0;
				dificultad = 0;
                                estado = INICIO;			
                                stop = 1;
                        }
                }
        }

        if (TeclaPulsada() == SELECT) //PAUSA
        {
		iprintf("\x1b[2;3H##########################");
		iprintf("\x1b[3;3H#####      PAUSA     #####");
		iprintf("\x1b[4;3H##########################");
		iprintf("\x1b[6;3H                          ");
		iprintf("\x1b[20;2H                           ");
		iprintf("\x1b[8;3H                          ");
		iprintf("\x1b[10;3H  PULSA A PARA CONTINUAR  ");
		iprintf("\x1b[12;3H                          ");
		iprintf("\x1b[14;3H                          ");
		iprintf("\x1b[16;3H                          ");
                while (stop == 0){
                        if(TeclaPulsada() == A){
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
                                stop = 1;
                        }
                }
        }
}


