#include <iostream>

using namespace std;

int ancho;
int alto;

unsigned char* tablero;

// imprimir tablero
void imprimirTablero() {

    for(int i = 0; i < alto; i++) {

        unsigned char filaTemp = tablero[i];

        for(int j = ancho-1; j >= 0; j--) {

            if(filaTemp & (1 << j))
                cout << "#";
            else
                cout << ".";
        }

        cout << endl;
    }
}

// crear tablero
void crearTablero() {

    tablero = new unsigned char[alto];

    for(int i = 0; i < alto; i++)
        tablero[i] = 0;
}

int main() {

    cout << "Ingrese ancho del tablero (8): ";
    cin >> ancho;

    cout << "Ingrese alto del tablero: ";
    cin >> alto;

    if(ancho != 8 || alto < 8) {

        cout << "Dimensiones invalidas\n";
        return 0;
    }

    crearTablero();

    cout << "\nTablero creado:\n";
    imprimirTablero();

    delete[] tablero;

    return 0;
}
