#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

struct Alumno {
    string codigo;
    string nombre;
    double practica;
    double parcial;
    double promedio;
    string estado;
};

const string USUARIO_ADMIN = "benito04";
const string PASSWORD_ADMIN = "12341234";

const string RUTA_ALUMNOS = "data/alumnos.txt";
const string RUTA_APROBADOS = "output/aprobados.txt";
const string RUTA_DESAPROBADOS = "output/desaprobados.txt";

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double calcularPromedio(double practica, double parcial) {
    return (practica + parcial) / 2.0;
}

string obtenerEstado(double promedio) {
    return promedio >= 12.0 ? "Aprobado" : "Desaprobado";
}

bool soloNumeros(const string& texto) {
    if (texto.empty()) return false;

    for (char c : texto) {
        if (!isdigit((unsigned char)c)) {
            return false;
        }
    }

    return true;
}

string completarCodigo(string codigo) {
    while (codigo.length() < 8) {
        codigo = "0" + codigo;
    }
    return codigo;
}

bool codigoValido(const string& codigo) {
    return soloNumeros(codigo) && codigo.length() <= 8;
}

bool nombreValido(const string& nombre) {
    if (nombre.empty()) return false;

    for (char c : nombre) {
        if (!isalpha((unsigned char)c) && c != ' ') {
            return false;
        }
    }

    return true;
}

double leerNota(const string& mensaje) {
    double nota;

    while (true) {
        cout << mensaje;
        cin >> nota;

        if (!cin.fail() && nota >= 0 && nota <= 20) {
            return nota;
        }

        limpiarBuffer();
        cout << "Nota invalida. Debe estar entre 0 y 20.\n";
    }
}

