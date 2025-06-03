#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define endl "\n"
#define DBG(x) cerr << #x << " = " << x << endl;
#define LINE cerr << "====================" << endl;
#define forn(n) for(int i = 0; i < n; i++)
#define forin(a, n) for(int i = a; i < n; i++)
#define mostrar(v) if(true) { for(auto &it : v) cout << it << " "; cout << endl; }
#define pb push_back
#define all(v) v.begin(), v.end()
#define fastio ios::sync_with_stdio(false); cin.tie(0);
const ll INF = 1e18;

class Producto {
private:
    string nombre;
    int precio, stock, codigo;

public:
    Producto(string Nombre, int Precio, int Stock, int Codigo)
        : nombre(Nombre), precio(Precio), stock(Stock), codigo(Codigo) {}

    // Getters
    string getNombre() const { return nombre; }
    int getPrecio() const { return precio; }
    int getStock() const { return stock; }
    int getCodigo() const { return codigo; }

    // Setters
    void setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
    void setPrecio(int nuevoPrecio) { precio = nuevoPrecio; }
    void setStock(int nuevoStock) { stock = nuevoStock; }
    void setCodigo(int nuevoCodigo) { codigo = nuevoCodigo; }

    // Método para mostrar info
    void mostrarInfo() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Precio: $" << precio << endl;
        cout << "Stock: " << stock << " unidades" << endl;
        cout << "Codigo: " << codigo << endl;
    }
};

class ProductoFisico: public Producto{

};

class ProductoDigital: public Producto{

};

void mostrarCatalogo(vector<Producto> productos){
    for(int i=0; i<productos.size(); i++){
        
    }
}

int main() {
    fastio;
    vector<Producto> productos = {
    Producto("Mouse Logitech G502", 15000, 10, 1001),
    Producto("Teclado Mecanico HyperX Alloy FPS", 25000, 8, 1002),
    Producto("Auriculares Razer Kraken", 18000, 12, 1003),
    Producto("Monitor Asus 24'' 144Hz", 60000, 5, 1004),
    Producto("Silla Gamer Cougar Armor", 80000, 4, 1005),
    Producto("Placa de Video RTX 3060", 200000, 2, 1006),
    Producto("Procesador Ryzen 5 5600X", 100000, 3, 1007),
    Producto("Memoria RAM 16GB DDR4", 30000, 6, 1008),
    Producto("Gabinete Gamer Redragon", 25000, 7, 1009),
    Producto("Fuente 650W Certificada", 35000, 6, 1010),
    Producto("Alfombrilla Razer Goliathus", 5000, 15, 1011),
    Producto("Webcam Logitech C920", 22000, 4, 1012),
    Producto("Microfono Blue Yeti", 45000, 3, 1013),
    Producto("Control Xbox Series X", 28000, 5, 1014),
    Producto("Joystick DualSense PS5", 32000, 5, 1015),
    Producto("SSD M.2 1TB NVMe", 50000, 6, 1016),
    Producto("Cooler Master Hyper 212", 15000, 8, 1017),
    Producto("Luz LED RGB para Setup", 10000, 10, 1018),
    Producto("Tarjeta Captura Elgato", 70000, 2, 1019),
    Producto("Hub USB 3.0 x4", 8000, 12, 1020)
};

    map<int, Producto> mapa;



    int opcion;
    do {
        cout << "\n==============================\n";
        cout << "       MENU TIENDA ONLINE      \n";
        cout << "==============================\n";
        cout << "1. Ver catalogo\n";
        cout << "2. Agregar producto al carrito\n";
        cout << "3. Ver carrito\n";
        cout << "4. Deshacer ultima accion\n";
        cout << "5. Confirmar pedido\n";
        cout << "6. Ver historial de pedidos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "\nCatalogo de productos:" << endl;
            mostrarCatalogo(productos);
        }
        else if (opcion == 2) {
            int cod;
            cout << "Ingrese codigo de producto: ";
            cin >> cod;
            if (catalogo.count(cod))
                carrito.agregarProducto(catalogo[cod]);
            else
                cout << "Producto no encontrado." << endl;
        }
        else if (opcion == 3) {
            carrito.mostrarCarrito();
        }
        else if (opcion == 4) {
            carrito.deshacerUltimo();
        }
        else if (opcion == 5) {
            auto productos = carrito.obtenerProductos();
            if (productos.empty()) {
                cout << "El carrito esta vacio, no se puede confirmar pedido." << endl;
            } else {
                Pedido p(productos);
                colaPedidos.push(p);
                cliente.agregarPedido(p);
                cout << "\nPedido confirmado. Se agrego a la cola de procesado.\n";
                p.mostrarFactura();
                carrito.vaciar();
            }
        }
        else if (opcion == 6) {
            cliente.mostrarHistorial();
        }
    } while (opcion != 0);

    cout << "\nGracias por usar la tienda. Hasta luego.\n";
    return 0;
}