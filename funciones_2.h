#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int **leerEntrada(int *n){
    FILE *archivoEntrada = fopen("Entrada2.in", "r");
    int primerNum = 0;
    fscanf(archivoEntrada, "%d", &primerNum);

    int **mapa = malloc(sizeof(int *)*primerNum);
    for (int i = 0; i < primerNum; i++)
    {
        mapa[i] = malloc(sizeof(int)*primerNum);
    }
    
    for(int i = 0; i < primerNum; i++)
    {
        for (int j = 0; j < primerNum; j++)
        {
            fscanf(archivoEntrada, "%d", &mapa[i][j]);
        }
        
    }
    fclose(archivoEntrada);

    *n = primerNum; // Para poder ocupar este numero fuera de la funcion
    return mapa;
}

void CalcularTiempo(time_t tiempo, struct tm *infor, char buffer[80]){

    time( &tiempo );
    infor = localtime( &tiempo );
    strftime(buffer,80,"%x - %X %p", infor);
}

void scrClean()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
//===================================================================================================================
//Funciones para el recorrido manual

//Funcion que imprime la ciudad a partir de cada cambio. Tiene como entrada la matriz.
void ImprimirCiudad(int ciudad[10][10], int tamanioCiudad, int x, int y){

	//recorrido filas
	for (int i = 0; i < tamanioCiudad; i++){

		//recorrido columnas
		for (int j = 0; j < tamanioCiudad; j++){
			//seleccion del elemento que busca el usuario
			if (x==i && y==j){
					printf("|%d|", ciudad[i][j]); //ubica al jugador
				}
			else printf(" %d ", ciudad[i][j]); //imprime la ciudad
		}
		printf("\n");
	}
}
/*Funcion que toma el numero mas cercano a la esquina derecha de la ciudad*/
int PosicionNororiente(int ciudad[10][10]){ //busca la posicion nororiente para partir a jugar
	int PosFinal = 0;
	int i = 10; //largo de la ciudad 
	while(i>0){
		if(ciudad[0][i] != 0){
			if (PosFinal == 0)
			{
				PosFinal = i;
			}
		}
		i=i-1;
	}
	return PosFinal;//retorna la posicion donde se encuentre el num mas cercano de la derecha
}

/*La funcion atrapado permite verificar si en cada uno de los 4 casos-> Arr, Aba, Izq, Der, existe un 0,
 nos retorna 1 si no esta atrapado y 0 si lo esta*/
int atrapado(int ciudad[10][10],int x,int y, int tamanioCiudad){
	int salida=1;
	if(x==0){
		if(y==0){
			if(ciudad[x+1][y]==0 && ciudad[x][y+1]==0){
				salida=0;
				return salida;
				}
			}
		else{
			if(ciudad[x+1][y]==0 && ciudad[x][y+1]==0 && ciudad[x][y-1]==0){
				salida=0;
				return salida;

			}
		}
	}

	if(x==(tamanioCiudad-1)){
		if(y==(tamanioCiudad-1)){
			if(ciudad[x-1][y]==0 && ciudad[x][y-1]==0){
				salida=0;
				return salida;
				}
		}
		else{
			if(ciudad[x-1][y]==0 && ciudad[x][y-1]==0 && ciudad[x][y+1]==0){
				salida=0;
				return salida;
			}
		}
	}

	if(y==0){
		if (x==0){
			if(ciudad[x+1][y]==0 && ciudad[x][y+1]==0){
				salida=0;
				return salida;
				}
			}
		else{
			if(ciudad[x+1][y]==0 && ciudad[x][y+1]==0 && ciudad[x][y-1]==0){
				salida=0;
				return salida;
			}
		}
	}

	if(y==(tamanioCiudad-1)){
		if(x==(tamanioCiudad-1)){
			if(ciudad[x-1][y]==0 && ciudad[x][y-1]==0){
				salida=0;
				return salida;
				}
		}
		else{
			if(ciudad[x-1][y]==0 && ciudad[x][y-1]==0 && ciudad[x][y+1]==0){
				salida=0;
				return salida;
			}
		}
	}

	if(ciudad[x+1][y]==0 && ciudad[x-1][y]==0 && ciudad[x][y+1]==0 && ciudad[x][y-1]==0)
	{
		salida=0;
		return salida;
	}
	else{
		return salida;
	} 

}

/*la funcion verificaMatriz nos permite saber si es que la matriz esta en su estado final o no, 
si aun esta incompleta, retorna 0, si la matriz ya esta lista, retorna 1*/
int verificaMatriz(int matriz[10][10],int tamanMatriz){
	int matrizLista=0;
	for (int i = 0; i < tamanMatriz; ++i){

		for (int j = 0; j < tamanMatriz; ++j){
			if (matriz[i][j]!=0){
				matrizLista=1;
			}
		}
	}
	return matrizLista;
}


