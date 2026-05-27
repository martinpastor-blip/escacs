#include "defines.h"
#include "taulell.h"
#include "includes.h"

Fitxa taulell[TAMANYTAULELL][TAMANYTAULELL];
Partida partida;


// Assigna una fitxa a una casella del taulell i actualitza el seu simbol 
void posarFitxa(int fila, int columna, ColorFitxa color, TipusFitxa tipus)
{
    taulell[fila][columna].color = color;
    taulell[fila][columna].tipus = tipus;

    if (tipus == TipusFitxa::BUIT)
    {
        taulell[fila][columna].simbol = " * ";
        return;
    }

