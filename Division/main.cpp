#include <iostream>
#include <string>
using namespace std;

// Función para sumar dos números binarios
string sumaBinaria(string bin1, string bin2) {
    int acarreo = 0;
    // Usamos un long int para que pueda almacenar valores grandes.
    long int n = bin1.size() - 1;
    string resultado = "";

    // Recorremos de derecha a izquierda.
    for (long int i = n; i >= 0; i--) {
        // Convertimos el carácter a su valor numérico.
        int bit1 = bin1[i] - '0';
        int bit2 = bin2[i] - '0';
        // Sumamos los bits y el acarreo
        int suma = bit1 + bit2 + acarreo;
        // Añadimos el resultado al string.
        // %2 para obtener el bit de la suma.
        resultado = char((suma % 2) + '0') + resultado;
        // Calculamos el acarreo para la siguiente iteración.
        acarreo = suma / 2;
    }

    return resultado;
}

// Función para restar dos números binarios
string restaBinaria(string bin1, string bin2) {
    int acarreo = 0;
    long int n = bin1.size() - 1;
    string resultado = "";

    for (long int i = n; i >= 0; i--) {
        int bit1 = bin1[i] - '0';
        int bit2 = bin2[i] - '0' + acarreo;

        if (bit1 < bit2) {
            // Cogemos "prestado" un 1 del siguiente bit.
            resultado = char((bit1 + 2 - bit2) + '0') + resultado;
            // Establecemos el acarreo a 1 para la siguiente iteración
            acarreo = 1;
        } else {
            resultado = char((bit1 - bit2) + '0') + resultado;
            acarreo = 0;
        }
    }

    return resultado;
}

// Función principal para la división con restauración
void divisionConRestauracion(string Q, string M) {
    long int n = Q.size();
    // Inicializamos el acumulador A con ceros
    string A(n, '0');

    cout << "Estado inicial: A = " << A << ", Q = " << Q << endl;

    for (int i = 0; i < n; i++) {
        // Paso 1: Desplazar A y Q a la izquierda
        A = A.substr(1) + Q[0]; // Desplazamos A a la izquierda y añadimos el primer bit de Q.
        Q = Q.substr(1) + '0';  // Desplazamos Q a la izquierda y añadimos un 0 al final.

        cout << "\nCiclo " << i + 1 << " (desplazamiento): A = " << A << ", Q = " << Q << endl;

        // Paso 2: Resta A = A - M
        string A_original = A; // Guardamos una copia de A antes de la resta.
        A = restaBinaria(A, M); // Restamos A - M.

        cout << "Ciclo " << i + 1 << " (resta): A = " << A << endl;

        // Paso 3: Evaluar si A es negativo
        if (A[0] == '1') { // Si el primer bit de A es 1, es negativo.
            A = A_original; // Restauramos A al valor anterior a la resta.
            cout << "Ciclo " << i + 1 << " (restauración): A = " << A << endl;
        } else {
            Q[n - 1] = '1'; // Si A no es negativo, ajustamos el último bit de Q a 1.
        }

        cout << "Ciclo " << i + 1 << " (ajuste Q): Q = " << Q << endl;
    }

    // Resultados finales
    cout << "\nResultados finales:\n";
    cout << "Cociente (Q) = " << Q << endl;
    cout << "Residuo (A) = " << A << endl;
}

int main() {
    // Entradas del usuario
    string dividendo, divisor;
    cout << "Introduce el dividendo en binario: ";
    cin >> dividendo;
    cout << "Introduce el divisor en binario: ";
    cin >> divisor;

    // El nº de bits será el máximos entre el dividendo y el divisor.
    float bits = max(dividendo.size(), divisor.size());
    while (dividendo.size() < bits) dividendo = "0" + dividendo;
    while (divisor.size() < bits) divisor = "0" + divisor;

    // Ejecutar el algoritmo de división con restauración.
    divisionConRestauracion(dividendo, divisor);

    return 0;
}
