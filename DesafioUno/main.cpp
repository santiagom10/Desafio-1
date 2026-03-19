#include <QCoreApplication>
#include <QTextStream>
#include "juego.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream in(stdin);
    QTextStream out(stdout);

    out << "+==============================+\n";
    out << "|        T E T R I S           |\n";
    out << "+==============================+\n\n";
    out.flush();

    ejecutarJuego(in, out);

    return 0;
}