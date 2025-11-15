#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <iomanip> // Para std::setw y std::left
#include <sstream> // Para std::ostringstream
#include <limits> // Para std::numeric_limits
#include <fstream> // Para manejo de archivos
using namespace std;

// ─────────────────────────────────────────────────────────────
// Carlxoso Full Stack
// ─────────────────────────────────────────────────────────────

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void efectoCarga() {
    color(11);
    cout << "\n\t\tProcesando";
    for (int i = 0; i < 6; i++) {
        cout << ".";
        Sleep(300);
    }
    cout << endl;
    color(7);
}

void mostrarHora() {
    time_t ahora = time(0);
    tm tiempo;
    localtime_s(&tiempo, &ahora);
    cout << "\t\tFecha: "
         << tiempo.tm_mday << "/"
         << tiempo.tm_mon + 1 << "/"
         << tiempo.tm_year + 1900 << "  "
         << "Hora: " << tiempo.tm_hour << ":"
         << tiempo.tm_min << ":"
         << tiempo.tm_sec << endl;
}

// Funcion para guardar el historial de compras en un archivo
void guardarHistorial(string nombre, string productos[], float precios[], int cantidades[], float total, int contador) {
    ofstream archivo("historial_compras.txt", ios::app); // Abrir en modo de añadir
    if (archivo.is_open()) {
        archivo << "Cliente: " << nombre << "\n";
        archivo << "Productos:\n";
        for (int i = 0; i < contador; i++) {
            archivo << "- " << productos[i] << " | Cantidad: " << cantidades[i] << " | Precio: $" << precios[i] << "\n";
        }
        archivo << "Total: $" << total << "\n";
        archivo << "---------------------------------------------\n";
        archivo.close();
    } else {
        cout << "Error al guardar el historial.\n";
    }
}

// Funcion para mostrar el historial de compras
void mostrarHistorial() {
    ifstream archivo("historial_compras.txt");
    if (archivo.is_open()) {
        string linea;
        cout << "\n\t\t==========================================\n";
        cout << "\t\t          HISTORIAL DE COMPRAS\n";
        cout << "\t\t==========================================\n";
        while (getline(archivo, linea)) {
            cout << "\t\t" << linea << "\n"; // Agregar tabulacion para centrar
        }
        cout << "\t\t==========================================\n";
        archivo.close();
    } else {
        cout << "\n\t\tNo hay historial de compras disponible.\n";
    }
}

// Factura del pedido con detalle.
void generarFactura(string nombre, string cedula, string direccion, string correo,
    string productos[], float precios[], int quantities[], float descuentos[], int contador) {

    float subtotal = 0;
    for (int i = 0; i < contador; i++) {
        subtotal += (precios[i] - descuentos[i]) * quantities[i];
    }

    float iva = subtotal * 0.15;
    float total = subtotal + iva;

    efectoCarga();

    color(9);
    cout << "\n\t\t=================================================================\n";
    cout << "\t\t                        FACTURA TIENDA DELL\n";
    cout << "\t\t=================================================================\n";
    color(7);

    mostrarHora();
    cout << "\t\t-----------------------------------------------------------------\n";

    if (nombre != "Consumidor Final") {
        cout << "\t\tCliente: " << nombre << endl;
        cout << "\t\tCedula: " << cedula << endl;
        cout << "\t\tDireccion: " << direccion << endl;
        cout << "\t\tCorreo: " << correo << endl;
    } else {
        cout << "\t\tCliente: Consumidor Final\n";
    }

    cout << "\t\t-----------------------------------------------------------------\n";
    color(11);
    cout << "\t\tDETALLE DE PRODUCTOS:\n";
    color(7);
    cout << "\t\t-----------------------------------------------------------------\n";
    cout << "\t\tProducto                      Cant  P.Unit     Desc.       Total\n";
    cout << "\t\t-----------------------------------------------------------------\n";

    for (int i = 0; i < contador; i++) {
        cout << fixed << setprecision(2); // Establecer 2 decimales
        cout << "\t\t" << left << setw(30) << productos[i]
             << setw(6) << quantities[i]
             << "$" << setw(10) << precios[i]
             << "$" << setw(10) << descuentos[i]
             << "$" << (precios[i] - descuentos[i]) * quantities[i] << endl;
    }

    cout << fixed << setprecision(2); // Establecer 2 decimales para totales
    cout << "\t\t-----------------------------------------------------------------\n";
    color(10);
    cout << "\t\tSubtotal: $" << subtotal << endl;
    cout << "\t\tIVA (15%): $" << iva << endl;
    color(14);
    cout << "\t\tTOTAL A PAGAR: $" << total << endl;
    color(7);
    cout << "\t\t-----------------------------------------------------------------\n";
    cout << "\t\tGracias por su compra | Vuelva pronto!\n";
    cout << "\t\t=================================================================\n\n";

    // Guardar el historial de la compra
    guardarHistorial(nombre, productos, precios, quantities, total, contador);

    cout << "\t\tPresione ENTER para volver al menu principal...";
    cin.ignore();
    cin.get();
}

