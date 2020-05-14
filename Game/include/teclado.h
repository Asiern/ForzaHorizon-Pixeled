/*-------------------------------------
teclado.h
-------------------------------------*/

extern int tecla; // variable para guardar el valor de la tecla pulsada

//Esta función tiene que devolver si una tecla ha sido pulsada
int DetectarTecla();

//Esta funci�n tiene que devolver el valor de la tecla pulsada
extern int TeclaPulsada();

//Rutina de atenci�n a la interrupci�n del teclado
extern void IntTec();

