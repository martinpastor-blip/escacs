#include "defines.h"
#include "taulell.h"
#include "includes.h"

Fitxa taulell[TAMANYTAULELL][TAMANYTAULELL];
Partida partida;


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




void inicialitzarTaulell()
{
    partida.tornActual = ColorFitxa::BLANC;
    partida.partidaAcabada = false;

    for (int fila = ZERO; fila < TAMANYTAULELL; fila++)
    {
        for (int columna = ZERO; columna < TAMANYTAULELL; columna++)
        {
            posarFitxa(fila, columna, ColorFitxa::CAP, TipusFitxa::BUIT);
        }
    }

    for (int columna = ZERO; columna < TAMANYTAULELL; columna++)
    {
        posarFitxa(FILA_PEONS_NEGRE, columna, ColorFitxa::NEGRE, TipusFitxa::PEO);
        posarFitxa(FILA_PEONS_BLANC, columna, ColorFitxa::BLANC, TipusFitxa::PEO);
    }

    posarFitxa(FILA_PECES_NEGRE, COLUMNA_TORRE_ESQ, ColorFitxa::NEGRE, TipusFitxa::TORRE);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_CAVALL_ESQ, ColorFitxa::NEGRE, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_ALFIL_ESQ, ColorFitxa::NEGRE, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_REINA, ColorFitxa::NEGRE, TipusFitxa::REINA);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_REI, ColorFitxa::NEGRE, TipusFitxa::REI);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_ALFIL_DRE, ColorFitxa::NEGRE, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_CAVALL_DRE, ColorFitxa::NEGRE, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_NEGRE, COLUMNA_TORRE_DRE, ColorFitxa::NEGRE, TipusFitxa::TORRE);

    posarFitxa(FILA_PECES_BLANC, COLUMNA_TORRE_ESQ, ColorFitxa::BLANC, TipusFitxa::TORRE);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_CAVALL_ESQ, ColorFitxa::BLANC, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_ALFIL_ESQ, ColorFitxa::BLANC, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_REINA, ColorFitxa::BLANC, TipusFitxa::REINA);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_REI, ColorFitxa::BLANC, TipusFitxa::REI);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_ALFIL_DRE, ColorFitxa::BLANC, TipusFitxa::ALFIL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_CAVALL_DRE, ColorFitxa::BLANC, TipusFitxa::CAVALL);
    posarFitxa(FILA_PECES_BLANC, COLUMNA_TORRE_DRE, ColorFitxa::BLANC, TipusFitxa::TORRE);
}


void imprimirTaulell()
{
    std::cout << "\nESCACS: POL MATES I MARTIN PASTOR\n";
    std::cout << NUMEROSTAULELL;
    std::cout << "    ------------------------\n";

    for (int fila = ZERO; fila < TAMANYTAULELL; fila++)
    {
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
        std::cout << "    Torn de Blanques (Majuscules)\n";
    }
    if (partida.tornActual == ColorFitxa::NEGRE)
    {
        std::cout << "    Torn de Negres (Minuscules)\n";
    }
}