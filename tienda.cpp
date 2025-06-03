#include <bits/stdc++.h>
using namespace std;

// Clase base Producto
class Producto {
protected:
    string nombre;
    double precio;
    int codigo;
    int stock;

public:
    Producto(string nombre, double precio, int codigo, int stock)
        : nombre(nombre), precio(precio), codigo(codigo), stock(stock) {}

    virtual ~Producto() {}

    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getCodigo() const { return codigo; }
    int getStock() const { return stock; }

    void setStock(int nuevoStock) { stock = nuevoStock; }

    virtual void mostrarInfo() const {
        cout << "Producto: " << nombre
             << " | Precio: $" << precio
             << " | Codigo: " << codigo
             << " | Stock: " << stock << endl;
    }
};

// Producto fisico
class ProductoFisico : public Producto {
    double peso;

public:
    ProductoFisico(string nombre, double precio, int codigo, int stock, double peso)
        : Producto(nombre, precio, codigo, stock), peso(peso) {}

    void mostrarInfo() const override {
        Producto::mostrarInfo();
        cout << "  Tipo: Fisico | Peso: " << peso << "kg" << endl;
    }
};

// Producto digital
class ProductoDigital : public Producto {
    string formato;

public:
    ProductoDigital(string nombre, double precio, int codigo, int stock, string formato)
        : Producto(nombre, precio, codigo, stock), formato(formato) {}

    void mostrarInfo() const override {
        Producto::mostrarInfo();
        cout << "  Tipo: Digital | Formato: " << formato << endl;
    }
};

// Pedido
class Pedido {
    vector<shared_ptr<Producto>> productos;
    double total;

public:
    Pedido(const vector<shared_ptr<Producto>>& productos)
        : productos(productos), total(0) {
        for (auto& p : productos)
            total += p->getPrecio();
    }

    void mostrarFactura() const {
        cout << "\nFactura del Pedido:" << endl;
        for (auto& p : productos)
            p->mostrarInfo();
        cout << "Total a pagar: $" << total << "\n" << endl;
    }

    double getTotal() const { return total; }
};

// Cliente
class Cliente {
    string nombre;
    int id;
    vector<Pedido> historial;

public:
    Cliente(string nombre, int id) : nombre(nombre), id(id) {}

    void agregarPedido(const Pedido& p) {
        historial.push_back(p);
    }

    void mostrarHistorial() const {
        cout << "\nHistorial de pedidos de " << nombre << ":" << endl;
        if (historial.empty()) {
            cout << "  No hay pedidos en el historial." << endl;
        } else {
            for (auto& p : historial)
                p.mostrarFactura();
        }
    }

    int getId() const { return id; }
};

// Carrito
class Carrito {
    vector<shared_ptr<Producto>> productos;
    stack<shared_ptr<Producto>> acciones; // pila para deshacer

public:
    void agregarProducto(shared_ptr<Producto> p) {
        productos.push_back(p);
        acciones.push(p);
        cout << "Producto agregado: " << p->getNombre() << endl;
    }

    void deshacerUltimo() {
        if (!acciones.empty()) {
            auto ultimo = acciones.top();
            acciones.pop();
            auto it = find(productos.begin(), productos.end(), ultimo);
            if (it != productos.end())
                productos.erase(it);
            cout << "Accion deshecha: se elimino " << ultimo->getNombre() << endl;
        } else {
            cout << "No hay acciones para deshacer." << endl;
        }
    }

    double calcularTotal() const {
        double total = 0;
        for (auto& p : productos)
            total += p->getPrecio();
        return total;
    }

    vector<shared_ptr<Producto>> obtenerProductos() const {
        return productos;
    }

    void mostrarCarrito() const {
        cout << "\nCarrito actual:" << endl;
        if (productos.empty()) {
            cout << "  El carrito esta vacio." << endl;
        } else {
            for (auto& p : productos)
                p->mostrarInfo();
            cout << "Total: $" << calcularTotal() << "\n" << endl;
        }
    }

    void vaciar() {
        productos.clear();
        while (!acciones.empty())
            acciones.pop();
    }
};

int main() {
    map<int, shared_ptr<Producto>> catalogo;
    queue<Pedido> colaPedidos;

    // Crear productos de prueba
    catalogo[1] = make_shared<ProductoFisico>("Laptop", 800.0, 1, 10, 2.5);
    catalogo[2] = make_shared<ProductoDigital>("Ebook C++", 15.0, 2, 100, "PDF");
    catalogo[3] = make_shared<ProductoFisico>("Mouse Gamer", 25.0, 3, 50, 0.2);
    catalogo[4] = make_shared<ProductoDigital>("Curso Online", 100.0, 4, 500, "Video");

    Cliente cliente("Juan", 101);
    Carrito carrito;

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
            for (auto& [codigo, prod] : catalogo)
                prod->mostrarInfo();
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
