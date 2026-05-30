#include "joc.h"
#include "defines.h"
#include "includes.h"


void canviarTorn()
{
    if (partida.tornActual == ColorFitxa::BLANC)
    {
        partida.tornActual = ColorFitxa::NEGRE;
    }
    else
    {
        partida.tornActual = ColorFitxa::BLANC;
    }
}


int valorAbsolut(int numero)
{
    if (numero < ZERO)
    {
        return -numero;
    }
    return numero;
}

bool camiLliure(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    int dirFila = SENSE_DIRECCIO;
    if (filaDesti > filaOrigen)
    {
        dirFila = DIRECCIO_POSITIVA;
    }

    if (filaDesti < filaOrigen)
    {
        dirFila = DIRECCIO_NEGATIVA;
    }

    int dirColumna = SENSE_DIRECCIO;
    if (columnaDesti > columnaOrigen)
    {
        dirColumna = DIRECCIO_POSITIVA;
    }

    if (columnaDesti < columnaOrigen)
    {
        dirColumna = DIRECCIO_NEGATIVA;
    }

    int fila = filaOrigen + dirFila;
    int columna = columnaOrigen + dirColumna;

    while (fila != filaDesti || columna != columnaDesti)
    {
        if (taulell[fila][columna].tipus != TipusFitxa::BUIT)
        {
            return false;
        }
        fila = fila + dirFila;
        columna = columna + dirColumna;
    }
    return true;
}

bool esMovimentPeoValid(Fitxa origen, Fitxa desti, int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    int direccio = DIRECCIO_NEGRE;
    if (origen.color == ColorFitxa::BLANC)
    {
        direccio = DIRECCIO_BLANC;
    }

    int diffColumna = valorAbsolut(columnaDesti - columnaOrigen);

    if (columnaOrigen == columnaDesti && desti.tipus == TipusFitxa::BUIT && filaDesti - filaOrigen == direccio)
    {
        return true;
    }

    bool estaAFilaInicial = false;
    if (origen.color == ColorFitxa::BLANC && filaOrigen == FILA_PEONS_BLANC)
    {
        estaAFilaInicial = true;
    }

    if (origen.color == ColorFitxa::NEGRE && filaOrigen == FILA_PEONS_NEGRE)
    {
        estaAFilaInicial = true;
    }

    if (columnaOrigen == columnaDesti && estaAFilaInicial && desti.tipus == TipusFitxa::BUIT)
    {
        if (filaDesti - filaOrigen == DOS_PASSOS * direccio)
        {
            if (taulell[filaOrigen + direccio][columnaOrigen].tipus == TipusFitxa::BUIT)
            {
                return true;
            }
        }
    }

    if (diffColumna == UN_PAS && filaDesti - filaOrigen == direccio && desti.tipus != TipusFitxa::BUIT)
    {
        return true;
    }

    return false;
}

bool esMovimentTorreValid(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    if (filaOrigen != filaDesti && columnaOrigen != columnaDesti)
    {
        return false;
    }

    return camiLliure(filaOrigen, columnaOrigen, filaDesti, columnaDesti);
}

bool esMovimentAlfilValid(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti, int diffFila, int diffColumna)
{
    if (diffFila != diffColumna)
    {
        return false;
    }

    return camiLliure(filaOrigen, columnaOrigen, filaDesti, columnaDesti);
}

bool esMovimentCavallValid(int diffFila, int diffColumna)
{
    if (diffFila == SALT_CAVALL_LLARG && diffColumna == SALT_CAVALL_CURT)
    {
        return true;
    }

    if (diffFila == SALT_CAVALL_CURT && diffColumna == SALT_CAVALL_LLARG)
    {
        return true;
    }
    return false;
}

bool esMovimentReinaValid(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti, int diffFila, int diffColumna)
{
    bool esLinia = (filaOrigen == filaDesti || columnaOrigen == columnaDesti);
    bool esDiagonal = (diffFila == diffColumna);

    if (!esLinia && !esDiagonal)
    {
        return false;
    }
    return camiLliure(filaOrigen, columnaOrigen, filaDesti, columnaDesti);
}

bool esMovimentReiValid(int diffFila, int diffColumna)
{
    if (diffFila <= UN_PAS && diffColumna <= UN_PAS)
    {
        return true;
    }
    return false;
}

