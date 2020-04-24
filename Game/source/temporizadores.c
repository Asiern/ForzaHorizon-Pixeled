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
        tik++;
        if (tik >= 100){
            tik = 0;
            seg++;
            iprintf("\x1b[10;5HTIMER: %d",seg);
        }
    }

    if (estado == PUERTA_ABIERTA){        
        if (tik < 300){
            MostrarPuertaAbierta();
        }
        else{
            tik = 0;
            estado = PUERTA_CERRADA;
        }
    }


}





