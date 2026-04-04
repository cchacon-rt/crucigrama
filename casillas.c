#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VACIO   '#'
#define ESPACIO '.'

typedef struct {
    char valor;
    int usoContador;
} T_casilla;

T_casilla *tablero;
int numLineas, numColumnas;

char car;
char palabra[50];

void inicializarTablero() {
    for (int f = 0; f < numLineas; f++) {
        for (int c = 0; c < numColumnas; c++) {
            tablero[f * numColumnas + c].valor = ESPACIO;
            tablero[f * numColumnas + c].usoContador = 0;
        }
    }
}

void imprimirTablero() {
    for (int f = 0; f < numLineas; f++) {
        for (int c = 0; c < numColumnas; c++) {
            printf(" %c", tablero[f * numColumnas + c].valor);
        }
        printf("\n");
    }
}

void adquirirPalabra(FILE *aStream) {
    int i = 0;
    while ((car==' ')||(car=='\t')||(car=='\n')||(car=='\r')||(isdigit(car))) {
        car = fgetc(aStream);
        if (car == EOF) {
            palabra[0] = '\0';
            return;
        }
    }
    while ((car!=EOF) && (car!=' ') && (car!='\t') && (car!='\n') && (car!='\r') && !isdigit(car)) {
        palabra[i++] = car;
        car = fgetc(aStream);
    }
    palabra[i] = '\0';
}

int leerNumero(FILE *aStream) {
    int valor = 0;
    while ((car==' ')||(car=='\t')||(car=='\n')||(car=='\r')) {
        car = fgetc(aStream);
        if (car == EOF) return -1; // bandera de fin
    }
    if (!isdigit(car)) return -1;
    while (isdigit(car)) {
        valor = valor * 10 + (car - '0');
        car = fgetc(aStream);
    }
    return valor;
}

int main() {
    FILE *aStream = fopen("crucigrama.datos", "r");
    if (aStream == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");
        exit(1);
    }

    // Leer LINEAS
    while ((car = fgetc(aStream)) != EOF && !isdigit(car));
    numLineas = 0;
    while (isdigit(car)) {
        numLineas = numLineas * 10 + (car - '0');
        car = fgetc(aStream);
    }

    // Leer COLUMNAS
    while ((car = fgetc(aStream)) != EOF && !isdigit(car));
    numColumnas = 0;
    while (isdigit(car)) {
        numColumnas = numColumnas * 10 + (car - '0');
        car = fgetc(aStream);
    }

    tablero = (T_casilla *) malloc(numLineas * numColumnas * sizeof(T_casilla));
    if (tablero == NULL) {
        perror("Error al reservar memoria");
        exit(1);
    }

    inicializarTablero();

    // leer coordenadas hasta PALABRAS
    int leyendoPalabras = 0;
    while (car != EOF && leyendoPalabras == 0) {
        adquirirPalabra(aStream);
        if (strcmp(palabra, "PALABRAS") == 0) {
            leyendoPalabras = 1;
        } else {
            int fila = leerNumero(aStream);
            while (fila != -1) {
                int col = leerNumero(aStream);
                if (col != -1 && fila < numLineas && col < numColumnas) {
                    tablero[fila * numColumnas + col].valor = VACIO;
                }
                fila = leerNumero(aStream);
            }
        }
    }

    // imprimir tablero 
    printf("╔══════════════════════════════════════╗\n");
    printf("║          C R U C I G R A M A         ║\n");
    printf("╚══════════════════════════════════════╝\n");
    imprimirTablero();

    // leer e imprimir palabras
    printf("╔═════════════════════╗\n");
    printf("║   P A L A B R A S   ║\n");
    printf("╚═════════════════════╝\n");
    while (car != EOF) {
        adquirirPalabra(aStream);
        if (palabra[0] != '\0') {
            printf("%s\n", palabra);
        }
    }

    fclose(aStream);
    return 0;
}
