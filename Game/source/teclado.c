/*-------------------------------------
 teclado.c
-------------------------------------*/

// Añadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"


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
        int stop = 0;
        if (TeclaPulsada() == START) //MENU
        {	
                BorrarCar(1,0,0);
                BorrarCar(2,0,0);
                BorrarCar(3,0,0);
                BorrarCar(4,0,0);
                erakutsipause();
                while (stop == 0){
                        if(TeclaPulsada() == A){
                                // FONDO erakutsijokoa();				
                                stop = 1;
                        }	
                        if(TeclaPulsada() == B){
                                timereset = 0;
                                estado = JUEGO;			
                                stop = 1;
                        }
                }
        }

        if (TeclaPulsada() == SELECT) //PAUSA
        {
                while (stop == 0){
                        if(TeclaPulsada() == A){
                                stop = 1;
                        }
                }
        }
}


