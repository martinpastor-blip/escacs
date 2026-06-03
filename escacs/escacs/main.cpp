#include "defines.h"
#include "includes.h"
#include "joc.h"
#include "taulell.h"

int main()
{
    inicialitzarTaulell();

    int filaOrigen = ZERO;
    int columnaOrigen = ZERO;
    int filaDesti = ZERO;
    int columnaDesti = ZERO;
    std::string missatgeError = "";

    while (!partida.partidaAcabada)
    {
        std::system("cls");
        imprimirTaulell();

        if (!missatgeError.empty())
        {
            std::cout << "\n ERROR: " << missatgeError << "\n";
            missatgeError = "";
        }

        std::cout << "\nEntra origen (Fila i Columna  1-8): ";
        if (!(std::cin >> filaOrigen >> columnaOrigen))
        {
            std::cin.clear();
            std::cin.ignore(BUFFER_INPUT, '\n');
            missatgeError = "Entrada no valida, introdueix dos numeros.";
            continue;
        }

        if (filaOrigen < RANG_MINIM || filaOrigen > RANG_MAXIM)
        {
            missatgeError = "Fila fora de rang, introdueix un valor entre  1-8.";
            continue;
        }
        if (columnaOrigen < RANG_MINIM || columnaOrigen > RANG_MAXIM)
        {
            missatgeError = "Columna fora de rang, introdueix un valor entre  1-8.";
            continue;
        }

        std::cout << "Entra desti  (Fila i Columna 1-8): ";
        if (!(std::cin >> filaDesti >> columnaDesti))
        {
            std::cin.clear();
            std::cin.ignore(BUFFER_INPUT, '\n');
            missatgeError = "Entrada no valida, introdueix dos numeros.";
            continue;
        }

        if (filaDesti < RANG_MINIM || filaDesti > RANG_MAXIM)
        {
            missatgeError = "Fila fora de rang, introdueix un valor entre 1-8.";
            continue;
        }
        if (columnaDesti < RANG_MINIM || columnaDesti > RANG_MAXIM)
        {
            missatgeError = "Columna fora de rang, introdueix un valor entre  1-8.";
            continue;
        }

        int filaMatriuOrigen = TAMANYTAULELL - filaOrigen;
        int columnaMatriuOrigen = columnaOrigen - UN_PAS;
        int filaMatriuDesti = TAMANYTAULELL - filaDesti;
        int columnaMatriuDesti = columnaDesti - UN_PAS;

        if (!moureFitxa(filaMatriuOrigen, columnaMatriuOrigen, filaMatriuDesti, columnaMatriuDesti))
        {
            missatgeError = "Moviment illegal o no es el teu torn.";
        }

        else if (estaEnEscac(partida.tornActual))
        {
            missatgeError = "ESCAC! El rei esta en perill.";
        }


    }

    std::system("cls");
    imprimirTaulell();

    if (estaEnEscac(partida.tornActual))
    {
        if (partida.tornActual == ColorFitxa::BLANC)
        {
            std::cout << "\n Guanyen les negres per jaque mat\n";
        }
        if (partida.tornActual == ColorFitxa::NEGRE)
        {
            std::cout << "\n Guanyen les blanques per jaq mat.\n";
        }
    }
    else
    {
        std::cout << "\n Taules! Cap jugador pot fer cap moviment legal.\n";
    }

    return ZERO;
}