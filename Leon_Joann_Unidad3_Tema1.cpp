#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear"); // Linux/macOS
    #endif
}

void encabezado(){
    // PORTADA DE EL SOFTWARE
    limpiarPantalla();
    cout<<"     *********************************"<<endl;
    cout<<"     ***                           ***"<<endl;
    cout<<"     ***   INVENTARIO DE BEBIDAS   ***"<<endl;
    cout<<"     ***                           ***"<<endl;
    cout<<"     *********************************"<<endl;
    cout<<endl;
}

int validarEnteros(int j, string title) {
    string entrada;
    int numero;
    bool valido = false;

    //Mientras el bool sea falso o la varaible vacía se repite 
    while (!valido || entrada.empty()){
        if (j >= 0) {
            cout << "Ingrese el " << title << " del producto [" << j + 1 << "] : ";
        } else {
            cout << "Ingrese la cantidad de productos: ";
        }

        cin>>entrada;

        // Validar que no esté vacía y que todos los caracteres sean dígitos
        if (!entrada.empty() && all_of(entrada.begin(), entrada.end(), ::isdigit)) {
            numero = stoi(entrada);
            if (numero >= 0) {
                valido = true;
            }
        }
        else{
            //Limpia el cin y evito espacio
            cin.clear();
            if (cin.peek() == '\n') cin.ignore();
        }
    }
    
    return numero;
}

int validarMenu() {
    string entrada;
    int numero;
    bool valido = false;

    //Mientras el bool sea falso o la varaible vacía se repite 
    while (!valido || entrada.empty()){
        
        encabezado();
        cout<<endl;
        cout<<" 1. Visualizar los datos"<<endl;
        cout<<" 2. Suma y promedio de los elementos"<<endl;
        cout<<" 3. Identificar el valor mínimo y el máximo en el arreglo"<<endl;
        cout<<" 4. Contar cuantos elementos son pares e impares"<<endl;
        cout<<" 0. Salir"<<endl;
        cout<<endl;
        cout << "Ingrese una opcion: ";

        cin>>entrada;

        // Validar que no esté vacía y que todos los caracteres sean dígitos
        if (!entrada.empty() && all_of(entrada.begin(), entrada.end(), ::isdigit)) {
            numero = stoi(entrada);
            if (numero >= 0 && numero <=4) {
                valido = true;
            }
        }
        else{
            //Limpia el cin y evito espacio
            cin.clear();
            if (cin.peek() == '\n') cin.ignore();
        }
    }
    
    return numero;
}

string validarAlfanumerico(int j) {
    string entrada;
    bool valido = false;

    // Mientras bool sea falso o el dato vacio se repite la condicion
    while (!valido || entrada.empty()){
        getline(cin, entrada);
        for (char c : entrada) {
            if (isalnum(c)) {  // si no es letra ni número
                valido = true;
                break;
            }
        }

        if (!valido || entrada.empty()) {
         
            cout<<"Ingrese el nombre del producto ["<<j+1<<"] : ";
        }

    } 

    return entrada;
}

void leerVectores(int n, vector<string>& nombre, vector<int>& stock, vector<int>& anio){
    //For para recorrer el vector y leer los datos uno por uno
    for(int i = 0; i < n; i++){
        cout<<endl;
        nombre[i] = validarAlfanumerico(i);
        stock[i] = validarEnteros(i, "stock");
        anio[i] = validarEnteros(i, "anio de caducidad");
    }
}

void sumaPromedio(vector<int> vector, string txt, int n){
    int suma = 0, prom = 0;
    cout<<"      SUMA Y PROMEDIO DEL "<<txt<<"      "<<endl;
    cout<<"        ----------------------------      "<<endl;
    
    for(int j=0;j<n;j++){
        // suma cada valor por el indice
        suma += vector[j];
    }

    // Calculo el pormedio dividinedo el total de la suma por el tamaño del vector
    prom = suma/n;

    cout<<endl;
    cout<<"LA SUMA DEL "<<txt<<" = "<<suma<<endl;
    cout<<endl;
    cout<<"EL PROMEDIO DEL "<<txt<<" = "<<prom<<endl;
}

