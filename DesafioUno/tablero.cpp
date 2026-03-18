#include "tablero.h"

const uint8 PIEZAS[7][4][4] = {
    {{0x0,0xF,0,0},{2,2,2,2},{0x0,0xF,0,0},{2,2,2,2}},
    {{6,6,0,0},{6,6,0,0},{6,6,0,0},{6,6,0,0}},
    {{4,0xE,0,0},{4,6,4,0},{0xE,4,0,0},{4,0xC,4,0}},
    {{6,0xC,0,0},{4,6,2,0},{6,0xC,0,0},{4,6,2,0}},
    {{0xC,6,0,0},{2,6,4,0},{0xC,6,0,0},{2,6,4,0}},
    {{8,0xE,0,0},{6,4,4,0},{0xE,2,0,0},{4,4,0xC,0}},
    {{2,0xE,0,0},{4,4,6,0},{0xE,8,0,0},{0xC,4,4,0}}
};

uint32* crearTablero(sint32 alto)
{
    uint32* t = new uint32[alto];
    for (int i = 0; i < alto; i++) t[i] = 0;
    return t;
}

void destruirTablero(uint32* t)
{
    delete[] t;
}

uint32 mascaraLlena(sint32 ancho)
{
    return ((1u << ancho) - 1u) << (32 - ancho);
}

uint32 mascaraPieza(uint8 fila, sint32 x)
{
    uint32 m = fila << 28;
    return m >> x;
}

bool hayColision(uint32* tablero, sint32 alto, sint32 ancho,
                 sint32 tipo, sint32 rot, sint32 x, sint32 y)
{
    // 🔥 CONTROL DE BORDES (SOLUCIÓN)
    if (x < 0)
        return true;
    uint32 llena = mascaraLlena(ancho);
    uint32 fuera = ~llena;

    for (int f = 0; f < 4; f++) {
        uint8 fila = PIEZAS[tipo][rot][f];
        if (!fila) continue;

        int real = y + f;

        if (real >= alto)
            return true;

        uint32 m = mascaraPieza(fila, x);

        if (m & fuera)
            return true;

        if (real >= 0 && (m & tablero[real]))
            return true;
    }

    return false;
}

void fijarPieza(uint32* tablero, sint32 alto,
                sint32 tipo, sint32 rot, sint32 x, sint32 y)
{
    for (int f = 0; f < 4; f++) {
        uint8 fila = PIEZAS[tipo][rot][f];
        if (!fila) continue;

        int real = y + f;
        if (real >= 0 && real < alto)
            tablero[real] |= mascaraPieza(fila, x);
    }
}





//// linmpiar filas








void dibujar(QTextStream& out, uint32* tablero, sint32 alto, sint32 ancho,
             sint32 tipo, sint32 rot, sint32 x, sint32 y)
{
    out << "\n";

    for (int i = 0; i < alto; i++) {
        out << "|";
        for (int j = 0; j < ancho; j++) {
            uint32 mask = 1u << (31 - j);
            bool ocupado = tablero[i] & mask;

            bool pieza = false;
            int pf = i - y;
            int pc = j - x;

            if (pf >= 0 && pf < 4 && pc >= 0 && pc < 4) {
                pieza = (PIEZAS[tipo][rot][pf] >> (3 - pc)) & 1;
            }

            out << ((ocupado || pieza) ? "#" : ".");
        }
        out << "|\n";
    }
}


