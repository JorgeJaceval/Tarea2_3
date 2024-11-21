#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <chrono>
#include <utility>

using namespace std;

vector<char> abecedario{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
                                  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                                  'u', 'v', 'w', 'x', 'y', 'z'};

vector <int> cost_insert;
vector <int> cost_delete;
vector <vector <int>> cost_replace;
vector <vector <int>> cost_transpose;

// Costo de Sustitución: Esta función calcula el costo de sustituir el carácter ‘a’ por el carácter ‘b’.
// Parámetros:
// - a : carácter original
// - b : carácter con el que se sustituye 
// Retorno: costo de sustituir ‘a’ por ‘b’
int costo_sub(char a, char b) {
    int costo, pos_a, pos_b;
    pos_a = distance(abecedario.begin(), find(abecedario.begin(), abecedario.end(), a));
    pos_b = distance(abecedario.begin(), find(abecedario.begin(), abecedario.end(), b));
    costo = cost_replace[pos_b][pos_a];
    return costo;
}

// Costo de Inserción: Esta función devuelve el costo de insertar el carácter ‘b’ en la cadena.
// Parámetros:
// - b : carácter a insertar
// Retorno: costo de insertar ‘b’
int costo_ins(char b) {
    int costo, pos_b;
    pos_b = distance(abecedario.begin(), find(abecedario.begin(), abecedario.end(), b));
    costo = cost_insert[pos_b];
    return costo;
}

// Costo de Eliminación: Esta función devuelve el costo de eliminar el carácter ‘a’ de la cadena.
// Parámetros:
// - a : carácter a eliminar
// Retorno: costo de eliminar ‘a’
int costo_del(char a) {
    int costo, pos_a;
    pos_a = distance(abecedario.begin(), find(abecedario.begin(), abecedario.end(), a));
    costo = cost_delete[pos_a];
    return costo;
}

// Costo de Transposición: Esta función devuelve el costo de intercambiar los caracteres ‘a’ y ‘b’ si son adyacentes.
// Parámetros:
// - a : primer carácter a transponer
// - b : segundo carácter a transponer
// Retorno: costo de transponer ‘a’ y ‘b’
int costo_trans(char a, char b) {
    int costo, pos_a, pos_b;
    pos_a = distance(abecedario.begin(), find(abecedario.begin(), abecedario.end(), a));
    pos_b = distance(abecedario.begin(), find(abecedario.begin(), abecedario.end(), b));
    costo = cost_transpose[pos_b][pos_a];
    return costo;
}


int DP_Solver(const string& A, const string& B, int i, int j, vector<vector<int>>& DP) {
    int n = A.length();
    int m = B.length();
    
    if (DP[i][j] != -1) {
        return DP[i][j]; // Retornar si ya fue calculado
    }

    // Casos base
    if (i == n && j == m) {
        return DP[i][j] = 0;
    }
    if (i == n) {
        return DP[i][j] = DP_Solver(A, B, i, j + 1, DP) + costo_ins(B[j]);
    }
    if (j == m) {
        return DP[i][j] = DP_Solver(A, B, i + 1, j, DP) + costo_del(A[i]);
    }

    // Operaciones principales
    int substitute = DP_Solver(A, B, i + 1, j + 1, DP) + costo_sub(A[i], B[j]); 
    int transpose = INT_MAX;
    int delet = DP_Solver(A, B, i + 1, j, DP) + costo_del(A[i]);      
    int insert = DP_Solver(A, B, i, j + 1, DP) + costo_ins(B[j]);       

    if (A[i + 1] == B[j] && A[i] == B[j + 1] && n > (i + 1) && m > (j + 1)) {
        transpose = DP_Solver(A, B, i + 2, j + 2, DP) + costo_trans(A[i], A[i + 1]);
    }

    // mínimo en DP
    return DP[i][j] = min({delet, insert, substitute, transpose});
}

int Brute_Force(const string& A, const string& B, int i, int j) {
    // Caso base: si una de las cadenas está vacía
    if (i == A.length() && j == B.length()) {
        return 0; // Cadenas completas
    } else if (i == A.length()) {
        // Insertar el resto de B
        return costo_ins(B[j]) + Brute_Force(A, B, i, j + 1);
    } else if (j == B.length()) {
        // Eliminar el resto de A
        return costo_del(A[i]) + Brute_Force(A, B, i + 1, j);
    }

    // Cálculo de costos de inserción, eliminación y sustitución
    int delet = costo_del(A[i]) + Brute_Force(A, B, i + 1, j);
    int insert = costo_ins(B[j]) + Brute_Force(A, B, i, j + 1);
    int substitute = costo_sub(A[i], B[j]) + Brute_Force(A, B, i + 1, j + 1);
 
    // Transposición
    int transpose = INT_MAX;
    if (i > 0 && j > 0 && A[i] == B[j - 1] && A[i - 1] == B[j]) {
        transpose = costo_trans(A[i - 1], A[i]) + Brute_Force(A, B, i + 1, j + 1);
    }

    // Devolvemos el valor mínimo entre las operaciones
    return min({insert, delet, substitute, transpose});
}


