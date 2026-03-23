#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50

int main() {
    FILE *f;
    char c;
    int tablero[MAX][MAX];
    int filas = 0, columnas = 0;

    // Inicializar tablero con '.'
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            tablero[i][j] = '.';

    f = fopen("c.datos", "r");
    if (!f) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    int num = 0;
    int leyendoNumero = 0;
    int valores[1000];
    int total = 0;

    // Leer todo el archivo con fgetc
    while ((c = fgetc(f)) != EOF) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            leyendoNumero = 1;
        } else {
            if (leyendoNumero) {
                valores[total++] = num;
                num = 0;
                leyendoNumero = 0;
            }
        }
    }
    // Por si termina en número
    if (leyendoNumero) {
        valores[total++] = num;
    }

    fclose(f);

    // Primeros dos números: filas y columnas
    filas = valores[0];
    columnas = valores[1];

    // El resto son pares (x, y)
    for (int i = 2; i < total; i += 2) {
        int x = valores[i];
        int y = valores[i + 1];

        if (x < filas && y < columnas) {
            tablero[x][y] = '#';
        }
    }

    // Imprimir tablero
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }

    return 0;
}