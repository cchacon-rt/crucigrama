#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

#define FILAS 12
#define COLUMNAS 12

char car;
char palabra[50];

#define vacio '#'
#define espacio '.'

//char tablero[FILAS][COLUMNAS];  //matriz gllobal bidimensional
typedef struct
{
    char valor;
    int usoContador;
} T_casilla;

T_casilla tablero[FILAS][COLUMNAS];
/*/////////////////////////////////////////////////////////////*/
void adquirirPalabras (FILE *aStream)
{
    int i;

    while (((car==' ')||(car=='\t')||(car=='\n')||(car=='\r') || (isdigit(car))) && (car!=EOF)) car = fgetc(aStream);
        i = 0;

    while (((car!=' ')&&(car!='\t')&&(car!='\n')&&(car!='\r') && !(isdigit(car))) && (car!=EOF))
    {
        palabra[i++] = car;
        car = fgetc(aStream);
    }
    palabra[i] = '\0';
}

/*/////////////////////////////////////////////////*/

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

    while (car)
    {
        adquirirPalabras (aStream);  //this calls another function
        if (palabra[0] != '\0')
        {
            printf("%s\n", palabra);
        }
    } 
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

/*//////////////////////////////////////////////////*/
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

/*////////////////////////////////////////////////*/

int main()
{
    printf("╔═════════════════════════════════════════════╗\n");
    printf("║            C R U C I G R A M A              ║\n");
    printf("╚═════════════════════════════════════════════╝\n");


    funcionTablero();

    imprimirTablero();

    adquirirPrimeraPalabra();
    //aca verificamos que el archivo inicie con la palabra PALABRAS

    if(strcmp(palabra,"PALABRAS")!=0)
    {   
        fprintf(stderr,"Error: PALABRAS del crucigrama no encontradas\n");    //de lo contrario imprime un error
        exit(1);
    } else {
        printf("\nPALABRAS: %s\n", palabra);
    }

    return 0;
}
