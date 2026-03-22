#include "tablero.h"

const uint8 PIEZAS[7][4][4] = {
    {{0xF,0,0,0},{8,8,8,8},{0xF,0,0,0},{8,8,8,8}},
    {{0xC,0xC,0,0},{0xC,0xC,0,0},{0xC,0xC,0,0},{0xC,0xC,0,0}},
    {{0xE,4,0,0},{4,0xC,4,0},{4,0xE,0,0},{4,6,4,0}},
    {{6,0xC,0,0},{4,6,2,0},{6,0xC,0,0},{4,6,2,0}},
    {{0xC,6,0,0},{2,6,4,0},{0xC,6,0,0},{2,6,4,0}},
    {{8,0xE,0,0},{6,4,4,0},{0xE,2,0,0},{4,4,0xC,0}},
    {{2,0xE,0,0},{4,4,6,0},{0xE,8,0,0},{0xC,4,4,0}}
};
const char* colorPieza(int tipo) {
    switch (tipo) {
    case 0: return "\033[36m"; // I - cyan
    case 1: return "\033[33m"; // O - amarillo
    case 2: return "\033[35m"; // T - magenta
    case 3: return "\033[32m"; // S - verde
    case 4: return "\033[31m"; // Z - rojo
    case 5: return "\033[34m"; // J - azul
    case 6: return "\033[37m"; // L - blanco
    default: return "\033[0m";
    }
}
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
    return (x >= 0) ? (m >> x) : (m << (-x));
}

sint32 offsetIzq(const uint8 pieza[4])
{
    for (int col = 0; col < 4; col++)
        for (int fila = 0; fila < 4; fila++)
            if ((pieza[fila] >> (3 - col)) & 1)
                return col;
    return 0;
}

bool hayColision(uint32* tablero, sint32 alto, sint32 ancho,
                 sint32 tipo, sint32 rot, sint32 x, sint32 y)
{
    if (x < 0) return true;

    uint32 llena = mascaraLlena(ancho);
    uint32 fuera = ~llena;
    int offset = offsetIzq(PIEZAS[tipo][rot]);

    for (int f = 0; f < 4; f++) {
        uint8 fila = PIEZAS[tipo][rot][f];
        if (!fila) continue;

        int real = y + f;
        if (real >= alto) return true;

        uint32 m = mascaraPieza(fila, x - offset);

        if (m & fuera) return true;
        if (real >= 0 && (m & tablero[real])) return true;
    }

    return false;
}

void fijarPieza(uint32* tablero, sint32 alto,
                sint32 tipo, sint32 rot, sint32 x, sint32 y)
{
    int offset = offsetIzq(PIEZAS[tipo][rot]);

    for (int f = 0; f < 4; f++) {
        uint8 fila = PIEZAS[tipo][rot][f];
        if (!fila) continue;

        int real = y + f;

        if (real >= 0 && real < alto)
            tablero[real] |= mascaraPieza(fila, x - offset);
    }
}

sint32 limpiarFilas(uint32* tablero, sint32 alto, sint32 ancho)
{
    uint32 llena = mascaraLlena(ancho);
    int count = 0;

    for (int i = alto - 1; i >= 0; i--) {
        if ((tablero[i] & llena) == llena) {
            for (int k = i; k > 0; k--)
                tablero[k] = tablero[k - 1];

            tablero[0] = 0;
            count++;
            i++;
        }
    }
    return count;
}

void dibujar(QTextStream& out, uint32* tablero, sint32 alto, sint32 ancho,
             sint32 tipo, sint32 rot, sint32 x, sint32 y)
{
    out << "\n";

    // 🔝 TECHO
    out << "+";
    for (int j = 0; j < ancho; j++) out << "-";
    out << "+\n";

    for (int i = 0; i < alto; i++) {
        out << "|";
        for (int j = 0; j < ancho; j++) {
            uint32 mask = 1u << (31 - j);
            bool ocupado = tablero[i] & mask;

            bool pieza = false;
            int pf = i - y;
            int offset = offsetIzq(PIEZAS[tipo][rot]);
            int pc = j - (x - offset);

            if (pf >= 0 && pf < 4 && pc >= 0 && pc < 4)
                pieza = (PIEZAS[tipo][rot][pf] >> (3 - pc)) & 1;

            if (ocupado) {
                out << "\033[37m#\033[0m";
            }
            else if (pieza) {
                out << colorPieza(tipo) << "#" << "\033[0m";
            }
            else {
                out << ".";
            }
        }
        out << "|\n";
    }


    out << "+";
    for (int j = 0; j < ancho; j++) out << "-";
    out << "+\n";
}