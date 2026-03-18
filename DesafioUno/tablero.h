#ifndef TABLERO_H
#define TABLERO_H

#include <QTextStream>

typedef unsigned int uint32;
typedef unsigned char uint8;
typedef int sint32;

uint32* crearTablero(sint32 alto);
void destruirTablero(uint32* t);

bool hayColision(uint32* tablero, sint32 alto, sint32 ancho,
                 sint32 tipo, sint32 rot, sint32 x, sint32 y);

void fijarPieza(uint32* tablero, sint32 alto,
                sint32 tipo, sint32 rot, sint32 x, sint32 y);

sint32 limpiarFilas(uint32* tablero, sint32 alto, sint32 ancho);

void dibujar(QTextStream& out, uint32* tablero, sint32 alto, sint32 ancho,
             sint32 tipo, sint32 rot, sint32 x, sint32 y);

#endif