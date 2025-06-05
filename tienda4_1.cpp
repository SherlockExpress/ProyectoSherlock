#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

using namespace std;

class Producto {
public:
    int id;
    string nombre;
    double precio;

    Producto() : id(0), nombre(""), precio(0.0) {}

    Producto(int id, const string& nombre, double precio)
        : id(id), nombre(nombre), precio(precio) {}

    void mostrar() const {
        cout << "ID: " << id
             << ", Nombre: " << nombre
             << ", Precio: $" << fixed << setprecision(2) << precio
             << '\n';
    }
    // para ordenar los productos 
    bool operator<(const Producto& otro) const {
        return precio < otro.precio;
    }
};

class Pedido {
    vector<Producto> productos;

public:
    Pedido(const vector<Producto>& prods) : productos(prods) {}

    void mostrar() const {
        double total = 0.0;
        cout << "Productos del pedido:\n";
        for (int i = 0; i < (int)productos.size(); ++i) {
            productos[i].mostrar();
            total += productos[i].precio;
        }
        cout << "Total del pedido: $" << fixed << setprecision(2) << total << "\n";
    }
};

class Cliente {
    vector<Pedido> historialPedidos;

public:
    void agregarPedido(const Pedido& p) {
        historialPedidos.push_back(p);
    }

    void mostrarHistorial() const {
        if (historialPedidos.empty()) {
            cout << "No hay pedidos realizados.\n";
            return;
        }

        for (int i = 0; i < (int)historialPedidos.size(); ++i) {
            cout << "\nPedido #" << (i + 1) << ":\n";
            historialPedidos[i].mostrar();
        }
    }
};

void mostrarMenu() {
    cout << "\n--- Sistema de Pedidos ---\n";
    cout << "1. Mostrar catalogo de productos\n";
    cout << "2. Agregar producto al pedido actual (por ID)\n";
    cout << "3. Mostrar productos del pedido actual\n";
    cout << "4. Confirmar pedido\n";
    cout << "5. Ver historial de pedidos\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
}

void mostrarCatalogo(const unordered_map<int, Producto>& catalogo) {
    cout << "Catalogo de productos:\n";
    for (auto it = catalogo.begin(); it != catalogo.end(); ++it) {
        it->second.mostrar();
    }
}

int main() {
    unordered_map<int, Producto> catalogo;
    catalogo[1] = Producto(1, "Pan", 1.20);
    catalogo[2] = Producto(2, "Leche", 2.50);
    catalogo[3] = Producto(3, "Queso", 4.75);
    catalogo[4] = Producto(4, "Arroz", 3.10);
    catalogo[5] = Producto(5, "Aceite", 5.90);
    catalogo[6] = Producto(6, "Galletas", 2.00);
    catalogo[7] = Producto(7, "Fideos", 1.90);

    Cliente cliente;
    vector<Producto> pedidoActual;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                mostrarCatalogo(catalogo);
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese el ID del producto a agregar: ";
                cin >> id;
                auto it = catalogo.find(id);
                if (it != catalogo.end()) {
                    pedidoActual.push_back(it->second);
                    cout << "Producto agregado al pedido actual.\n";
                } else {
                    cout << "ID invalido. Intente nuevamente.\n";
                }
                break;
            }
            case 3: {
                if (pedidoActual.empty()) {
                    cout << "El pedido actual esta vacio.\n";
                } else {
                    cout << "Productos del pedido actual:\n";
                    double total = 0.0;
                    for (int i = 0; i < (int)pedidoActual.size(); ++i) {
                        pedidoActual[i].mostrar();
                        total += pedidoActual[i].precio;
                    }
                    cout << "Total del pedido actual: $" 
                         << fixed << setprecision(2) << total << "\n";
                }
                break;
            }
            case 4: {
                if (pedidoActual.empty()) {
                    cout << "No se puede confirmar un pedido vacio.\n";
                } else {
                    Pedido nuevoPedido(pedidoActual);
                    cliente.agregarPedido(nuevoPedido);
                    cout << "Pedido confirmado.\n";
                    pedidoActual.clear();
                }
                break;
            }
            case 5: {
                cliente.mostrarHistorial();
                break;
            }
            case 6: {
                cout << "Gracias por usar el sistema de pedidos.\n";
                break;
            }
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }

    } while (opcion != 7);

    return 0;
}
