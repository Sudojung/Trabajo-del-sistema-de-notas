#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Usuario {
    string user;
    string pass;
    string nombre;
};

struct Alumno {
    string nombre;
    double practica;
    double parcial;
};

int main() {

    string userInput, passInput;

    vector<Usuario> usuarios;
    vector<Alumno> alumnos;

    Usuario u;
    Alumno a;

    ifstream fUsers("usuarios.txt");
    ifstream fAlumnos("alumnos.txt");

    if (!fUsers.is_open() || !fAlumnos.is_open()) {
        cout << "Error al abrir archivos" << endl;
        return 1;
    }

    // cargar usuarios
    while (fUsers >> u.user >> u.pass >> u.nombre) {
        usuarios.push_back(u);
    }

    // cargar alumnos
    while (fAlumnos >> a.nombre >> a.practica >> a.parcial) {
        alumnos.push_back(a);
    }

    cout << "=== LOGIN ===" << endl;
    cout << "Usuario: ";
    cin >> userInput;

    cout << "Password: ";
    cin >> passInput;

    bool loginOK = false;
    string nombreUsuario;

    // verificar login
    for (int i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].user == userInput &&
            usuarios[i].pass == passInput) {

            loginOK = true;
            nombreUsuario = usuarios[i].nombre;
            break;
        }
    }

    if (!loginOK) {
        cout << "Login incorrecto" << endl;
        return 0;
    }

    // buscar notas del alumno
    bool encontrado = false;

    for (int i = 0; i < alumnos.size(); i++) {

        if (alumnos[i].nombre == nombreUsuario) {

            double promedio = (alumnos[i].practica + alumnos[i].parcial) / 2;

            cout << "\nBienvenido " << nombreUsuario << endl;
            cout << "Practica: " << alumnos[i].practica << endl;
            cout << "Parcial: " << alumnos[i].parcial << endl;
            cout << "Promedio: " << promedio << endl;

            if (promedio >= 12)
                cout << "Estado: Aprobado" << endl;
            else
                cout << "Estado: Desaprobado" << endl;

            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron notas para este usuario" << endl;
    }

    return 0;
}
