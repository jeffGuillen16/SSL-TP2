/**
 * Ejemplo del autómata finito determinístico que
 * reconoce el lenguaje de las expresiones regulares (suma del lenguaje de los enternosNumericos y de las operaciones*
 */
#include <stdio.h>

int T(int q, int x);
int conseguirIndice(int x);
void vaciarString(char str[]);

int main(int argc, char **argv)
{
    int x;
    int estado_actual = 0;
    char string[100]; // Tamaño máximo de la cadena (ajusta según tus necesidades)
    vaciarString(string);
    const char *nombreArchivo = "archivo.txt";
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    int i = 0;
    x = fgetc(archivo);

    while (x != EOF)
    {
         char caracter = (char)x;
         printf("%c\n", caracter);
        if (x == '\n' || x == '\r')
        {
            if (estado_actual == 1 || estado_actual == 3)
            {
                printf("ACEPTADA\n");
                printf("%s", string);
            }
            else
            {
                printf("RECHAZADA\n");
                printf("%s", string);
            }
            vaciarString(string);
            estado_actual = 0;
            i = 0;
            continue;
        }
        else
        {
            estado_actual = T(estado_actual, x);
            if (estado_actual == 4 || estado_actual == 2)
            {
                printf("ACEPTADA: %s\n", string);
                ungetc(x, archivo);
                vaciarString(string);
                estado_actual = 0;
                i = 0;
            }
            else if (estado_actual == -1)
            {
                printf("RECHAZADA\n");
                printf("Caracter no válido: %c\n", (char)x); // Imprime el carácter no válido
                estado_actual = 0;
                i = 0;
            }
            else
            {
                char caracter = (char)x;
                // printf("%c\n", caracter);
                string[i] = caracter;
                /*for ( int j=0; j<6; j++) {
                  printf("%c\n", string[j]);
                }*/
                // printf("Cadena: %s\n", string);
                i++;
            }
            x = fgetc(archivo);
        }
    }
    fclose(archivo); // Cierra el archivo
    if (estado_actual == 1 || estado_actual == 3)
    {
        printf("ACEPTADA: %s\n", string);
    }
    else
    {
        printf("RECHAZADO: %s\n", string);
    }
    return 0;
}

void vaciarString(char str[])
{

    for (int i = 0; i < 100; i++)
    {
        str[i] = ' '; // Asignamos el valor nulo al primer elemento del arreglo
    }
}
int conseguirIndice(int x)
{
    if (x >= 48 && x <= 57)
    {
        return 0; // Dígitos del 0 al 9
    }
    if (x >= 40 && x <= 43 || x == 45 || x == 47)
    {
        return 1; // Caracteres operadores [(, ), +, *, - , /]
    }
    return -1; // Caracteres no válidos
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
    return tabla[q][indice];
}