void Read_matrix(string A, string B, string nombre, vector <vector <int>> & matrix) {

    std::ifstream archivo(nombre); // Abrir archivo en modo lectura

    if (!archivo) {  // Verificar si el archivo se abrió correctamente
        cerr << "No se pudo abrir el archivo." << endl;
    }

    string linea;
    int i = 0;
    int j = 0;
    while (getline(archivo, linea)) { // Leer el archivo línea por línea
        stringstream ss(linea);
        string valor;
        while (ss >> valor) {  // Leer cada palabra en la línea separada por espacios
            matrix[i][j] = stoi(valor);  // Convertir a entero y agregar a la matriz
            j += 1;
        }
        j = 0;
        i += 1;
    }
}

void Read_matrix(string A, string B, string nombre, vector <int> & matrix) {

    ifstream archivo(nombre); // Abrir archivo en modo lectura

    if (!archivo) {  // Verificar si el archivo se abrió correctamente
        cerr << "No se pudo abrir el archivo." << endl;
    }

    string linea;
    int i = 0;
    getline(archivo, linea);  // Leer el archivo línea por línea
    stringstream ss(linea);  // Usamos un stringstream para separar los valores
    string valor;
    while (ss >> valor) {  // Leer cada palabra en la línea separada por espacios
        matrix[i] = stoi(valor);  // Convertir a entero y agregar a la matriz
        i += 1;
    }
            
    }  



void Matrix_maker(string A, string B) {
    // Se inicializa el tamaño de las matrices de c
    cost_insert = vector <int> (26);
    cost_delete = vector <int> (26);
    cost_replace = vector <vector <int>> (26, vector <int> (26, 0));
    cost_transpose = vector <vector <int>> (26, vector <int> (26, 0));   
    
    Read_matrix(A, B, "Matrices_costo/costo_ins.txt", cost_insert);
    Read_matrix(A, B, "Matrices_costo/costo_del.txt", cost_delete);
    Read_matrix(A, B, "Matrices_costo/costo_sub.txt", cost_replace);
    Read_matrix(A, B, "Matrices_costo/costo_trans.txt", cost_transpose);

}

auto Timer_BF(string A, string B, vector <vector <int>> &DP) {

    // Ejecución brute_force

    auto start = chrono::high_resolution_clock::now();
    int resultado = Brute_Force(A, B, 0, 0);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    return elapsed;

}

auto Timer_DP(string A, string B, vector <vector <int>>& DP) {
    // Ejecución DP

    auto start = chrono::high_resolution_clock::now();
    int resultado = DP_Solver(A, B, 0, 0, DP);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    return elapsed;
}

void test(string test_case) {
    string A, B;

    chrono::duration<double, milli> time_BF(0), time_DP(0);

    ifstream archivo(test_case);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << test_case << endl;
    }


    while (getline(archivo, linea)) {
        size_t comaPos = linea.find(',');
        if (comaPos != string::npos) {
            A = linea.substr(0, comaPos);      // Parte antes de la coma es A
            B = linea.substr(comaPos + 1);     // Parte después de la coma es B
        }
        int n = A.length();
        int m = B.length();

        vector <vector <int>> DP (n + 1, vector <int> (m + 1, -1)); // Matriz de mínima edición
        Matrix_maker(A, B);
        time_BF += Timer_BF(A, B, DP);
        time_DP += Timer_DP(A, B, DP);

        cout << test_case << endl;
    }
        cout << "el promedio en ns de BF es : " << time_BF.count() / 10  << endl;
        cout << "el promedio en ns de DP es : " << time_DP.count() / 10 << endl;
        cout << endl;
}

int main() {

    
    test("Test/dataset_1.txt");
    test("Test/dataset_2.txt");
    test("Test/dataset_3.txt");
    test("Test/dataset_4.txt");
    test("Test/dataset_5.txt");
    
    return 1;
}

// Casos de prueba

// Dataset 1: S1 vacío y S2 de largo variable.
// Dataset 2: S2 vacío y S1 de largo variable.
// Dataset 3: S1 y S2 con caracteres repetidos, mismo tamaño 
// Dataset 4: S1 es una transposición por pares de S2.
// Dataset 5: Crecimiento incremental de S1 con S2 constante