int buscarIndiceAlumno(const vector<Alumno>& alumnos, const string& codigo) {
    for (int i = 0; i < (int)alumnos.size(); i++) {
        if (alumnos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

vector<Alumno> cargarAlumnos() {
    vector<Alumno> alumnos;
    ifstream archivo(RUTA_ALUMNOS);
    string linea;

    if (!archivo.is_open()) {
        ofstream crear(RUTA_ALUMNOS);
        crear.close();
        return alumnos;
    }

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        size_t p1 = linea.find('|');
        size_t p2 = linea.find('|', p1 + 1);
        size_t p3 = linea.find('|', p2 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos) {
            continue;
        }

        Alumno a;
        a.codigo = linea.substr(0, p1);
        a.nombre = linea.substr(p1 + 1, p2 - p1 - 1);

        try {
            a.practica = stod(linea.substr(p2 + 1, p3 - p2 - 1));
            a.parcial = stod(linea.substr(p3 + 1));
        } catch (...) {
            continue;
        }

        a.promedio = calcularPromedio(a.practica, a.parcial);
        a.estado = obtenerEstado(a.promedio);

        alumnos.push_back(a);
    }

    archivo.close();
    return alumnos;
}

void guardarAlumnos(const vector<Alumno>& alumnos) {
    ofstream archivo(RUTA_ALUMNOS);

    if (!archivo.is_open()) {
        cout << "Error: no se pudo guardar " << RUTA_ALUMNOS << endl;
        return;
    }

    for (const Alumno& a : alumnos) {
        archivo << a.codigo << "|"
                << a.nombre << "|"
                << a.practica << "|"
                << a.parcial << endl;
    }

    archivo.close();
}

void generarReportes(const vector<Alumno>& alumnos) {
    if (alumnos.empty()) {
        cout << "\nNo hay alumnos registrados para generar reportes.\n";
        return;
    }

    ofstream aprobados(RUTA_APROBADOS);
    ofstream desaprobados(RUTA_DESAPROBADOS);

    if (!aprobados.is_open() || !desaprobados.is_open()) {
        cout << "Error: no se pudieron crear los reportes.\n";
        return;
    }

    aprobados << fixed << setprecision(2);
    desaprobados << fixed << setprecision(2);

    aprobados << "============================================================\n";
    aprobados << "                    ALUMNOS APROBADOS\n";
    aprobados << "============================================================\n";
    aprobados << left << setw(12) << "Codigo"
              << setw(25) << "Alumno"
              << setw(12) << "Practica"
              << setw(12) << "Parcial"
              << setw(12) << "Promedio" << endl;
    aprobados << string(73, '-') << endl;

    desaprobados << "============================================================\n";
    desaprobados << "                  ALUMNOS DESAPROBADOS\n";
    desaprobados << "============================================================\n";
    desaprobados << left << setw(12) << "Codigo"
                 << setw(25) << "Alumno"
                 << setw(12) << "Practica"
                 << setw(12) << "Parcial"
                 << setw(12) << "Promedio" << endl;
    desaprobados << string(73, '-') << endl;

    int totalAprobados = 0;
    int totalDesaprobados = 0;

    for (const Alumno& a : alumnos) {
        if (a.estado == "Aprobado") {
            aprobados << left << setw(12) << a.codigo
                      << setw(25) << a.nombre
                      << setw(12) << a.practica
                      << setw(12) << a.parcial
                      << setw(12) << a.promedio << endl;
            totalAprobados++;
        } else {
            desaprobados << left << setw(12) << a.codigo
                         << setw(25) << a.nombre
                         << setw(12) << a.practica
                         << setw(12) << a.parcial
                         << setw(12) << a.promedio << endl;
            totalDesaprobados++;
        }
    }

    aprobados << "\nTotal de aprobados: " << totalAprobados << endl;
    desaprobados << "\nTotal de desaprobados: " << totalDesaprobados << endl;

    aprobados.close();
    desaprobados.close();

    cout << "\nReportes generados correctamente:\n";
    cout << "- " << RUTA_APROBADOS << endl;
    cout << "- " << RUTA_DESAPROBADOS << endl;
}

bool iniciarSesion() {
    string usuario, password;

    cout << "========================================\n";
    cout << "        SISTEMA DE NOTAS - UNMSM\n";
    cout << "========================================\n";
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasena: ";
    cin >> password;

    return usuario == USUARIO_ADMIN && password == PASSWORD_ADMIN;
}

void listarAlumnos(const vector<Alumno>& alumnos) {
    if (alumnos.empty()) {
        cout << "\nNo existen alumnos registrados.\n";
        return;
    }

    cout << "\n================ LISTA DE ALUMNOS ================\n";
    cout << left << setw(12) << "Codigo"
         << setw(25) << "Alumno"
         << setw(12) << "Practica"
         << setw(12) << "Parcial"
         << setw(12) << "Promedio"
         << setw(15) << "Estado" << endl;

    cout << string(88, '-') << endl;
    cout << fixed << setprecision(2);

    for (const Alumno& a : alumnos) {
        cout << left << setw(12) << a.codigo
             << setw(25) << a.nombre
             << setw(12) << a.practica
             << setw(12) << a.parcial
             << setw(12) << a.promedio
             << setw(15) << a.estado << endl;
    }
}

string leerCodigoNormalizado() {
    string codigo;
    getline(cin >> ws, codigo);

    if (!codigoValido(codigo)) {
        return "";
    }

    return completarCodigo(codigo);
}

void buscarAlumno(const vector<Alumno>& alumnos) {
    if (alumnos.empty()) {
        cout << "\nNo existen alumnos registrados.\n";
        return;
    }

    string codigo;

    cout << "\nIngrese el codigo del alumno: ";
    codigo = leerCodigoNormalizado();

    if (codigo.empty()) {
        cout << "Codigo invalido. Debe tener solo numeros y maximo 8 digitos.\n";
        return;
    }

    int pos = buscarIndiceAlumno(alumnos, codigo);

    if (pos == -1) {
        cout << "No se encontro al alumno.\n";
        return;
    }

    const Alumno& a = alumnos[pos];

    cout << "\nCodigo: " << a.codigo << endl;
    cout << "Alumno: " << a.nombre << endl;
    cout << "Practica: " << a.practica << endl;
    cout << "Parcial: " << a.parcial << endl;
    cout << "Promedio: " << fixed << setprecision(2) << a.promedio << endl;
    cout << "Estado: " << a.estado << endl;
}

void registrarAlumno(vector<Alumno>& alumnos) {
    Alumno a;

    cout << "\nCodigo del alumno: ";
    a.codigo = leerCodigoNormalizado();

    if (a.codigo.empty()) {
        cout << "Codigo invalido. Debe tener solo numeros y maximo 8 digitos.\n";
        cout << "Ejemplo: si escribe 201, se guardara como 00000201.\n";
        return;
    }

    if (buscarIndiceAlumno(alumnos, a.codigo) != -1) {
        cout << "El codigo ya existe. Use la opcion editar notas.\n";
        return;
    }

    cout << "Nombre completo del alumno: ";
    getline(cin >> ws, a.nombre);

    if (!nombreValido(a.nombre)) {
        cout << "Nombre invalido. Solo debe contener letras y espacios.\n";
        return;
    }

    a.practica = leerNota("Nota de practica (0 - 20): ");
    a.parcial = leerNota("Nota parcial (0 - 20): ");

    a.promedio = calcularPromedio(a.practica, a.parcial);
    a.estado = obtenerEstado(a.promedio);

    alumnos.push_back(a);
    guardarAlumnos(alumnos);

    cout << "\nAlumno registrado correctamente.\n";
    cout << "Codigo guardado: " << a.codigo << endl;
    cout << "Los reportes pueden generarse desde el menu principal.\n";
}

void editarNotas(vector<Alumno>& alumnos) {
    if (alumnos.empty()) {
        cout << "\nNo existen alumnos registrados.\n";
        return;
    }

    string codigo;

    cout << "\nIngrese el codigo del alumno a editar: ";
    codigo = leerCodigoNormalizado();

    if (codigo.empty()) {
        cout << "Codigo invalido. Debe tener solo numeros y maximo 8 digitos.\n";
        return;
    }

    int pos = buscarIndiceAlumno(alumnos, codigo);

    if (pos == -1) {
        cout << "No se encontro al alumno.\n";
        return;
    }

    cout << "Alumno encontrado: " << alumnos[pos].nombre << endl;

    alumnos[pos].practica = leerNota("Nueva nota de practica (0 - 20): ");
    alumnos[pos].parcial = leerNota("Nueva nota parcial (0 - 20): ");

    alumnos[pos].promedio = calcularPromedio(alumnos[pos].practica, alumnos[pos].parcial);
    alumnos[pos].estado = obtenerEstado(alumnos[pos].promedio);

    guardarAlumnos(alumnos);

    cout << "\nNotas actualizadas correctamente.\n";
    cout << "Recuerde generar nuevamente los reportes.\n";
}

void eliminarAlumno(vector<Alumno>& alumnos) {
    if (alumnos.empty()) {
        cout << "\nNo existen alumnos registrados.\n";
        return;
    }

    string codigo;

    cout << "\nIngrese el codigo del alumno a eliminar: ";
    codigo = leerCodigoNormalizado();

    if (codigo.empty()) {
        cout << "Codigo invalido. Debe tener solo numeros y maximo 8 digitos.\n";
        return;
    }

    int pos = buscarIndiceAlumno(alumnos, codigo);

    if (pos == -1) {
        cout << "No se encontro al alumno.\n";
        return;
    }

    cout << "Alumno encontrado: " << alumnos[pos].nombre << endl;
    cout << "Seguro que desea eliminarlo? (s/n): ";

    char confirmacion;
    cin >> confirmacion;

    if (confirmacion == 's' || confirmacion == 'S') {
        alumnos.erase(alumnos.begin() + pos);
        guardarAlumnos(alumnos);

        cout << "\nAlumno eliminado correctamente.\n";
        cout << "Recuerde generar nuevamente los reportes.\n";
    } else {
        cout << "Operacion cancelada.\n";
    }
}

void mostrarEstadisticas(const vector<Alumno>& alumnos) {
    if (alumnos.empty()) {
        cout << "\nNo existen alumnos registrados para mostrar estadisticas.\n";
        return;
    }

    int aprobados = 0;
    int desaprobados = 0;

    for (const Alumno& a : alumnos) {
        if (a.estado == "Aprobado") {
            aprobados++;
        } else {
            desaprobados++;
        }
    }

    cout << "\n=============== ESTADISTICAS ===============\n";
    cout << "Total de alumnos: " << alumnos.size() << endl;
    cout << "Aprobados: " << aprobados << endl;
    cout << "Desaprobados: " << desaprobados << endl;

    double porcentaje = (aprobados * 100.0) / alumnos.size();
    cout << "Porcentaje de aprobacion: " << fixed << setprecision(2) << porcentaje << "%\n";
}

void mostrarMenu() {
    cout << "\n============== MENU PRINCIPAL ==============\n";
    cout << "1. Listar alumnos\n";
    cout << "2. Buscar alumno\n";
    cout << "3. Registrar alumno\n";
    cout << "4. Editar notas\n";
    cout << "5. Eliminar alumno\n";
    cout << "6. Generar reportes\n";
    cout << "7. Ver estadisticas\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    vector<Alumno> alumnos = cargarAlumnos();

    if (!iniciarSesion()) {
        cout << "Login incorrecto. Acceso denegado.\n";
        return 0;
    }

    cout << "\nBienvenido, administrador.\n";

    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        if (cin.fail()) {
            limpiarBuffer();
            cout << "Opcion invalida.\n";
            continue;
        }

        switch (opcion) {
            case 1:
                listarAlumnos(alumnos);
                break;
            case 2:
                buscarAlumno(alumnos);
                break;
            case 3:
                registrarAlumno(alumnos);
                break;
            case 4:
                editarNotas(alumnos);
                break;
            case 5:
                eliminarAlumno(alumnos);
                break;
            case 6:
                generarReportes(alumnos);
                break;
            case 7:
                mostrarEstadisticas(alumnos);
                break;
            case 8:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 8);

    return 0;
}