#pragma once
#include "taulell.h"
#include "defines.h"

#define RANG_MINIM           UN
#define RANG_MAXIM           VUIT
#define DIRECCIO_BLANC      -UN
#define DIRECCIO_NEGRE       UN

#define UN_PAS               UN
#define DOS_PASSOS           DOS
#define SENSE_REI           -UN
#define DIRECCIO_POSITIVA    UN
#define DIRECCIO_NEGATIVA   -UN
#define SENSE_DIRECCIO       ZERO

#define SALT_CAVALL_LLARG    DOS
#define SALT_CAVALL_CURT     UN

// Funcions de control del joc
void canviarTorn();
bool estaEnEscac(ColorFitxa color);
bool teMovimentsValids(ColorFitxa color);
bool moureFitxa(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti);


// Funcions de logica de les peces
int valorAbsolut(int numero);
bool camiLliure(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti);
bool potAtacar(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti);
bool esMovimentValid(int filaOrigen, int columnaOrigen, int filaDesti, int columnaDesti);