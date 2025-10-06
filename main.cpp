#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <new>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int capacidad = 50;
    int usados = 0;        // total encolados (incluye despachados)
    int frente = 0;        // índice del posible siguiente 'E' (se va moviendo)
    // arreglos paralelos
    int* id = new(nothrow) int[capacidad];
    double* peso = new(nothrow) double[capacidad];
    string* destino = new(nothrow) string[capacidad];
    int* prioridad = new(nothrow) int[capacidad];
    char* estado = new(nothrow) char[capacidad];
    if (!id || !peso || !destino || !prioridad || !estado) {
        cout << "No hubo memoria para iniciar.\n";
        delete[] id; delete[] peso; delete[] destino; delete[] prioridad; delete[] estado;
        return 1;
    }
    cout << "--- Sistema de Despacho Logistico MegaEnvio (Modo Punteros) ---\n\n";
    cout << "Inicializando sistema con capacidad para " << capacidad << " paquetes...\n";
    cout << "Capacidad actual: " << capacidad << ". Paquetes en cola: 0.\n\n";

    auto limpiarLinea = [](){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    };
    auto crecer = [&](int nuevaCap) -> bool {
        // esta parte duplica la capacidad cuando hace falta
        int* id2 = new(nothrow) int[nuevaCap];
        double* peso2 = new(nothrow) double[nuevaCap];
        string* destino2 = new(nothrow) string[nuevaCap];
        int* prioridad2 = new(nothrow) int[nuevaCap];
        char* estado2 = new(nothrow) char[nuevaCap];
        if (!id2 || !peso2 || !destino2 || !prioridad2 || !estado2) {
            delete[] id2; delete[] peso2; delete[] destino2; delete[] prioridad2; delete[] estado2;
            return false;
        }
        for (int i = 0; i < usados; ++i) {
            id2[i] = id[i];
            peso2[i] = peso[i];
            destino2[i] = destino[i];
            prioridad2[i] = prioridad[i];
            estado2[i] = estado[i];
        }
        delete[] id; delete[] peso; delete[] destino; delete[] prioridad; delete[] estado;
        id = id2; peso = peso2; destino = destino2; prioridad = prioridad2; estado = estado2;
        capacidad = nuevaCap;
        return true;
    };
    auto avanzarFrente = [&](){
        while (frente < usados && estado[frente] != 'E') frente++;
    };
    int opcion;
    cout << fixed << setprecision(2);
    while (true) {
        cout << "\nSeleccione una operacion:\n";
        cout << "1. Agregar Paquete (Encolar)\n";
        cout << "2. Despachar Paquete (Desencolar)\n";
        cout << "3. Inspeccionar Frente de Cola\n";
        cout << "4. Reporte por Destino\n";
        cout << "5. Salir (Liberar Memoria)\n\n";
        cout << "Opcion seleccionada: ";
        if (!(cin >> opcion)) { cout << "Entrada invalida.\n"; return 0; }
        limpiarLinea();
        if (opcion == 1) {
            // encolar
            if (usados == capacidad) {
                int nuevaCap = capacidad * 2;
                if (!crecer(nuevaCap)) {
                    cout << "No se pudo expandir memoria.\n";
                    continue;
                } else {
                    cout << "Capacidad duplicada a " << capacidad << ".\n";
                }
            }
            int nid; double npeso; string ndest; int nprio;
            cout << "Ingrese ID: ";
            if (!(cin >> nid)) { cout << "ID invalido.\n"; cin.clear(); limpiarLinea(); continue; }
            limpiarLinea();
            cout << "Peso (kg): ";
            if (!(cin >> npeso)) { cout << "Peso invalido.\n"; cin.clear(); limpiarLinea(); continue; }
            limpiarLinea();
            cout << "Destino: ";
            getline(cin, ndest);
            if (ndest.empty()) { cout << "Destino vacio.\n"; continue; }
            cout << "Prioridad (1-3): ";
            if (!(cin >> nprio)) { cout << "Prioridad invalida.\n"; cin.clear(); limpiarLinea(); continue; }
            limpiarLinea();
            if (nprio < 1 || nprio > 3) { cout << "Prioridad fuera de rango.\n"; continue; }
            id[usados] = nid;
            peso[usados] = npeso;
            destino[usados] = ndest;
            prioridad[usados] = nprio;
            estado[usados] = 'E';
            usados++;
            // por si el frente estaba al final, lo recolocamos
            if (frente >= usados - 1 && estado[usados - 1] == 'E') frente = usados - 1;
            cout << "Paquete " << nid << " encolado. Capacidad utilizada: " << usados << "/" << capacidad << ".\n";
        }
        else if (opcion == 2) {
            // desencolar (FIFO lógico)
            avanzarFrente();
            if (frente >= usados) {
                cout << "No hay paquetes en cola.\n";
                continue;
            }
            cout << "Despachando paquete...\n";
            estado[frente] = 'D';
            cout << "Paquete " << id[frente] << " despachado con exito. Estado: 'D'.\n";
            frente++;
            avanzarFrente(); // esta linea hace que el frente apunte al siguiente 'E'
        }
        else if (opcion == 3) {
            // inspeccionar frente
            avanzarFrente();
            if (frente >= usados) {
                cout << "No hay paquetes en cola.\n";
                continue;
            }
            cout << "Frente de la cola:\n";
            cout << "  ID: " << id[frente]
                 << " | Peso: " << peso[frente] << " kg"
                 << " | Destino: " << destino[frente]
                 << " | Prioridad: " << (prioridad[frente] == 1 ? "Alta" : prioridad[frente] == 2 ? "Media" : "Baja")
                 << "\n";
        }
        else if (opcion == 4) {
            // reporte por destino
            string q;
            cout << "Ingrese el destino para el reporte: ";
            getline(cin, q);
            if (q.empty()) { cout << "Destino vacio.\n"; continue; }

            int cuenta = 0;
            double suma = 0.0;
            for (int i = 0; i < usados; ++i) {
                if (estado[i] == 'E' && destino[i] == q) {
                    cuenta++;
                    suma += peso[i];
                }
            }
            cout << "Reporte para destino '" << q << "':\n";
            cout << "  Paquetes En Cola: " << cuenta << "\n";
            if (cuenta > 0) {
                cout << "  Peso Promedio: " << (suma / cuenta) << " kg\n";
            } else {
                cout << "  Peso Promedio: 0.00 kg\n";
            }
        }
        else if (opcion == 5) {
            cout << "Liberando " << capacidad << " bloques de memoria asignada...\n";
            delete[] id; delete[] peso; delete[] destino; delete[] prioridad; delete[] estado;
            cout << "Sistema cerrado. ¡Memoria libre!\n";
            break;
        }
        else {
            cout << "Opcion no valida.\n";
        }
    }
    return 0;
}
