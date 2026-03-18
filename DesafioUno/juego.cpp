#include "juego.h"
#include "tablero.h"
#include <cstdlib>
#include <ctime>
#include <QString>
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