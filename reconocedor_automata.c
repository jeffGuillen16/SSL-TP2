#include "reconocedor.h"
#include <stdio.h>
#include <string.h>

int conseguirIndice(int x)
{
    if (x >= 48 && x <= 57)
    {
        return 0; // Dígitos del 0 al 9
    }
    else if (x >= 40 && x <= 43 || x == 45 || x == 47)
    {
        return 1; // Caracteres operadores [(, ), +, *, - , /]
    }
    else {
        return -1; // Caracteres no válidos
    }

}

void conseguirToken(char token[20], int estado_actual) {
    if (estado_actual == 2) {
        strcpy(token, "Constante numerica");
    } else {
        strcpy(token, "Operador");
    }
    
}
int T(int q, int x)
    {
        int indice = conseguirIndice(x);

        static int tabla[4][2] = {
            {1, 3},
            {1, 2},
            {-1, -1},
            {-1, -1}};

        if (indice == -1)
        {
            return -1; // Caracter no válido
        }
        else
        {
            return tabla[q][indice];
            
        }
    }