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
    int fila = 1;
    int col = 1;
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
            fila++;
            col=0;
           //conseguirToken(token, estado_actual + 1);
            //printf("| %-11s | %-20.*s |\n", string, 20, token);
            memset(string, 0, LENGTH);
            estado_actual = 0;
            i = 0;
            printf("*************************************\n");
            printf("\n");
            printf("+-------------+----------------------+\n");
            printf("|En el codigo | Token                |\n");
            printf("+-------------+----------------------+\n");
            col++;
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

            else if (estado_actual == -1)
            {
                printf("RECHAZADA\n");
                printf("Caracter no válido: %c\n", (char)x); // Imprime el carácter no válido
                printf(" fila %d y columna %d\n", fila, col);
                estado_actual = 0;
                memset(string, 0, LENGTH);
                i = 0;
                col++;
            }
            else
            {
                char caracter = (char)x;
                string[i] = caracter;
                i++;
                col++;
            }
            if ( estado_actual == 3)
            {
                conseguirToken(token, estado_actual + 1);
                printf("| %-11s | %-20.*s |\n", string, 20, token);
                printf("+-------------+----------------------+\n");
            }
        }
            x = fgetc(archivo);
    }
        fclose(archivo); // Cierra el archivo
                         if (estado_actual == 1 )
                         {
                             conseguirToken(token, estado_actual + 1);
                             printf("| %-11s | %-20.*s |\n", string, 20, token);
                             printf("+-------------+----------------------+\n");
                         }
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
    int T(int q, int x)
    {
        int indice = conseguirIndice(x);

        static int tabla[5][2] = {
            {1, 3},
            {1, 2},
            {-1, -1},
            {4, 4},
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