// Funcion para recomendar productos basados en las compras actuales
void recomendarProductos(string productos[], int contador) {
    cout << "\n\t\t==========================================\n";
    cout << "\t\t          RECOMENDACIONES DE PRODUCTOS\n";
    cout << "\t\t==========================================\n";
    for (int i = 0; i < contador; i++) {
        if (productos[i] == "Laptop Dell Inspiron") {
            cout << "\t\t- Mouse Dell Inalambrico\n";
            cout << "\t\t- Base Refrigerante Dell\n";
        } else if (productos[i] == "Monitor Dell 24\"") {
            cout << "\t\t- Cable HDMI\n";
            cout << "\t\t- Soporte para Monitor\n";
        } else if (productos[i] == "Mouse Dell Inalambrico") {
            cout << "\t\t- Teclado Dell Mecanico\n";
            cout << "\t\t- Alfombrilla para Mouse\n";
        } else if (productos[i] == "Teclado Dell Mecanico") {
            cout << "\t\t- Mouse Dell Inalambrico\n";
            cout << "\t\t- Audifonos Dell Pro\n";
        } else if (productos[i] == "Cargador Dell 65W") {
            cout << "\t\t- Adaptador Universal\n";
            cout << "\t\t- Funda Protectora\n";
        }
        // Agregar más recomendaciones según los productos
    }
    cout << "\t\t==========================================\n";
}

