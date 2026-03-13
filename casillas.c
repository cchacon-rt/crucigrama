#include <stdio.h>

#define FILAS 11
#define COLUMNAS 11

#define vacio '#'
#define espacio ' '

char tablero[FILAS][COLUMNAS];  //matriz gllobal bidimensional

/*/////////////////////////////////////////////////////////////*/
void funcionTablero()
{
    int f,  //filas
        c;  //columnas

    for(f=0; f<FILAS; f++){
        for(c=0; c<COLUMNAS; c++){
            tablero[f][c] = vacio;
        }

    }
//posicion de palabras en el tablero
tablero[0][4] = espacio;

/*
0 4 
1 1  1 6  1 8  1 10
2 4
3 1  3 3  3 6  3 8  3 10
4 0  4 5
5 6  5 8  5 10  5 11
6 0  6 2  6 4  6 9  6 11
7 6  7 8  7 9  7 11
8 0  8 2  8 4
9 7  9 9  9 11
10 0  10 2  10 4  10 6
11 0  11 1  11 9  11 11*/


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
            printf(" %c", tablero[f][c]);
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

    funcionTablero();

    imprimirTablero();

    return 0;
}