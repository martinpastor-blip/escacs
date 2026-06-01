#include "joc.h"
#include "defines.h"
#include "includes.h"


// Canvia el torn de les blanques a les negres o viceversa
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

// Comprova que no hi hagi peces entre l'origen i el desti
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

// Validacio del moviment del peo
bool esMovimentPeoValid(Fitxa origen, Fitxa desti, int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    int direccio = DIRECCIO_NEGRE;
    if (origen.color == ColorFitxa::BLANC)
    {
        direccio = DIRECCIO_BLANC;
    }

    int diffColumna = valorAbsolut(columnaDesti - columnaOrigen);

    // Avancar normal d'una casella
    if (columnaOrigen == columnaDesti && desti.tipus == TipusFitxa::BUIT && filaDesti - filaOrigen == direccio)
    {
        return true;
    }

    // Doble avanc des de la fila inicial
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

    // Captura en diagonal
    if (diffColumna == UN_PAS && filaDesti - filaOrigen == direccio && desti.tipus != TipusFitxa::BUIT)
    {
        return true;
    }

    return false;
}

// Validacio del moviment de la torre
bool esMovimentTorreValid(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    if (filaOrigen != filaDesti && columnaOrigen != columnaDesti)
    {
        return false;
    }

    return camiLliure(filaOrigen, columnaOrigen, filaDesti, columnaDesti);
}

// Validacio del moviment de l'alfil
bool esMovimentAlfilValid(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti, int diffFila, int diffColumna)
{
    if (diffFila != diffColumna)
    {
        return false;
    }

    return camiLliure(filaOrigen, columnaOrigen, filaDesti, columnaDesti);
}

// Validacio del moviment del cavall
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

// Validacio del moviment de la reina
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

// Validacio del moviment del rei
bool esMovimentReiValid(int diffFila, int diffColumna)
{
    if (diffFila <= UN_PAS && diffColumna <= UN_PAS)
    {
        return true;
    }
    return false;
}

// Comprova si el moviment es valid segons les regles del joc i el torn actual
bool esMovimentValid(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    Fitxa origen = taulell[filaOrigen][columnaOrigen];
    Fitxa desti = taulell[filaDesti][columnaDesti];

    if (origen.tipus == TipusFitxa::BUIT)
    {
        return false;
    }

    if (origen.color != partida.tornActual)
    {
        return false;
    }

    if (desti.tipus != TipusFitxa::BUIT && desti.color == origen.color)
    {
        return false;
    }

    int diffFila = valorAbsolut(filaDesti - filaOrigen);
    int diffColumna = valorAbsolut(columnaDesti - columnaOrigen);

    if (origen.tipus == TipusFitxa::PEO)
    {
        return esMovimentPeoValid(origen, desti, filaOrigen, columnaOrigen, filaDesti, columnaDesti);
    }

    if (origen.tipus == TipusFitxa::TORRE)
    {
        return esMovimentTorreValid(filaOrigen, columnaOrigen, filaDesti, columnaDesti);
    }

    if (origen.tipus == TipusFitxa::ALFIL)
    {
        return esMovimentAlfilValid(filaOrigen, columnaOrigen, filaDesti, columnaDesti, diffFila, diffColumna);
    }

    if (origen.tipus == TipusFitxa::CAVALL)
    {
        return esMovimentCavallValid(diffFila, diffColumna);
    }

    if (origen.tipus == TipusFitxa::REINA)
    {
        return esMovimentReinaValid(filaOrigen, columnaOrigen, filaDesti, columnaDesti, diffFila, diffColumna);
    }

    if (origen.tipus == TipusFitxa::REI)
    {
        return esMovimentReiValid(diffFila, diffColumna);
    }

    return false;
}

// Comprova si una peca pot atacar una casella independentment del torn
// Serveix per detectar si el rei esta en escac
bool potAtacar(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    Fitxa origen = taulell[filaOrigen][columnaOrigen];
    Fitxa desti = taulell[filaDesti][columnaDesti];

    if (origen.tipus == TipusFitxa::BUIT)
    {
        return false;
    }

    if (desti.color == origen.color)
    {
        return false;
    }

    int diffFila = valorAbsolut(filaDesti - filaOrigen);
    int diffColumna = valorAbsolut(columnaDesti - columnaOrigen);

    if (origen.tipus == TipusFitxa::PEO)
    {
        int direccio = DIRECCIO_NEGRE;
        if (origen.color == ColorFitxa::BLANC)
        {
            direccio = DIRECCIO_BLANC;
        }
        if (diffColumna == UN_PAS && filaDesti - filaOrigen == direccio)
        {
            return true;
        }
        return false;
    }

    if (origen.tipus == TipusFitxa::TORRE)
    {
        return esMovimentTorreValid(filaOrigen, columnaOrigen, filaDesti, columnaDesti);
    }

    if (origen.tipus == TipusFitxa::ALFIL)
    {
        return esMovimentAlfilValid(filaOrigen, columnaOrigen, filaDesti, columnaDesti, diffFila, diffColumna);
    }

    if (origen.tipus == TipusFitxa::CAVALL)
    {
        return esMovimentCavallValid(diffFila, diffColumna);
    }

    if (origen.tipus == TipusFitxa::REINA)
    {
        return esMovimentReinaValid(filaOrigen, columnaOrigen, filaDesti, columnaDesti, diffFila, diffColumna);
    }

    if (origen.tipus == TipusFitxa::REI)
    {
        return esMovimentReiValid(diffFila, diffColumna);
    }

    return false;
}