// Parte del programa principal.
int main() {
    const int NUM_PRODUCTOS = 10;

    string catalogo[NUM_PRODUCTOS] = {
        "Laptop Dell Inspiron", "Monitor Dell 24\"", "Mouse Dell Inalambrico",
        "Teclado Dell Mecanico", "Cargador Dell 65W", "Laptop Dell XPS 13",
        "Base Refrigerante Dell", "Audifonos Dell Pro", "Disco SSD Dell 1TB", "Impresora Dell Laser"
    };

    float preciosCatalogo[NUM_PRODUCTOS] = { 750, 200, 25, 45, 60, 1200, 35, 80, 150, 300 };
    string promociones[NUM_PRODUCTOS] = {
        "10% de descuento", "Incluye HDMI gratis", "2x1 accesorios inalambricos",
        "15% descuento lanzamiento", "Gratis adaptador universal", "Funda protectora incluida",
        "20% descuento efectivo", "Incluye microfono adicional", "$30 descuento proxima compra",
        "Cartucho inicial gratuito"
    };

    int cantidadMinima[NUM_PRODUCTOS] = { 2, 3, 2, 2, 2, 2, 3, 2, 2, 1 };
    float descuentoMayor[NUM_PRODUCTOS] = { 0.10, 0.05, 0.50, 0.15, 5, 0.10, 0.20, 10, 30, 0 };

    int opcion;
    char continuar;

    do {
        color(9);
        cout << "\n\t\t===============================================\n";
        cout << "\t\t        BIENVENIDO A TIENDA DELL\n";
        cout << "\t\t===============================================\n\n";

        color(10);
        cout << "\t\t1) Realizar pedido de producto\n";
        cout << "\t\t2) Mostrar historial de compras\n";
        cout << "\t\t3) Salir\n\n";

        color(7);
        cout << "\t\tSeleccionate una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string productosCompra[50];
            float preciosCompra[50];
            int cantidadesCompra[50];
            float descuentosCompra[50];
            int contador = 0;

            do {
                color(11);
                cout << "\n\t\t------ CATALOGO DE PRODUCTOS DELL ------\n\n";
                for (int i = 0; i < NUM_PRODUCTOS; i++) {
                    ostringstream precioFormateado;
                    precioFormateado << fixed << setprecision(2) << preciosCatalogo[i];

                    string producto = to_string(i + 1) + ") " + catalogo[i] + " - $" + precioFormateado.str();
                    string promocion = promociones[i];
                    int anchoProducto = 50; // Espacio reservado para el producto
                    int anchoPromocion = 30; // Espacio reservado para la promocion

                    cout << "\t\t" << left << setw(anchoProducto) << producto;
                    color(14); // Cambiar color para las promociones
                    cout << " | " << setw(anchoPromocion) << promocion << endl;
                    color(7); // Restaurar color predeterminado
                }

                // Validacion para seleccionar el numero del producto
                int indice;
                do {
                    color(7);
                    cout << "\n\t\tSeleccione el numero del producto (1-10): ";
                    cin >> indice;

                    if (cin.fail() || indice < 1 || indice > NUM_PRODUCTOS) {
                        color(12);
                        cout << "\t\tEntrada invalida. Por favor, ingrese un numero entre 1 y 10.\n";
                        cin.clear();
                        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    }
                } while (indice < 1 || indice > NUM_PRODUCTOS);
                cin.ignore();

                color(10);
                cout << "\n\t\tProducto: " << catalogo[indice - 1] << endl;
                cout << "\t\tPrecio: $" << preciosCatalogo[indice - 1] << endl;

                color(14);
                cout << "\t\tPromocion: " << promociones[indice - 1] << endl;
                color(7);

                // Validacion para la cantidad deseada
                int cantidad;
                do {
                    color(7);
                    cout << "\n\t\tIngrese la cantidad deseada (mayor a 0): ";
                    cin >> cantidad;

                    if (cin.fail() || cantidad <= 0) {
                        color(12);
                        cout << "\t\tEntrada invalida. Por favor, ingrese un numero mayor a 0.\n";
                        cin.clear();
                        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    }
                } while (cantidad <= 0);
                cin.ignore();

                float descuento = 0;
                if (cantidad >= cantidadMinima[indice - 1]) {
                    if (descuentoMayor[indice - 1] < 1) {
                        descuento = preciosCatalogo[indice - 1] * descuentoMayor[indice - 1];
                    } else {
                        descuento = descuentoMayor[indice - 1];
                    }
                }

                productosCompra[contador] = catalogo[indice - 1];
                preciosCompra[contador] = preciosCatalogo[indice - 1];
                cantidadesCompra[contador] = cantidad;
                descuentosCompra[contador] = descuento;
                contador++;

                color(10);
                cout << "\t\tProducto agregado al carrito.\n";
                if (descuento > 0) {
                    cout << "\t\tDescuento aplicado por compra mayoritaria: $" << descuento << endl;
                }

                // Validacion para continuar (S/N)
                do {
                    color(7);
                    cout << "\n\t\tDesea agregar otro producto? (S/N): ";
                    cin >> continuar;

                    if (cin.fail() || (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n')) {
                        color(12);
                        cout << "\t\tEntrada invalida. Por favor, ingrese 'S' para si o 'N' para no.\n";
                        cin.clear();
                        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    }
                } while (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n');
                cin.ignore();

            } while (continuar == 'S' || continuar == 's');

            // Impresion de la factura del cliente
            int tipoFactura;
            color(10);
            cout << "\n\t\tDesea generar factura?\n";
            cout << "\t\t1) Con datos del cliente\n";
            cout << "\t\t2) Consumidor final\n";
            cout << "\t\t3) No generar factura\n";
            cout << "\t\tOpcion: ";
            cin >> tipoFactura;
            cin.ignore();

            if (tipoFactura == 1) {
                string nombre, cedula, direccion, correo;
                color(7);
                cout << "\n\t\tIngrese su nombre completo: ";
                getline(cin, nombre);
                cout << "\t\tIngrese su cedula: ";
                getline(cin, cedula);
                cout << "\t\tIngrese su direccion: ";
                getline(cin, direccion);
                cout << "\t\tIngrese su correo: ";
                getline(cin, correo);

                generarFactura(nombre, cedula, direccion, correo, productosCompra, preciosCompra, cantidadesCompra, descuentosCompra, contador);
            } else if (tipoFactura == 2) {
                generarFactura("Consumidor Final", "", "", "", productosCompra, preciosCompra, cantidadesCompra, descuentosCompra, contador);
            } else {
                color(8);
                cout << "\n\t\tFactura no generada. Presione ENTER para volver al menu principal...";
                cin.ignore();
                cin.get();
            }

            recomendarProductos(productosCompra, contador);

        } else if (opcion == 2) {
            mostrarHistorial();
        } else if (opcion == 3) {
            color(10);
            cout << "\n\t\tGracias por visitar Tienda Dell. Hasta pronto!\n";
        } else {
            color(12);
            cout << "\n\t\tOpcion no valida. Intente nuevamente.\n\n";
        }

    } while (opcion != 3);

    color(7);
    return 0;
}
