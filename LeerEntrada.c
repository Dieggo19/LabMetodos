#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define p printf
#define xd printf("xd");



// Matrices de info
// Filas
int** filas;
int* lenFilas;
// Columnas
int** columnas; //  Edificios en las columnas
char** linea_columna; // Lineas de texto de las columnas
int** len_columna; // Cantidad de edificios por columna
int* cant_grupos; // Cantidad de grupos

// Ciudad
int DIM;
int ** ciudad;

// .txt
char * LeerEntrada(char * nombre_archivo){
	// Lee el archivo de entrada y lo devuelve como cadena
	printf("Leyendo archivo...\n");
    FILE * flujo = fopen(nombre_archivo, "r");
    // Contar numero de caracteres
    fseek(flujo, 0, SEEK_END);  
    int num_elementos = ftell(flujo); 
    rewind(flujo); 
    char * cadena = (char*) calloc(sizeof(char), num_elementos);
    int num_elementos_leidos = fread(cadena, sizeof(char), num_elementos, flujo);
    fclose(flujo);
    printf("El archivo se ha leido correctamente:\n\n");
    printf("%s\n\n", cadena);
    return cadena;
}

char ** extraerColumnasTXT(char * string){
    // Quitar las filas de info
	char listado[500]; strcpy(listado, string);  // Copio info
	char * listado_1 = strtok(listado, "\n"); // N
	int g = 0;
	while(g < DIM){
		listado_1 = strtok(NULL, "\n");
		g++;
    }  // Ultimo token = ultima fila -> siguiente es columna

	// Guardar info de columnas en lista
    //printf("Recortando cadena...\n");
	char** aux = (char**) malloc(sizeof(char*) * DIM);
	for(int g = 0; g < DIM; g++){
		aux[g] = strtok(NULL, "\n");
        printf("%s\n", aux[g]);
	}
    return aux;
}

int contar(char * frase, char caracter){
	// Función que cuenta las veces que aparece un caracer en un string
	int contador = 0;
	for(int i = 0; i < strlen(frase); i++){
		if(frase[i] == caracter){
			contador++;
		}
	} return contador;
}

char ** strtokLine(char * string){
    int filas = 2 * DIM + 1;
    char** aux = (char**)malloc(sizeof(char*) * filas);

}


void printCiudad(int ** matriz){
	printf("\nCiudad:\n\n");
	for(int i = 0; i < DIM; i++){
        printf("\t");
		for(int j = 0; j < DIM; j++){
			printf("%d ", matriz[i][j]);
		} printf("\n");
	} printf("\n");
}

void desplazarFila(int ** matriz, int fila){
    int * aux = (int*)malloc(sizeof(int) * DIM);
    aux[0] = 0;
    for(int i = 1; i < DIM; i++){  // Copiar valores
        aux[i] = matriz[fila][i-1];
    }
    for(int i = 0; i < DIM; i++){
        matriz[fila][i] = aux[i];
    }
    free(aux);
}

void Entrada(char * nombre_archivo){  //! No abrir
	// Lee el archivo de entrada y lo devuelve como cadena
	printf("Leyendo archivo...\n");
    FILE* flujo = fopen(nombre_archivo, "r");
    fscanf(flujo, "%d", &DIM);  // N
    printf("Dimension de la ciudad = %d", DIM);
    // Comienzo inmediatamente el armado de la ciudad
    ciudad = (int**)malloc(sizeof(int*) * DIM);
    for(int i = 0; i < DIM; i++){
        ciudad[i] = (int*)malloc(sizeof(int) * DIM);
        for(int j = 0; j < DIM; j++){  // Relleno con ceros
            ciudad[i][j] = 0;  // Para evitar nulls
        }
    }
    // Filas
    lenFilas = (int*)malloc(sizeof(int) * (DIM));
    filas = (int**)malloc(sizeof(int*) * (DIM));
    int* cant_grupos = (int*)malloc(sizeof(int) * (DIM));
    int i = 0;
    while(i < DIM){  // Recorro archivo por fila
        fscanf(flujo, "%d", &lenFilas[i]);  // Añado len de linea
        filas[i] = (int*)malloc(sizeof(int) * lenFilas[i]);
        // Añadir edificios a la ciudad
        for(int j = 0; j < lenFilas[i]; j++){  // Recorro la linea
            fscanf(flujo, "%d", &filas[i][j]);
            ciudad[i][j] = filas[i][j];
        }
        i++;
    } printCiudad(ciudad);

    // Columnas
      
    //?
    
    free(lenFilas);
    fclose(flujo);
    return;
}

