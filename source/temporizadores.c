/*-------------------------------------
 temporizadores.c
-------------------------------------*/
// Añadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>

int seg = 0;
// Rutina de atención a la interrupción del temporizador
void IntTemp() {
    if (estado == PUERTA_CERRADA){
        time++;
        if (time >= 100){
            time = 0;
            seg++;
            iprintf("\x1b[10;5HTIMER: %d",seg);
        }
    }

    if (estado == PUERTA_ABIERTA){        
        if (time < 300){
            MostrarPuertaAbierta();
        }
        else{
            time = 0;
            estado = PUERTA_CERRADA;
        }
    }


}