int menor(int min,int pos, int n, vector<int> vector){
    
    // Termina la función recursiva cuando la posicion sea igual o mayor al tamaño del vector
    if(pos>=n){
        return min;
    }
    // Si el valor es menor al actual, la variable min adiquiere el nuevo valor
    if(vector[pos] < min){
        min = vector[pos];
    }
    // Función recursiva aumentando la posicion del vector
    return menor(min,pos + 1,n,vector);
}

int mayor(int max,int pos, int n, vector<int> vector){

    // Termina la función recursiva cuando la posicion sea igual o mayor al tamaño del vector
    if(pos>=n){
        return max;
    }
    // Si el valor es mayor al actual, la variable min adiquiere el nuevo valor
    if(vector[pos] > max){
        max = vector[pos];
    }
    // Función recursiva aumentando la posicion del vector
    return mayor(max,pos + 1,n,vector);
}

int pares(int n, vector<int> vector){ 
    int total = 0;
    for(int i=0;i<n;i++){
        // Si el residuo del valor del vector es 0 quiere decir que es par y sea agregar 1 al total
        if(vector[i] % 2 == 0){
            total++;
        }
    }
    return total;
}

int impares(int n, vector<int> vector){ 
    int total = 0;
    for(int i=0;i<n;i++){
          // Si el residuo del valor del vector es 1 quiere decir que es impar y sea agregar 1 al total
        if(vector[i] % 2 == 1){
            total++;
        }
    }
    return total;
}

void opcionesMenu(vector<string>& nombre, vector<int>& stock, vector<int>& anio, int opt, int n){
    switch (opt)
    {
        case 1:
        {
            encabezado();
            cout<<"      VISUALIZACION DE LOS DATOS      "<<endl;
            cout<<"     ----------------------------      "<<endl;
            cout<<"Index  ||  Nombre    ||  Stock    ||  Anio Caducidad "<<endl;
            for(int i=0; i<n;i++){
                cout<<"   "<<i+1<<"   "<<"    "<<  nombre[i] <<"           "<< stock[i] << "              " <<anio[i]<<endl;
            }
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;
        case 2:
        {
            encabezado();
            sumaPromedio(stock,"VECTOR STOCK",n);
            cout<<endl;
            sumaPromedio(anio,"VECTOR ANIO CADUCIDAD",n);
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

        case 3: 
        {
            encabezado();
            int min = 0, max = 0;
            cout<<"         VALOR MINIMO Y MAXIMO "<<endl;
            cout<<"     ----------------------------      "<<endl;
            cout<<endl;
            min = menor(stock[0],1,n,stock);
            max = mayor(stock[0],1,n,stock);
            cout<<"Vector Stock: minimo = "<<min<<" ; mayor = "<<max<<endl;
            cout<<endl;
            min = menor(anio[0],1,n,anio);
            max = mayor(anio[0],1,n,anio);
            cout<<"Vector Anio Caducidad: minimo = "<<min<<" ; mayor = "<<max<<endl;
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

        case 4:
        {
            encabezado();
            int par = 0, imp = 0;
            cout<<"            PARES E IMPARES "<<endl;
            cout<<"     ----------------------------      "<<endl;
            cout<<endl;
            par = pares(n,stock);
            imp = impares(n,stock);
            cout<<"Vector Stock: pares = "<<par<<" ; impares = "<<imp<<endl;
            cout<<endl;
            par = pares(n,anio);
            imp = impares(n,anio);
            cout<<"Vector Anio Caducidad: pares = "<<par<<" ; impares = "<<imp<<endl;
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;
    
        default:
        encabezado();    
        cout<<"GRACIAS POR USAR NUESTRO INVENTARIO DE BEBIDAS !"<<endl;
        system("read -p 'Presione enter para continuar ...'");
        break;
    }
}

void showMenu(vector<string>& nombre, vector<int>& stock, vector<int>& anio, int& n){
    int option;
    //Mientras la opcion no pase la validación o sea diferente de 0 el ciclo se repite
    do
    {
        option = validarMenu();
        opcionesMenu(nombre,stock,anio,option,n);
    } while (option != 0);
    
}

int main() {
    //Declaración de variables y vectores
    int n;
    encabezado();
    n = validarEnteros(-1,"none");
    vector<string> nombre(n);
    vector<int> stock(n);
    vector<int> anio(n);
    leerVectores(n,nombre,stock,anio);
    showMenu(nombre,stock,anio,n);
    return 0;
}
