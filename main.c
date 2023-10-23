/**
 * Ejemplo del autómata finito determinístico que
 * reconoce el lenguaje de las expresiones regulares (suma del lenguaje de los enternosNumericos y de las operaciones*
 */
#include <stdio.h>
#include <string.h>
#define LENGTH 50
#include "reconocedor.h"
int T(int q, int x);
int conseguirIndice(int x);
void vaciarString(char str[]);
void conseguirToken(char token[20], int estado_actual);
void imprimirCaracterRechazado(int x, int fila, int columna);
void inicioTabla();
void finTabla();
void imprimirToken(char string[LENGTH], char token[20]);
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
    inicioTabla();
    int i = 0;
    x = fgetc(archivo);

    while (x != EOF)
    {
        if (x == '\n')
        {   
            if (estado_actual == 1)
            {
                conseguirToken(token, estado_actual+1);
                imprimirToken(string,token);
            }
            fila++;
            col=1;
            memset(string, 0, LENGTH);
            estado_actual = 0;
            i = 0;
            finTabla();
            inicioTabla();
        }
        else
        {    
            col++; 
            estado_actual = T(estado_actual, x);
            if (estado_actual == 2)
            {
                conseguirToken(token, estado_actual);
                imprimirToken(string,token);
                ungetc(x, archivo);
                memset(string, 0, LENGTH);
                estado_actual = 0;
                i = 0;
            }
            else if (estado_actual == 3 )
            {
                conseguirToken(token, estado_actual);
                estado_actual = 0;
                char caracter = (char)x;
                string[i] = caracter;
                imprimirToken(string,token);
            }
            
            else if (estado_actual == -1)
            {
                if (strlen(string)>0)
                {
                    conseguirToken(token, 1);
                    imprimirToken(string,token);
                    memset(string, 0, LENGTH);                    
                }
                imprimirCaracterRechazado(x, fila,col);
                estado_actual = 0;
                memset(string, 0, LENGTH);
                i = 0;
            }
            else
            {
                char caracter = (char)x;
                string[i] = caracter;
                i++;
            }
        }

        x = fgetc(archivo);
    }
        fclose(archivo); // Cierra el archivo
        if (estado_actual == 1 )
        {
            conseguirToken(token, estado_actual + 1);
            imprimirToken(string,token);
            finTabla();
        }
        return 0;
    }
    void imprimirToken(char string[LENGTH], char token[20]) {
            printf("| %-11s | %-20.*s |\n", string, 20, token);
            printf("+-------------+----------------------+\n");       
    }
    void imprimirCaracterRechazado(int x, int fila, int columna){
            printf("**************************************\n");      
            fprintf(stderr, "Rechazo de: %c en la fila %d y columna %d\n", (char)x, fila, columna);
            printf("+-------------+----------------------+\n");
    }
    void inicioTabla(){
        printf("+-------------+----------------------+\n");
        printf("|En el codigo | Token                |\n");
        printf("+-------------+----------------------+\n");
    }

    void finTabla(){
        printf("**************************************\n");
        printf("\n");
    }