#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define FILAS 12
#define COLUMNAS 12

char car;
char palabra[50];

#define vacio '#'
#define espacio ' '

//char tablero[FILAS][COLUMNAS];  //matriz gllobal bidimensional
typedef struct
{
    char valor;
    int usoContador;
} T_casilla;

T_casilla tablero[FILAS][COLUMNAS];
/*/////////////////////////////////////////////////////////////*/

void adquirirPalabraSiguiente(FILE *aStream)
{
    int i;

    while (((car==' ')||(car=='\t')||(car=='\n')||(car=='\r')) && (car!=EOF)) car = fgetc(aStream);

    i = 0;

    while (((car!=' ')&&(car!='\t')&&(car!='\n')&&(car!='\r')) && (car!=EOF))
    {
        palabra[i] = car;
        i++;
        car = fgetc(aStream);
    }

    palabra[i] = '\0';
}
/*////////////////////////////////////////////////////////////*/

//esta funcion inicia la lectura del primer car del input y hace un buclesito
void adquirirPrimeraPalabra()
{
    FILE *aStream;

    if ((aStream = fopen("crucigrama.datos","r"))==NULL)
    {
        fprintf(stderr,"Error al abrir el archivo\n");
        exit(2);
    }

    car = fgetc(aStream);
    adquirirPalabraSiguiente (aStream);  //this calls another function

    fclose(aStream); 
}

/*///////////////////////////////////////////////////////////*/
void funcionTablero(){
    int f,  //filas
        c;  //columnas

    for(f=0; f<FILAS; f++){
        for(c=0; c<COLUMNAS; c++){
            tablero[f][c].valor = espacio;
        }

    }


//posicion de palabras en el tablero
//esto esta siendo manual, queremos que adquiera x,y de forma automatica
tablero[0][4].valor = vacio;

tablero[1][1].valor = vacio;
tablero[1][6].valor = vacio;
tablero[1][8].valor = vacio;
tablero[1][10].valor = vacio;

tablero[2][4].valor = vacio;

tablero[3][1].valor = vacio;
tablero[3][3].valor = vacio;
tablero[3][6].valor = vacio;
tablero[3][8].valor = vacio;
tablero[3][10].valor = vacio;

tablero[4][0].valor = vacio;
tablero[4][5].valor = vacio;

tablero[5][6].valor = vacio;
tablero[5][8].valor = vacio;
tablero[5][10].valor = vacio;
tablero[5][11].valor = vacio;

tablero[6][0].valor = vacio;
tablero[6][2].valor = vacio;
tablero[6][4].valor = vacio;
tablero[6][9].valor = vacio;
tablero[6][11].valor = vacio;

tablero[7][6].valor = vacio;
tablero[7][8].valor = vacio;
tablero[7][9].valor = vacio;
tablero[7][11].valor = vacio;

tablero[8][0].valor = vacio;
tablero[8][2].valor = vacio;
tablero[8][4].valor = vacio;

tablero[9][7].valor = vacio;
tablero[9][9].valor = vacio;
tablero[9][11].valor = vacio;

tablero[10][0].valor = vacio;
tablero[10][2].valor = vacio;
tablero[10][4].valor = vacio;
tablero[10][6].valor = vacio;

tablero[11][0].valor = vacio;
tablero[11][1].valor = vacio;
tablero[11][9].valor = vacio;
tablero[11][11].valor = vacio;
}

/*////////////////////////////////////////////////////////////*/
void imprimirTablero()
{
    int f,  //filas
        c;  //columnas

    for (f=0; f < FILAS; f++)
    {
        for ( c = 0; c < COLUMNAS; c++)
        {
            printf("  %c", tablero[f][c]);
        }
        printf("\n");
    }
    
}


/*///////////////////////////////////////////////////////////*/

int main()
{
    printf("╔═════════════════════════════════════════════╗\n");
    printf("║            C R U C I G R A M A              ║\n");
    printf("╚═════════════════════════════════════════════╝\n");

    adquirirPrimeraPalabra();

    funcionTablero();

    printf("\nPrimera palabra leida: %s\n", palabra);

    imprimirTablero();

    return 0;
}
