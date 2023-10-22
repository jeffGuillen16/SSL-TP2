
/**
 * Ejemplo del autómata finito determinístico que
 * reconoce el lenguaje de las expresiones regulares (suma del lenguaje de los enternosNumericos y de las operaciones*
 */
#include <stdio.h>
#include <string.h>
// #include "reconocedor.h"
int T(int q, int x);
int conseguirIndice(int x);
void vaciarString(char str[]);
void conseguirToken(char token[20], int estado_actual);
#define LENGTH 50

int main(int argc, char **argv)
{
    int x;
    int estado_actual = 0;
    char string[LENGTH]; // Tamaño máximo de la cadena (ajusta según tus necesidades)
    memset(string, 0, LENGTH);
    const char *nombreArchivo = "archivo.txt";
    FILE *archivo = fopen(nombreArchivo, "r");
    char token[20];
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
    printf("+-------------+----------------------+\n");
    printf("|En el codigo | Token                |\n");
    printf("+-------------+----------------------+\n");

    int i = 0;
    x = fgetc(archivo);

    while (x != EOF)
    {
        if (x == '\n')
        {
            conseguirToken(token, estado_actual + 1);
            printf("| %-11s | %-20.*s |\n", string, 20, token);
            memset(string, 0, LENGTH);
            estado_actual = 0;
            i = 0;
            printf("+-------------+----------------------+\n");
            printf("\n");
            printf("+-------------+----------------------+\n");
            printf("|En el codigo | Token                |\n");
            printf("+-------------+----------------------+\n");
        }
        else
        {
            estado_actual = T(estado_actual, x);
            if (estado_actual == 4 || estado_actual == 2)
            {
                conseguirToken(token, estado_actual);
                printf("| %-11s | %-20.*s |\n", string, 20, token);
                // printf("ACEPTADA: %s\n", string);
                ungetc(x, archivo);
                memset(string, 0, LENGTH);
                estado_actual = 0;
                i = 0;
            }
            else if ( estado_actual == 3)
            {
                conseguirToken(token, estado_actual + 1);
                printf("| %-11s | %-20.*s |\n", string, 20, token);
                printf("+-------------+----------------------+\n");
            }
            if (estado_actual == -1)
            {
                printf("RECHAZADA\n");
                printf("Caracter no válido: %c\n", (char)x); // Imprime el carácter no válido
                estado_actual = 0;
                memset(string, 0, LENGTH);
                i = 0;
            }
            else
            {
                char caracter = (char)x;
                string[i] = caracter;
                // printf("%c\n", caracter);
                // for ( int j=0; j<6; j++) {
                //  printf("%c\n", string[j]);
                //}
                // printf("Cadena: %s\n", string);
                i++;
            }
        }
        x = fgetc(archivo);
    }

    fclose(archivo); // Cierra el archivo
    /*if (estado_actual == 1 || estado_actual == 3)
    {
        conseguirToken(token, estado_actual + 1);
        printf("| %-11s | %-20.*s |\n", string, 20, token);
        printf("+-------------+----------------------+\n");
    }
    else
    {
        printf("RECHAZADA: %s\n", string);
    }*/
    return 0;
}
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
    else
    {
        return -1; // Caracteres no válidos
    }
}

void conseguirToken(char token[20], int estado_actual)
{
    if (estado_actual == 2)
    {
        strcpy(token, "Constante numerica");
    }
    else
    {
        strcpy(token, "Operador");
    }
}

void esEstadoRechazo(int *fila, int x, int *indice)
{
    *fila = 0;
    if (*fila == 0)
    {
        *fila = 2;

        // printf("Fila: %d\n", *fila);
        if ((*fila == 2 || *fila == 4) && conseguirIndice(x) == -1)
        {
            // printf("indice: %d\n", *indice);
            *indice = 0;
        }
    }
    if (*fila == 0)
    {
        *fila = 4;
        if ((*fila == 2 || *fila == 4) && conseguirIndice(x) == -1)
        {
            *indice = 1;
        }
    }
}

void esFilasColumnas(int tabla[5][2], int *fila, int colum)
{

    int elemento = tabla[*fila][colum]; // Acceder al elemento en la fila y columna indicadas

    // Puedes hacer algo con 'elemento', por ejemplo, imprimirlo
    printf("Elemento en fila %d y columna %d: %d\n", *fila, colum, elemento);
}

int T(int q, int x)
{ // Estados de rechazo

    int indice;
    int *puntero;
    int *fila = &q;

    static int tabla[5][2] = {
        {1, 3},
        {1, 2},
        {-1, -1},
        {4, 4},
        {-1, -1}};

    if (conseguirIndice(x) == -1)
    {
        // Ahora fila es un puntero que apunta a q
        int x = conseguirIndice(x);
        puntero = &x;
        esEstadoRechazo(fila, x, puntero);
        // Imprime el valor de fila al que apunta
        esFilasColumnas(tabla, fila, *puntero);
        return tabla[*fila][*puntero];
    }
    else
    {
        indice = conseguirIndice(x);
        return tabla[*fila][indice];
    }
}