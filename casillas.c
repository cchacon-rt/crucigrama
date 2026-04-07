#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    ESPACIO = '.',   // casilla libre
    VACIO   = '#'    // casilla negra
} TipoCasilla;

typedef struct {    //estructura de cada casilla en el tablero
    TipoCasilla valor;
    int usoContador;
} T_casilla;

T_casilla *tablero;     //var global (reservada con malloc)
int numLineas, numColumnas;

char car;
char palabra[50];

//recorre todas las casillas y las inicia como ESPACIO = '.'
void inicializarTablero() {
    for (int f = 0; f < numLineas; f++) {
        for (int c = 0; c < numColumnas; c++) {
            tablero[f * numColumnas + c].valor = ESPACIO;
            tablero[f * numColumnas + c].usoContador = 0;
        }
    }
}

//recorre el tablero y muestra cada casilla en pantalla
void imprimirTablero() {
    for (int f = 0; f < numLineas; f++) {
        for (int c = 0; c < numColumnas; c++) {
            printf(" %c", tablero[f * numColumnas + c].valor);
        }
        printf("\n");
    }
}

//obtenemos la info de nuestro crucigrama.datos
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

//avanzamos hasta leer un num de nuestro file
int leerNumero(FILE *aStream) {
    int valor = 0;
    while ((car==' ')||(car=='\t')||(car=='\n')||(car=='\r')) {
        car = fgetc(aStream);
        if (car == EOF) return -1; // bandera de fin
    }
    if (!isdigit(car)) return -1;   // si no es un digito tambien pone bandera de fin
    while (isdigit(car)) {      // y si hay digitos, se contruye el numero 
        valor = valor * 10 + (car - '0');
        car = fgetc(aStream);
    }
    return valor;
}

int main() {
    FILE *aStream = fopen("crucigrama.datos", "r");     //abrimos el archivo en modo lectura
    if (aStream == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");     //si falla muestra error y termina
        exit(1);
    }
//leemos las dimensiones
    //primero LINEAS
    while ((car = fgetc(aStream)) != EOF && !isdigit(car));     //avanza hasta encontrar un digito
    numLineas = 0;
    while (isdigit(car)) {
        numLineas = numLineas * 10 + (car - '0');
        car = fgetc(aStream);
    }

    //despues COLUMNAS
    while ((car = fgetc(aStream)) != EOF && !isdigit(car));     //avanza hasta encontrar un digito
    numColumnas = 0;
    while (isdigit(car)) {
        numColumnas = numColumnas * 10 + (car - '0');
        car = fgetc(aStream);
    }

    //reserva memoria para todas las casillas
    tablero = (T_casilla *) malloc(numLineas * numColumnas * sizeof(T_casilla));
    if (tablero == NULL) {
        perror("Error al reservar memoria");    //si falla, imprime el error
        exit(1);
    }

    inicializarTablero();       //llama a la funcion todas en ESPACIO

    int leyendoPalabras = 0;
    while (car != EOF && leyendoPalabras == 0) {
        adquirirPalabra(aStream);
        if (strcmp(palabra, "PALABRAS") == 0) {     //si encuentra la palabra PALABRAS
            leyendoPalabras = 1;        //cambia a modo lectura de palabras
        } else {
            int fila = leerNumero(aStream);         //de lo contrario, interpreta los nums como coordenadas
            while (fila != -1) {
                int col = leerNumero(aStream);
                if (col != -1 && fila < numLineas && col < numColumnas) {
                    tablero[fila * numColumnas + col].valor = VACIO;        //y les cambia su valor de ESPACIO a VACIO
                }
                fila = leerNumero(aStream);
            }
        }
    }

    //decoracion
    printf("╔════════════════════════════════╗\n");
    printf("║       C R U C I G R A M A      ║\n");
    printf("╚════════════════════════════════╝\n");
    imprimirTablero();

    printf("╔═════════════════════╗\n");
    printf("║   P A L A B R A S   ║\n");
    printf("╚═════════════════════╝\n");
    while (car != EOF) {            
        adquirirPalabra(aStream);
        if (palabra[0] != '\0') {
            printf("%s\n", palabra);        //imprime el string palabra
        }
    }

    fclose(aStream);        //cierra el archivo
    return 0;       //finaliza programa
}