// BES: Acomodar columnas
int ID;
struct solucion{
    int id;
    int * desplazamientos;
    int ** ciudad;
}typedef solucion;

// Conjunto solucion
solucion * conjunto; int dim_conjunto; // Cantidad de desplazamientos x fila

void printConjunto(int existe_ciudad){
    for(int i = 0; i < dim_conjunto; i++){
        printf("%d. ", conjunto[i]);
        for(int j = 0; j < DIM; j++){  // Imprimir array
            if(j == 0){
                printf("[%d,", conjunto[i].desplazamientos[j]);
            }else if(j == DIM - 1){
                printf(" %d]\n",conjunto[i].desplazamientos[j] );
            }else{
                printf(" %d,", conjunto[i].desplazamientos[j]);
            }
        }

        if(existe_ciudad == 1){
            printCiudad(conjunto[i].ciudad);
        }
    }
   
}


solucion * addSolucion(solucion x){ //! No abrir
    // Agrega un estado al final de la lista
	solucion * aux = (solucion *)malloc(sizeof(solucion)*(dim_conjunto+1));
	for (int i = 0; i < dim_conjunto; i++){  // Cpy
		aux[i] = conjunto[i];
	}
	aux[dim_conjunto] = x;  // Añadir al final
	dim_conjunto = dim_conjunto+1;
	free(conjunto);
	return aux;
}

void printList(int* list){
    for(int h = 0; h < DIM; h++){
        printf("%d ", list[h]);
    } printf("\n");
}

int cmpSolucion(solucion x, solucion y){
    for(int j = 0; j < DIM; j++){  // Valores
        if(x.desplazamientos[j] != y.desplazamientos[j]){
            return 0;
        }
    }
    return 1;
}

int solucionRepetida(solucion x){
    for(int i = 0; i < dim_conjunto; i++){
        if(cmpSolucion(x, conjunto[i]) == 1){
            return 1;
        }
    }
    return 0;
}

int ** cpyCiudad(){  //! No abrir
    int** aux = (int**)malloc(sizeof(int*) * DIM);
    for(int i = 0; i < 0; i++){
        aux[i] = (int*)malloc(sizeof(int) * DIM);
        for(int j = 0; j < 0; j++){
            aux[i][j] = ciudad[i][j];
        }
    }
    return aux;
}

void cpyCiudad2(int ** x, int ** y){
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            x[i][j] = y[i][j];
        }
    }
}

void GenerarCiudadSolucion(int** matriz, int* list){
    for(int i = 0; i < DIM; i++){  // Fila
        for(int j = 0; j < list[i]; j++){
            desplazarFila(matriz, i);
        }
    }
}

void cpyList(int* x, int*y){//! No abrir
    // Copiar valores de y en x
    for(int i = 0; i < DIM; i++){
        x[i] = y[i];
    }
}

void combinatoria(solucion n){
    //printf("Llamada recursiva\n");
    // Lista de DIM elementos...
    // List = [0,0,0], i = 0
    for(int k = 0; k < DIM; k++){  // Caso base
        if(n.desplazamientos[k] > DIM-1){
            //printf("Solucion invalida\n");
            return;
        }
    }

    // Sumar uno a cada casilla, itera x casillas
    for(int j = 0; j < DIM; j++){  
        // Nueva solucion
        solucion a;
        a.id = ID; ID++;
        a.desplazamientos = (int*)malloc(sizeof(int) * DIM);
        for(int f = 0; f < DIM; f++){ // Copiar valores
            a.desplazamientos[f] = n.desplazamientos[f];
        }
        if(a.desplazamientos[j] < DIM-1){
            a.desplazamientos[j] += 1;  // Sumar uno
        }
        
        //printList(a.desplazamientos);
        

        // Ramificación
        if(solucionRepetida(a) == 0){ // Si es nueva solución
            //printf("Solucion nueva\n");
            conjunto = addSolucion(a); // añadir solucion
            //printf("Guardo.\n");
            //printList(a.desplazamientos); 
            combinatoria(a);
        }else{
            //printf("Esta solucion ya existe.\n");
        }
        
    }

}


