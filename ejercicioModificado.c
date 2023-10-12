/**
 * Ejemplo del autómata finito determinístico que 
 * reconoce el lenguaje de las expresiones regulares (suma del lenguaje de los enternosNumericos y de las operaciones*
*/
#include <stdio.h>

int T(int q, int x);
int conseguirIndice(int x);
void vaciarString(char str[]);

int main(int argc, char **argv) {
    int x;
    int estado_actual = 0;
    char string[] ="";
    
     for (int i = 0; (x=getchar()) > 0; i++) {
        
        if (x == '\n' || x == '\r') {
            if (estado_actual == 3 || estado_actual == 2) {
                printf("ACEPTADA\n");
                printf(string);
            } else {
                printf("RECHAZADA\n");
                printf(string);
            }
            ungetc(x);
            vaciarString(string);
            estado_actual = 0;
            continue;
        } else {
            string[i]=x;
        }
        
        printf("%c", x);
        estado_actual = T(estado_actual, x);

        if (estado_actual == -1) {
            printf("RECHAZADA\n");
            printf(string);
            vaciarString(string);
            estado_actual = 0;
        }
    }

    return 0;
}

void vaciarString(char str[]) {
    str[0] = '\0';  // Asignamos el valor nulo al primer elemento del arreglo
}

int conseguirIndice( int x){
    if (x>=48 && x<=57){
        return 0;         //Digitos del 0 al 9
    }
    if (x>=40 && x<=43 || x == 45 || x == 47){
        return 1;     // Caracteres operadores [(, ), +, *, - , /]
    }
    return -1; // Caracteres no validos
}

int T(int q, int x) {

    int indice = conseguirIndice(x);    

    static int tabla[5][3] = {
        { 1,  3, -1},
        { 1,  2, -1},
        {-1, -1, -1},
        { 4, -1, -1},
        {-1, -1, -1}
    };
    return tabla[q][indice];
}