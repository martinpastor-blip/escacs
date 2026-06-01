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

// Inicialitza el taulell amb totes les peces a la posicio inicial i prepara la partida per a que comencin les blanques
void inicialitzarTaulell()
{
    // Comencen les blanques i la partida no ha acabat
    partida.tornActual = ColorFitxa::BLANC;
    partida.partidaAcabada = false;

    // Buidem tot el taulell
    for (int fila = ZERO; fila < TAMANYTAULELL; fila++)
    {
        for (int columna = ZERO; columna < TAMANYTAULELL; columna++)
        {
            posarFitxa(fila, columna, ColorFitxa::CAP, TipusFitxa::BUIT);
        }
    }

    // Posem els peons
    for (int columna = ZERO; columna < TAMANYTAULELL; columna++)
    {
        posarFitxa(FILA_PEONS_NEGRE, columna, ColorFitxa::NEGRE, TipusFitxa::PEO);
        posarFitxa(FILA_PEONS_BLANC, columna, ColorFitxa::BLANC, TipusFitxa::PEO);
    }

    // Peces negres a la fila ZERO
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_TORRE_ESQ, ColorFitxa::NEGRE, TipusFitxa::TORRE);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_CAVALL_ESQ, ColorFitxa::NEGRE, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_ALFIL_ESQ, ColorFitxa::NEGRE, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_REINA, ColorFitxa::NEGRE, TipusFitxa::REINA);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_REI, ColorFitxa::NEGRE, TipusFitxa::REI);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_ALFIL_DRE, ColorFitxa::NEGRE, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_CAVALL_DRE, ColorFitxa::NEGRE, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_TORRE_DRE, ColorFitxa::NEGRE, TipusFitxa::TORRE);

    // Peces blanques a la fila SET
    posarFitxa(FILA_PECES_BLANC, COLUMNA_TORRE_ESQ, ColorFitxa::BLANC, TipusFitxa::TORRE);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_CAVALL_ESQ, ColorFitxa::BLANC, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_ALFIL_ESQ, ColorFitxa::BLANC, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_REINA, ColorFitxa::BLANC, TipusFitxa::REINA);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_REI, ColorFitxa::BLANC, TipusFitxa::REI);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_ALFIL_DRE, ColorFitxa::BLANC, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_CAVALL_DRE, ColorFitxa::BLANC, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_TORRE_DRE, ColorFitxa::BLANC, TipusFitxa::TORRE);
}


// Mostra el taulell per pantalla amb les peces actuals i indica de qui es el torn
void imprimirTaulell()
{
    std::cout << "\nESCACS: POL MATES I MARTIN PASTOR\n";
    std::cout << NUMEROSTAULELL;
    std::cout << "    ------------------------\n";

    for (int fila = ZERO; fila < TAMANYTAULELL; fila++)
    {
        // Restem per mostrar les files de l'VUIT al UN de dalt a baix
        std::cout << " " << TAMANYTAULELL - fila << " |";
        for (int columna = ZERO; columna < TAMANYTAULELL; columna++)
        {
            std::cout << taulell[fila][columna].simbol;
        }
        std::cout << "|\n";
    }

    std::cout << "    ------------------------\n";

    if (partida.tornActual == ColorFitxa::BLANC)
    {
        std::cout << "    TORN: BLANQUES (Maj)\n";
    }
    if (partida.tornActual == ColorFitxa::NEGRE)
    {
        std::cout << "    TORN: NEGRES (Min)\n";
    }
}