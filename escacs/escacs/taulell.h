#pragma once
#include "includes.h"
#include "defines.h"

#define TAMANYTAULELL VUIT
#define NUMEROSTAULELL "\n    1  2  3  4  5  6  7  8\n"
#define FILA_PEONS_NEGRE UN
#define FILA_PEONS_BLANC SIS
#define FILA_CORONACIO_BLANC ZERO
#define FILA_CORONACIO_NEGRE SET
#define FILA_PECES_NEGRE ZERO
#define FILA_PECES_BLANC SET
#define COLUMNA_TORRE_ESQ ZERO
#define COLUMNA_CAVALL_ESQ UN
#define COLUMNA_ALFIL_ESQ DOS
#define COLUMNA_REINA TRES
#define COLUMNA_REI CUATRE
#define COLUMNA_ALFIL_DRE CINC
#define COLUMNA_CAVALL_DRE SIS
#define COLUMNA_TORRE_DRE SET

// Estructures i enums globals
enum class ColorFitxa { BLANC, NEGRE, CAP };
enum class TipusFitxa { PEO, TORRE, CAVALL, ALFIL, REINA, REI, BUIT };

struct Fitxa {
    ColorFitxa color;
    TipusFitxa tipus;
    std::string simbol;
};

struct Partida {
    ColorFitxa tornActual;
    bool partidaAcabada;
};

extern Fitxa taulell[TAMANYTAULELL][TAMANYTAULELL];
extern Partida partida;

// Funcions del TAULELl
void inicialitzarTaulell();
void imprimirTaulell();
void posarFitxa(int fila, int columna, ColorFitxa color, TipusFitxa tipus);