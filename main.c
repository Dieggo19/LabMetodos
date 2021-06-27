#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void imprimirArray1D(char * array, int len){
	for(int i = 0; i < len; i++){
		printf("%c", array[i]);
	}
	printf("\n");
}


char * LeerEntrada(char * nombre_archivo, int * len){
    // Creo el flujo
    FILE * flujo = fopen(nombre_archivo, "r");

    // Contar numero de caracteres
    fseek(flujo, 0, SEEK_END);  // Me voy al final del archivo
    int num_elementos = ftell(flujo);  // Cuento la cantidad de caracteres
    rewind(flujo);  // Vuelvo al principio

    /// Adjudicar memoria para la variable que guarda la info
    char * cadena = (char*) calloc(sizeof(char), num_elementos);
    // Trabajo pesado
    int num_elementos_leidos = fread(cadena, sizeof(char), num_elementos, flujo);
    *len = num_elementos_leidos;
    
    // Cerrar el archivo
    fclose(flujo);
    printf("\nel archivo se ha leido correctamente\n");
    return cadena;
}


void agregar_edificios(char * token, char ** ciudad, int fila){
	printf("token en funcion = %s\n", token);  // token = 4 1 2 1 1
	int len = atoi(token); // 4, numero de edificios
	int c = 0;  // Columna
	int i = 2;
	while(c < len && i < strlen(token)){
		if(token[i] != ' '){
			ciudad[fila][c] = token[i];
			c++;
		}
		i++;
	}
	
	// Imprimir su fila
	/*
	printf("imprimir ed:");
	for(int j = 0; j < len; j++){
		printf("%c ", ciudad[fila][j]);
	} printf("\n");
	*/
	return;
}


void imprimirArray2D(char ** array, int len){
	printf("\nimprimir matriz\n\n");
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			printf("%c ", array[i][j]);
		}
		printf("\n");
	}
}



int main(){
	// ENTRADA
	printf("Ejecucion iniciada."); int len, respuesta; char * info;
	printf("Que entrada va a usar?\n1) Entrada.in\n2) Entrada2.in\n:");
	scanf("%d", &respuesta); printf("Leyendo archivo... ");
	
	// PROCESAMIENTO
	// Lectura de archivo
	if(respuesta == 1){
		info = LeerEntrada("Entrada.in", &len);
	}else{
		info = LeerEntrada("Entrada2.in", &len);
	}
	printf("Lectura finalizada con exito:\n");
	imprimirArray1D(info, len);
	
	// Generar archivo contrario
	if(respuesta == 1){
		// Generar matriz de la ciudad
		char ** ciudad;  // Genero puntero de matriz bidimensional
		char primer_numero[500];  // Genero puntero de primera linea del archivo 'N'
		strcpy(primer_numero, info);  // Copio el string en n LISTO
		char * n = strtok(primer_numero, "\n");  // Obtengo el primer numero
		int dim = atoi(n);  // Lo convierto en int
		// Adjudicar memoria
		ciudad = (char**) malloc(sizeof(char*) * dim);
		for(int j = 0; j < dim; j++){
			ciudad[j] = (char*) malloc(sizeof(char) * dim);
		}

		// presentar generación alfa de la ciudad
		for(int i = 0; i < dim; i++){
			for(int j = 0; j < dim; j++){
				ciudad[i][j] = '0';	
			}
		}
		imprimirArray2D(ciudad, dim); printf("\n");
		// Lectura de info para agregar numeros a la matriz  //
		int leninfo;  // Variable que guarda la cantidad de edificios por fila
		int i = 0; // Iterador de caracter
		int contador_saltolinea = 0;  // Variable que guarda los saltos de linea leidos
		// Mientras haya contado menos de dim saltos de linea
		// Hacer primer token
		char infocopia[500];
		strcpy(infocopia, info);  // copio la info
		char * token = strtok(infocopia, "\n");  // Outplut: 10
		//printf("\n###info#### = \n\n%s\n", info);
		// esto iba en el while contador_saltolinea < dim
		int contador_token = 0;
		int strlentoken;
		while(contador_token < 10){  // Recorrer solo filas
			token = strtok(NULL, "\n");  // 4 1 2 1 1
			strlentoken += strlen(token);
			if(token == NULL){
				printf("nul");
				token = infocopia + strlentoken;
				token = strtok(token, "\n");
			}
			agregar_edificios(token, ciudad, contador_token);  //Fb
			contador_token += 1;
			imprimirArray2D(ciudad, dim);
			}
		imprimirArray2D(ciudad, dim);
	}else{
		// Entrada 2 DIEGO ACUÑA
		// Codigo
	}

	printf("Desea recorrer automatico o manual?\n1) Automatico\n2) Manual ");
	int modo_recorrido; scanf("%d", &modo_recorrido);
	if(respuesta == 1){
		// Automático

	}else{
		// Manual
	}


	// Escribir registro
	printf("\nEjecucion finalizada○\n");
	return 0;
}
