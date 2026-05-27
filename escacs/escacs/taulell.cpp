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

    if (color == ColorFitxa::BLANC)
    {
        if (tipus == TipusFitxa::PEO)
        {
            taulell[fila][columna].simbol = " P ";
        }
        if (tipus == TipusFitxa::TORRE)
        {
            taulell[fila][columna].simbol = " T ";
        }
        if (tipus == TipusFitxa::CAVALL)
        {
            taulell[fila][columna].simbol = " H ";
        }
        if (tipus == TipusFitxa::ALFIL)
        {
            taulell[fila][columna].simbol = " B ";
        }
        if (tipus == TipusFitxa::REINA)
        {
            taulell[fila][columna].simbol = " Q ";
        }
        if (tipus == TipusFitxa::REI)
        {
            taulell[fila][columna].simbol = " K ";
        }
    }

    if (color == ColorFitxa::NEGRE)
    {
        if (tipus == TipusFitxa::PEO)
        {
            taulell[fila][columna].simbol = " p ";
        }
        if (tipus == TipusFitxa::TORRE)
        {
            taulell[fila][columna].simbol = " t ";
        }
        if (tipus == TipusFitxa::CAVALL)
        {
            taulell[fila][columna].simbol = " h ";
        }
        if (tipus == TipusFitxa::ALFIL)
        {
            taulell[fila][columna].simbol = " b ";
        }
        if (tipus == TipusFitxa::REINA)
        {
            taulell[fila][columna].simbol = " q ";
        }
        if (tipus == TipusFitxa::REI)
        {
            taulell[fila][columna].simbol = " k ";
        }
    }
}