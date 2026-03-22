#include "juego.h"
#include "tablero.h"
#include <cstdlib>
#include <ctime>
#include <QString>

typedef int sint32;

sint32 leerEntero(QTextStream& in, QTextStream& out, const char* msg)
{
    sint32 v;

    while (true) {
        out << msg;
        out.flush();

        in >> v;

        if (in.status() == QTextStream::Ok)
            return v;

        in.resetStatus();
        in.readLine();
        out << "Entrada invalida.\n";
    }
}

char leerChar(QTextStream& in, QTextStream& out)
{
    out << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
    out.flush();

    QString linea = in.readLine();
    if (linea.isEmpty()) return ' ';

    char op = linea[0].toLatin1();

    if (op >= 'A' && op <= 'Z')
        op = (char)(op + ('a' - 'A'));

    return op;
}

void nuevaPieza(sint32 ancho, sint32& tipo, sint32& rot, sint32& x, sint32& y)
{
    tipo = rand() % 7;
    rot = 0;
    x = (ancho / 2) - 2;
    y = -1;
}

void ejecutarJuego(QTextStream& in, QTextStream& out)
{
    sint32 ancho, alto;

    do {
        ancho = leerEntero(in, out, "Ancho (8-32 multiplo de 8): ");
    } while (ancho < 8 || ancho > 32 || (ancho % 8 != 0));

    do {
        alto = leerEntero(in, out, "Alto (>=8): ");
    } while (alto < 8);

    uint32* tablero = crearTablero(alto);
    srand((unsigned int)time(0));

    sint32 tipo, rot, x, y;
    nuevaPieza(ancho, tipo, rot, x, y);

    bool corriendo = true;

    while (corriendo) {
        dibujar(out, tablero, alto, ancho, tipo, rot, x, y);

        char op = leerChar(in, out);

        if (op == 'a') {
            if (!hayColision(tablero, alto, ancho, tipo, rot, x - 1, y)) x--;
        }
        else if (op == 'd') {
            if (!hayColision(tablero, alto, ancho, tipo, rot, x + 1, y)) x++;
        }
        else if (op == 'w') {
            sint32 nuevaRot = (rot + 1) & 3;
            if (!hayColision(tablero, alto, ancho, tipo, nuevaRot, x, y))
                rot = nuevaRot;
        }
        else if (op == 'q') {
            break;
        }

        if (op == 's') {
            if (!hayColision(tablero, alto, ancho, tipo, rot, x, y + 1)) {
                y++;
                continue;
            }
        }

        if (!hayColision(tablero, alto, ancho, tipo, rot, x, y + 1)) {
            y++;
        } else {
            fijarPieza(tablero, alto, tipo, rot, x, y);
            limpiarFilas(tablero, alto, ancho);
            nuevaPieza(ancho, tipo, rot, x, y);

            if (hayColision(tablero, alto, ancho, tipo, rot, x, y))
                corriendo = false;
        }
    }

    out << "\nGAME OVER\n";
    destruirTablero(tablero);
}