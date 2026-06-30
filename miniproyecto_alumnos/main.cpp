#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Alumno {
    string nombre;
    double practica;
    double parcial;
    double promedio;
    string estado;
};

int main() {

    ifstream entrada("alumnos.txt");
    ofstream salida("resultados.txt");

    // Verificar apertura del archivo de entrada
    if (!entrada.is_open()) {
        cout << "Error al abrir el archivo alumnos.txt" << endl;
        return 1;
    }

    // Verificar creación del archivo de salida
    if (!salida.is_open()) {
        cout << "Error al crear el archivo resultados.txt" << endl;
        return 1;
    }

    vector<Alumno> alumnos;
    Alumno a;

    // Leer datos del archivo
    while (entrada >> a.nombre >> a.practica >> a.parcial) {

        // Calcular promedio
        a.promedio = (a.practica + a.parcial) / 2.0;

        // Determinar si aprueba
        if (a.promedio >= 12) {
            a.estado = "Aprobado";
        } else {
            a.estado = "Desaprobado";
        }

        alumnos.push_back(a);
    }

    // Formato del archivo de salida
    salida << fixed << setprecision(2);
    salida << "Alumno\tPC\tParcial\tPromedio\tEstado" << endl;

    // Escribir resultados
    for (int i = 0; i < alumnos.size(); i++) {
        salida << alumnos[i].nombre << "\t"
               << alumnos[i].practica << "\t"
               << alumnos[i].parcial << "\t"
               << alumnos[i].promedio << "\t\t"
               << alumnos[i].estado << endl;
    }

    entrada.close();
    salida.close();

    cout << "Proceso realizado correctamente." << endl;
    cout << "Revise el archivo resultados.txt" << endl;

    return 0;
}
