#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

#define FILAS 12
#define COLUMNAS 12

char lineas[20];
char columnas[15];

char car;
char palabra[50];

#define vacio '#'
#define espacio '.'


typedef struct
{
    char valor;
    int usoContador;
} T_casilla;



//T_casilla tablero[FILAS][COLUMNAS];
/*/////////////////////////////////////////////////////////////*/
typedef enum { TRUE = 1, FALSE = 0 } T_bool;  //da valor de T o F segun un 1 o 0


typedef enum{
    HORIZONTAL = 1,
    VERTICAL = 2
}   T_sentido;

typedef struct{
    T_sentido sentido;
    int x;
    int y;
    int len; //longitud
    T_bool ocupado;
} T_espacio;




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
        else {
            exit(2);
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


    T_espacio espacio;

    espacio.sentido=VERTICAL;


  if ((tablero = (T_casilla **) malloc (numLineas * sizeof (T_casilla *))) == NULL) {
      perror ("Malloc tablero err!\n");
      exit (1);
   }
   for (i = 0; i < numLineas; i++)
      if ((tablero[i] = (T_casilla *) malloc (numColumnas * sizeof (T_casilla))) == NULL) {
         perror ("Malloc tablero err!\n");
         exit (2);
      }


//posicion de palabras en el tablero
//esto esta siendo manual, queremos que adquiera x,y de forma automatica
//tablero[0][4].valor = vacio;


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
