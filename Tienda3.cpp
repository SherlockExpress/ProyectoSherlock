#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Pedido {
    vector<string> productos;
public:
    Pedido(const vector<string>& prods) : productos(prods) {}

    void mostrar() const {
        cout << "Productos del pedido:\n";
        for (const auto& producto : productos) {
            cout << "- " << producto << '\n';
        }
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

        for (size_t i = 0; i < historialPedidos.size(); ++i) {
            cout << "\nPedido #" << (i + 1) << ":\n";
            historialPedidos[i].mostrar();
        }
    }
};

void mostrarMenu() {
    cout << "\n--- Sistema de Pedidos ---\n";
    cout << "1. Agregar producto al pedido actual\n";
    cout << "2. Mostrar productos del pedido actual\n";
    cout << "3. Confirmar pedido\n";
    cout << "4. Ver historial de pedidos\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    Cliente cliente;
    vector<string> pedidoActual;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // limpiar salto de línea

        switch (opcion) {
            case 1: {
                string producto;
                cout << "Ingrese el nombre del producto: ";
                getline(cin, producto);
                pedidoActual.push_back(producto);
                cout << "Producto agregado al pedido actual.\n";
                break;
            }

            case 2: {
                if (pedidoActual.empty()) {
                    cout << "El pedido actual está vacío.\n";
                } else {
                    cout << "Productos del pedido actual:\n";
                    for (const auto& prod : pedidoActual) {
                        cout << "- " << prod << '\n';
                    }
                }
                break;
            }

            case 3: {
                if (pedidoActual.empty()) {
                    cout << "No se puede confirmar un pedido vacío.\n";
                } else {
                    Pedido nuevoPedido(pedidoActual);
                    cliente.agregarPedido(nuevoPedido);
                    cout << "Pedido confirmado.\n";
                    pedidoActual.clear();
                }
                break;
            }

            case 4: {
                cliente.mostrarHistorial();
                break;
            }

            case 5: {
                cout << "Gracias por usar el sistema de pedidos.\n";
                break;
            }

            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 5);

    return 0;
}
