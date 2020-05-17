/*-------------------------------------
 temporizadores.c
-------------------------------------*/
// Añadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>

int dificultad;
int jugadores;
int timereset;

int tik = 0;
static int seg=0;
int x = 5;
int x1 = 5;
int x2 = 5;
int x3 = 5;
int x4 = 5;

// Rutina de atención a la interrupción del temporizador
void IntTemp() {
	
	/* Esta rutina se utiliza para el control de los jugadores*/
	static int seg = 0;
	static int dec = 0;
	static int cont = 0; // Contador de movimiento
	static int speed1 = 10; //Dificultad Facil
	static int speed2 = 20; //Dificultad Normal
	static int speed3 = 30; //Dificultad Dificil
	
	if (timereset == 0){ //Reset al timer
		BorrarCar(1,0,0);
		BorrarCar(2,0,0);
		BorrarCar(3,0,0);
		BorrarCar(4,0,0);
		x = 5;
		x1 = 5;
		x2 = 5;
		x3 = 5;
		x4 = 5;
		seg = 0;
		dec = 0;
	}
	else{
		tik++; 
		if (tik==1)
		{
			dec++;
			if (dec == 100)
			{
				seg++;	
				dec=0; 	
				cont = 1;			
			}	
			tik=0;				
		}
		switch (jugadores){
			case 1:	//Para un jugador
				if (cont == 1 && dificultad != 0){
					if (x2 > 240){
						
						BorrarCar(2,0,0);
					}
					else{
						BorrarCar(2,x2,68);
						MostrarCar(2,x2+1,68);
						if (dificultad == 1){
							x2 = x2+speed1;}
						else if (dificultad == 2){
							x2 = x2+speed2;}
						else if (dificultad == 3){
							x2 = x2+speed3;	
						}
					}
				}
				if (cont == 1 && dificultad != 0){
					if (x3 > 240){
						BorrarCar(3,0,0);
					}
					else{
						BorrarCar(3,x3,96);
						MostrarCar(3,x3+1,96);
						if (dificultad == 1){
							x3 = x3 + speed1;}
						else if (dificultad == 2){
							x3 = x3+speed2;}
						else if (dificultad == 3){
							x3 = x3+speed3;	
						}
					}
				}
				if (cont == 1 && dificultad != 0){
					if (x4 > 240){
						
						BorrarCar(4,0,0);
					}
					else{
						BorrarCar(4,x4,124);
						MostrarCar(4,x4+1,124);
						if (dificultad == 1){
							x4 = x4+speed1;}
						else if (dificultad == 2){
							x4 = x4+speed2;}
						else if (dificultad == 3){
							x4 = x4+speed3;	
						}
					}
				}
				cont = 0;
			case 2: //Para 2 jugadores 
				if (cont == 1 && dificultad != 0){
					if (x3 > 240){
						
						BorrarCar(3,0,0);
					}
					else{
						BorrarCar(3,x3,96);
        					MostrarCar(3,x3+1,96);
						if (dificultad == 1){
							x3 = x3 + speed1;}
						else if (dificultad == 2){
							x3 = x3+speed2;}
						else if (dificultad == 3){
							x3 = x3+speed3;	
						}
					}
				}
				if (cont == 1 && dificultad != 0){
					if (x4 > 240){
						
						BorrarCar(4,0,0);
					}
					else{
						BorrarCar(4,x4,124);
						MostrarCar(4,x4+1,124);
						if (dificultad == 1){
							x4 = x4+speed1;}
						else if (dificultad == 2){
							x4 = x4+speed2;}
						else if (dificultad == 3){
							x4 = x4+speed3;	
						}
					}
				}
				
				cont = 0;
			case 3: //Para 3 jugadores 
				if (cont == 1 && dificultad != 0){
					if (x4 > 240){
						
						BorrarCar(4,0,0);
					}
					else{
						cont = 0;
						BorrarCar(4,x4,124);
						MostrarCar(4,x4+1,124);
						if (dificultad == 1){
							x4 = x4+speed1;}
						else if (dificultad == 2){
							x4 = x4+speed2;}
						else if (dificultad == 3){
							x4 = x4+speed3;	
						}
					}
				}
		
		}
	}


}





