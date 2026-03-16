#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define FILAS 12
#define COLUMNAS 12

char car;
char palabra[50];

#define vacio '#'
#define espacio ' '

char tablero[FILAS][COLUMNAS];  //matriz gllobal bidimensional
/*typedef struct casillas
{
    char valor;
    int usoContador;
} T_casilla;

T_casilla tablero [FILAS][COLUMNAS];
*/
/*/////////////////////////////////////////////////////////////*/

void adquirirPalabraSiguiente()  //la funcion que lee palabra x palabra
{
    int i;
	//mientras que el car no sea igual a espacio, o a tabulador, o a new line, o a carriage return, o sea end of file... keep reading the next char
    while (((car==' ')||(car=='\t')||(car=='\n')||(car=='\r')) && (car!=EOF))
        car=getchar();
//All of this means 'keep reading characters while they are whitespace and not-EOF'
    i=0;  //initialize the index to start storing characters from the beginning of 'palabra'

    while (((car!=' ')&&(car!='\t')&&(car!='\n')&&(car!='\r')) && (car!=EOF))  //these are the characters we told it to stop when they appear
    {
        palabra[i]=car; //guarda el car dentro del array palabra
        i++;  //i=i+1
        car=getchar(); //reads ONE char from std input, returns it and store it, read the next char aaand repeat
    }
    palabra[i]=0x00; //this is an hexadecimal zero (same as '\0') w/o this it wouldnt be a valid C string
}

/*////////////////////////////////////////////////////////////*/

//esta funcion inicia la lectura del primer car del input y hace un buclesito
void adquirirPrimeraPalabra()
{
    FILE *aStream;

    car = fgetc(aStream);
    if ((aStream = fopen("crucigrama.datos","r"))==NULL)
    {
        fprintf(stderr,"Un texto\n");
        exit(2);
    }
    fclose(aStream); 


    adquirirPalabraSiguiente();  //this calls another function
}

/*///////////////////////////////////////////////////////////*/
void funcionTablero()
{
    int f,  //filas
        c;  //columnas

    for(f=0; f<FILAS; f++){
        for(c=0; c<COLUMNAS; c++){
            tablero[f][c] = espacio;
        }

    }
//posicion de palabras en el tablero
tablero[0][4] = vacio;

tablero[1][1] = vacio;
tablero[1][6] = vacio;
tablero[1][8] = vacio;
tablero[1][10] = vacio;

tablero[2][4] = vacio;

tablero[3][1] = vacio;
tablero[3][3] = vacio;
tablero[3][6] = vacio;
tablero[3][8] = vacio;
tablero[3][10] = vacio;

tablero[4][0] = vacio;
tablero[4][5] = vacio;

tablero[5][6] = vacio;
tablero[5][8] = vacio;
tablero[5][10] = vacio;
tablero[5][11] = vacio;

tablero[6][0] = vacio;
tablero[6][2] = vacio;
tablero[6][4] = vacio;
tablero[6][9] = vacio;
tablero[6][11] = vacio;

tablero[7][6] = vacio;
tablero[7][8] = vacio;
tablero[7][9] = vacio;
tablero[7][11] = vacio;

tablero[8][0] = vacio;
tablero[8][2] = vacio;
tablero[8][4] = vacio;

tablero[9][7] = vacio;
tablero[9][9] = vacio;
tablero[9][11] = vacio;

tablero[10][0] = vacio;
tablero[10][2] = vacio;
tablero[10][4] = vacio;
tablero[10][6] = vacio;

tablero[11][0] = vacio;
tablero[11][1] = vacio;
tablero[11][9] = vacio;
tablero[11][11] = vacio;

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