/*La funcion salidaOut nos permite guardar un string dentro de un archivo .out en este caso, tiene como entrada
el puntero del string.*/
void salidaOut(char *guardar){
	FILE * salida = fopen("salida2.out","w");
	fputs(guardar,salida);
	fclose(salida);
	printf("Guardado con exito!\n");
}
/*La funcion recorridoMan es la funcion principal, para poder trabajar:*/
void recorridoMan(int ciudad[10][10], int tamanMatriz){
	//creamos las posiciones iniciales para el eje x e y.
	int y = PosicionNororiente(ciudad);
	int x=0;
	//Primera posicion, hace referencia a si es la primera jugada 
	int primeraPosicion=0;
	//Se crea un char array en entrada
	char entrada[100];
	//verifica la salida.
	int sinSalida;
	//verifica si es correcta la matriz.
	int verificacionMatriz;
	//creamos 2 char que nos permitan guardar las direcciones
	//N S E O
	char *direccion;
	char *guardar;
	//Se inicializa el buffer para poder obtener los datos de posicion.
	guardar=(char*)malloc(4);
	int i=0;
	int exit=0;

	while(exit!=1){  //ciclo while para recorrer la ciudad

		ImprimirCiudad(ciudad,tamanMatriz,x,y);
		printf("\nBienvenido al recorrido manual, muevete con las teclas:\n");
		printf("W -> arriba\nA -> izquierda\nS -> abajo\nD -> derecha\nselecciona una tecla:");
		scanf(" %s",entrada);
		while (strcmp(entrada,"w")!=0 &&strcmp(entrada,"d")!=0 &&strcmp(entrada,"s")!=0 &&strcmp(entrada,"a")!=0 ) //ciclo para verificar si es correcta la entrada
		{
			printf("\n POR FAVOR INGRESE UNA ENTRADA VALIDA\n");
			printf("selecciona una tecla y luego enter:");
			scanf(" %s",entrada);
		}

		if (primeraPosicion==0)
		{
			ciudad[x][y]=ciudad[x][y]-1;
			primeraPosicion=primeraPosicion+1;
		}
		
		//Luego, dependiendo de la entrada del user, se selecciona la posicion, se verifica si es valida
		//de serlo, se guarda en el *guardar , se elimina la jugada y pasa a la posicion siguiente volviendo a preguntar por la seleccion. 
		if (strcmp(entrada,"w")==0){	
			x=x-1;
			y=y;
			if (ciudad[x][y]==0){
				printf("\nHAY UN 0!\n\n");
				x=x+1;
				y=y;
			}

			
			else{//Las 4 condiciones son iguales solo cambia si el usuario ingresa los parametros o indicaciones N S E O 
				if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
					ciudad[x][y]=ciudad[x][y]-1;
					direccion="N";
					strcat(guardar,direccion);
					guardar=(char *)realloc(guardar,8+i);
					i=i+1;
					verificacionMatriz=verificaMatriz(ciudad,10);
					if (verificacionMatriz==0)
					{
						printf("Logrado\n");
						salidaOut(guardar);
						free(guardar);
						exit=1;
					}
					else{
						sinSalida=atrapado(ciudad,x,y,10);
						if (sinSalida==0)
						{
							exit=1;
						}
					}
					
					}
				else{	
					printf("\n\nIntentalo nuevamente...\n\n");
					x=x+1;
					y=y;
				}

		}
	}

		if (strcmp(entrada,"a")==0){	
			x=x;
			y=y-1;
			if (ciudad[x][y]==0){
				printf("\nHAY UN 0!\n\n");
				x=x;
				y=y+1;
			}
			else{
				if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
					ciudad[x][y]=ciudad[x][y]-1;
					direccion="E";
					strcat(guardar,direccion);
					guardar=(char *)realloc(guardar,8+i);
					i=i+1;
					verificacionMatriz=verificaMatriz(ciudad,10);
					if (verificacionMatriz==0)
					{
						printf("Logrado\n");
						salidaOut(guardar);
						free(guardar);
						exit=1;
					}
					else{
						sinSalida=atrapado(ciudad,x,y,10);
						if (sinSalida==0)
						{
							exit=1;
						}
					}	}
				else{
					
					printf("\n\nIntentalo nuevamente...\n\n");
					x=x;
					y=y+1;
				}
				
			}
		}
		if (strcmp(entrada,"s")==0){	
			x=x+1;
			y=y;
			if (ciudad[x][y]==0){
				printf("\nHAY UN 0!\n\n");
				x=x-1;
				y=y;
			}
			else{
				if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
					ciudad[x][y]=ciudad[x][y]-1;
					direccion="S";
					strcat(guardar,direccion);
					guardar=(char *)realloc(guardar,8+i);
					i=i+1;
					verificacionMatriz=verificaMatriz(ciudad,10);
					if (verificacionMatriz==0)
					{
						printf("Logrado\n");
						salidaOut(guardar);
						free(guardar);
						exit=1;
					}
					else{
						sinSalida=atrapado(ciudad,x,y,10);
						if (sinSalida==0){
							exit=1;
						}}
					}
				else{
					printf("\n\nIntentalo nuevamente...\n\n");
					x=x-1;
					y=y;
				}
				
			}}
		if (strcmp(entrada,"d")==0)
		{	
			x=x;
			y=y+1;
			if (ciudad[x][y]==0){
				printf("\nLogrado\n\n");
				x=x;
				y=y-1;
			}
			else{
				if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
					ciudad[x][y]=ciudad[x][y]-1;
					direccion="O";
					strcat(guardar,direccion);
					guardar=(char *)realloc(guardar,8+i);
					i=i+1;
					verificacionMatriz=verificaMatriz(ciudad,10);
					if (verificacionMatriz==0)
					{
						printf("Logrado\n");
						salidaOut(guardar);
						free(guardar);
						exit=1;
					}
					else{
						sinSalida=atrapado(ciudad,x,y,10);
						if (sinSalida==0)
						{
							exit=1;
						}}
				
			}
				else{
					
					printf("\n\nIntentalo nuevamente...\n\n");
					x=x;
					y=y-1;
				}
			}
		}
	}
	if (sinSalida==0)
	{
		printf("\nPerdiste, mas suerte para la proxima :)\n");
	}

}