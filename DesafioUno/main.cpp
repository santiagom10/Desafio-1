#include <QCoreApplication>
#include <QTextStream>
#include "juego.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream in(stdin);
    QTextStream out(stdout);


    out.flush();

    ejecutarJuego(in, out);

    return 0;
}