// Comprova si el rei del color indicat esta en escac
bool estaEnEscac(ColorFitxa color)
{
    int filaRei = SENSE_REI;
    int columnaRei = SENSE_REI;

    // Buscar el rei al taulell
    for (int fila = ZERO; fila < TAMANYTAULELL; fila++)
    {
        for (int columna = ZERO; columna < TAMANYTAULELL; columna++)
        {
            if (taulell[fila][columna].tipus == TipusFitxa::REI && taulell[fila][columna].color == color)
            {
                filaRei = fila;
                columnaRei = columna;
            }
        }
    }

    if (filaRei == SENSE_REI)
    {
        return false;
    }

    ColorFitxa colorEnemic;
    if (color == ColorFitxa::BLANC)
    {
        colorEnemic = ColorFitxa::NEGRE;
    }
    else
    {
        colorEnemic = ColorFitxa::BLANC;
    }

    // Comprovem si alguna peca enemiga pot arribar al rei
    for (int fila = ZERO; fila < TAMANYTAULELL; fila++)
    {
        for (int columna = ZERO; columna < TAMANYTAULELL; columna++)
        {
            if (taulell[fila][columna].color == colorEnemic)
            {
                if (potAtacar(fila, columna, filaRei, columnaRei))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Comprova si el jugador indicat te algun moviment legal disponible
// Serveix per detectar escac i matar o taules
bool teMovimentsValids(ColorFitxa color)
{
    ColorFitxa tornOriginal = partida.tornActual;
    partida.tornActual = color;

    for (int filaO = ZERO; filaO < TAMANYTAULELL; filaO++)
    {
        for (int columnaO = ZERO; columnaO < TAMANYTAULELL; columnaO++)
        {
            if (taulell[filaO][columnaO].color != color)
            {
                continue;
            }

            for (int filaD = ZERO; filaD < TAMANYTAULELL; filaD++)
            {
                for (int columnaD = ZERO; columnaD < TAMANYTAULELL; columnaD++)
                {
                    if (!esMovimentValid(filaO, columnaO, filaD, columnaD))
                    {
                        continue;
                    }

                    // Provar el moviment temporalment
                    Fitxa copiaOrigen = taulell[filaO][columnaO];
                    Fitxa copiaDesti = taulell[filaD][columnaD];

                    taulell[filaD][columnaD] = taulell[filaO][columnaO];
                    taulell[filaO][columnaO].color = ColorFitxa::CAP;
                    taulell[filaO][columnaO].tipus = TipusFitxa::BUIT;
                    taulell[filaO][columnaO].simbol = " * ";

                    bool reiEnPerill = estaEnEscac(color);

                    // Desfer el moviment
                    taulell[filaO][columnaO] = copiaOrigen;
                    taulell[filaD][columnaD] = copiaDesti;

                    if (!reiEnPerill)
                    {
                        partida.tornActual = tornOriginal;
                        return true;
                    }
                }
            }
        }
    }

    partida.tornActual = tornOriginal;
    return false;
}

// Executa el moviment si es legal i gestiona coronament i canvi de torn
bool moureFitxa(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti)
{
    if (filaOrigen < ZERO || filaOrigen >= TAMANYTAULELL)
    {
        return false;
    }
    if (columnaOrigen < ZERO || columnaOrigen >= TAMANYTAULELL)
    {
        return false;
    }
    if (filaDesti < ZERO || filaDesti >= TAMANYTAULELL)
    {
        return false;
    }
    if (columnaDesti < ZERO || columnaDesti >= TAMANYTAULELL)
    {
        return false;
    }

    if (!esMovimentValid(filaOrigen, columnaOrigen, filaDesti, columnaDesti))
    {
        return false;
    }

    // Guardem copies per desfer el moviment si exposa el propi rei
    Fitxa copiaOrigen = taulell[filaOrigen][columnaOrigen];
    Fitxa copiaDesti = taulell[filaDesti][columnaDesti];

    taulell[filaDesti][columnaDesti] = taulell[filaOrigen][columnaOrigen];
    taulell[filaOrigen][columnaOrigen].color = ColorFitxa::CAP;
    taulell[filaOrigen][columnaOrigen].tipus = TipusFitxa::BUIT;
    taulell[filaOrigen][columnaOrigen].simbol = " * ";

    if (estaEnEscac(copiaOrigen.color))
    {
        taulell[filaOrigen][columnaOrigen] = copiaOrigen;
        taulell[filaDesti][columnaDesti] = copiaDesti;
        return false;
    }

    // Moviment definitiu
    posarFitxa(filaDesti, columnaDesti, copiaOrigen.color, copiaOrigen.tipus);
    posarFitxa(filaOrigen, columnaOrigen, ColorFitxa::CAP, TipusFitxa::BUIT);

    // Coronacio del peo si arriba a l'extrem oposat
    if (taulell[filaDesti][columnaDesti].tipus == TipusFitxa::PEO)
    {
        if (taulell[filaDesti][columnaDesti].color == ColorFitxa::BLANC)
        {
            if (filaDesti == FILA_CORONACIO_BLANC)
            {
                posarFitxa(filaDesti, columnaDesti, ColorFitxa::BLANC, TipusFitxa::REINA);
            }
        }
        if (taulell[filaDesti][columnaDesti].color == ColorFitxa::NEGRE)
        {
            if (filaDesti == FILA_CORONACIO_NEGRE)
            {
                posarFitxa(filaDesti, columnaDesti, ColorFitxa::NEGRE, TipusFitxa::REINA);
            }
        }
    }

    canviarTorn();

    // Si el seguent jugador no te moviments la partida acaba
    if (!teMovimentsValids(partida.tornActual))
    {
        partida.partidaAcabada = true;
    }

    return true;
}