//! DIFICIL !//
int verificar(solucion x){
    // Fuente de información: char** linea_columna; (array de strings separados por linea de texto (columnas) ).
    for(int c = 0; c < DIM; c++){  // Itero por columna y por linea de texto
        // Verificar columna individualmente
        int puntero = 2; // Me dirijo hacia el primer numero de edificio, como base se parte del 2 porque siempre existe un numero al principio
        int cantidadGrupos = contar(linea_columna[c], '-');
        if(cantidadGrupos >= 2){
            puntero += 2*cantidadGrupos;
        }

        //nuevoString = linea_columna[c][puntero];
        //printf("Nuevo string = %s\t\n", linea_columna[c] + puntero);
        for(int j = 0; j < DIM; j++){ // Recorro misma columna (filas)
            if(x.ciudad[j][c] != 0){
                if(x.ciudad[j][c] != atoi(linea_columna[c] + puntero)){
                    return 0;
                }
                puntero += 2;
            }
        }  // Columna pasó la prueba
    }
    printf("La solucion %d si es la ciudad correspondiente.\n", x.id);
    printCiudad(x.ciudad);
    return 1;
}

int** buscarCiudadSolucion(){
    // Utiliza las formulas solucion para armar cada ciudad
    printf("\nGenerando ciudades solucion...\n");
    for(int i = 0; i < dim_conjunto; i++){ // Recorrer conjunto soluciones
        // Adjudicar memoria
        conjunto[i].ciudad = (int**)malloc(sizeof(int*) * DIM);
        for(int h = 0; h < DIM; h++){
            conjunto[i].ciudad[h] = (int*)malloc(sizeof(int) * DIM);
        }
        //conjunto[i].ciudad = cpyCiudad(); //!NO SIRVE 
        for(int h = 0; h < DIM; h++){
            for(int y = 0; y < DIM; y++){ // Copio la ciudad original
                conjunto[i].ciudad[h][y] = ciudad[h][y];
            }
        }

        //printList(conjunto[i].desplazamientos);
        //! Aqui está el error conjunto[i].ciudad =
        GenerarCiudadSolucion(conjunto[i].ciudad,
                             conjunto[i].desplazamientos);  
        // Aplico desplazamientos
        //printCiudad(conjunto[i].ciudad);
        //printf("%d", conjunto[i].ciudad[0][0]);
        //!
        // Verificar
        
    }
}

// Filtrado 2
int edInColumn(int ** matriz, int columna, int edificio){
    for(int i = 0; i < DIM; i++){
        if(matriz[i][columna] == edificio){
            return 1;
        }
    }
    return 0;
}

int filtro2(solucion x){
    // Buscar cantidad de edificios hay en una columna
    // ¿Como lo hago?
    /*contar cantidad de giones -> hacer (cantidad de guiones+1) strtoks -> hacerles atoi -> sumar

    luego hay que contar la cantidad de edificios distintos de cero por cada fila y columna

    Si son iguales entonces la ciudad es correcta
    */
   for(int i = 0; i < DIM; i++){  // Recorro string y columna

   }
}

int main(int argc, char const *argv[]){
    
    

    // Leer archivo y generar ciudad con filas rellenas
    Entrada("Entrada.in");

    // Leer el archivo como texto para poder analizar columnas
    char * info = LeerEntrada("Entrada.in");
    
    
   

    // BES: Acomodar columnas
    solucion inicial;
    inicial.id = ID; ID++;
    inicial.desplazamientos = (int*) malloc(sizeof(int) * DIM);  // Aqui linea_columna se pierde
    for(int i = 0; i < DIM; i++){inicial.desplazamientos[i] = 0;}
    conjunto = addSolucion(inicial);
    // Generar soluciones
    printf("Generando formulas de solucion...\n");
    combinatoria(inicial); //printConjunto(0);
    printf("Armando ciudades...\n");
    buscarCiudadSolucion(); //printConjunto(1);
    // Filtrar
    linea_columna = extraerColumnasTXT(info);
    // Probando función que verifica una solución
    for(int r = 0; r < dim_conjunto ; r++){
        verificar(conjunto[r]);
    }

    // Buscar solución
    /*
    solucion sol;
    for(int i = 0; i < dim_conjunto; i++){
        if(verificar(conjunto[i])){
            sol = conjunto[i];
        }
    }
    
    cpyCiudad2(ciudad, sol.ciudad);*/
    //! QUEDE EN EL SEGUNDO FILTRADO EXPLICADO EN EL EXCEL: "idea combinatoria"
    

    





    // Fin
    free(conjunto);
    for(int i = 0; i < DIM; i++){
        free(ciudad[i]);
    } free(ciudad);
    printf("\n\nEjecucion finalizada.");
    return 0;
}
