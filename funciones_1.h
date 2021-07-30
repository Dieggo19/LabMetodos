
void entrada_respuesta(int * respuesta){
	scanf("%d", respuesta);
	while(*respuesta != 1 && *respuesta != 2){
		printf("Respuesta invalida, ingrese una correcta: ");
		scanf("%d", respuesta);
	} return;
}


void imprimirArray1D(char * array, int len){
	for(int i = 0; i < len; i++){
		printf("%c", array[i]);
	}
	printf("\n");
}



char * LeerEntrada(char * nombre_archivo, int * len){
	// Lee el archivo de entrada y lo devuelve como cadena
	printf("Leyendo archivo...\n");
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
    printf("El archivo se ha leido correctamente:\n\n");
    imprimirArray1D(cadena, *len); printf("\n");
    return cadena;
}



int obtener_primer_numero(char * info){
	// Obtiene el primer numero del string archivo
	char primer_numero[500]; strcpy(primer_numero, info); // Copiar información
	char * n = strtok(primer_numero, "\n");  // Primera linea
	int dim = atoi(n); // Convertir en int
	return dim;
}


void imprimirArray2D(int ** array, int len){
	// Imprime una matriz int
	printf("\nMatriz:\n\n");
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}


void rellenar_matriz(int ** matriz, int dim){
	// Rellena una matriz con ceros en todas sus casillas
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			matriz[i][j] = 0;	
		}
	} return;
}


void agregar_edificios(char * token, int ** ciudad, int fila){
	// Agrega edificios a una fila de la matriz
	int len = atoi(token); // primer numero: numero de edificios 
	int c = 0;  // Columna
	int i = 2;  // Itador que comienza en el segundo numero (primer edificio)
	while(c < len && i < strlen(token)){
		if(token[i] != ' '){
			ciudad[fila][c] = token[i] - 48;
			c++;
		}
		i++;
	}
	return;
}


void insertar_filas(char * info, int ** ciudad, int dim){
	// Agrega todos los edificios a la matriz segun fila (falta ordenarlos después)
	// Respaldar
	char infocopia[500]; strcpy(infocopia, info); 

	// Primer token
	char * token = strtok(infocopia, "\n");  // Outplut: 10
	int contador_token = 0;
	int strlentoken;

	// Mientras haya contado menos de dim saltos de linea
	while(contador_token < dim){  // Recorrer solo filas
		token = strtok(NULL, "\n");  // 4 1 2 1 1
		strlentoken += strlen(token);
		if(token == NULL){
			printf("NULL\n");
			token = infocopia + strlentoken;
			token = strtok(token, "\n");
		}
		agregar_edificios(token, ciudad, contador_token);
		contador_token += 1;
		}
	imprimirArray2D(ciudad, dim);
}


void desplazar(int ** ciudad, int dim, int fila){
	// Desplaza los elementos de una fila de una matriz en 1 espacio

	int * aux = (int*) malloc(sizeof(int) * (dim+1));
	// hacer copia corregida
	for(int i = 0; i < dim; i++){  // dim - 1 ?
		aux[i+1] = ciudad[fila][i];
	}

	// Asignar ceros
	for(int i = 0; i < dim; i++){
		if(aux[i] > 9 || aux[i] < 0){
			aux[i] = 0;
		}
	}

	// Sobre escribir
	for(int z = 0; z < dim; z++){
		ciudad[fila][z] = aux[z];
	}
	return;
}


void acom(int ** ciudad, int ** edificios, int * len_ed, int lenlen, int dim,int columna){
	// Función que acomoda una columna determinada de la matriz
	//printf("\n\n\n ##### inicio de acom ##### \n\n");
	// Columna constante
	// Grupo constante
	// Asumir que no es columna nula
	
	
	// Grupo len_ed
	int fila = 0;  // Iterador de fila
	int grupo = 0;  // Iterador de 
	// Fila
	while(fila < dim && grupo < lenlen){
		int contador_edificio = 0;

		// Grupo
		//printf("Grupo %d\n", grupo+1);
		//printf("\tContador edificio = %d\n", contador_edificio);
		//printf("\tlen_ed[grupo] = %d\n", len_ed[grupo]);
		//printf("\tlenlen = %d\n", lenlen);
		

		//printf("\tcontador_edificio (%d) < len_ed[grupo] (%d) = %d\n", contador_edificio,len_ed[grupo],contador_edificio < len_ed[grupo]);
		//printf("\tgrupo < lenlen = %d\n", grupo < lenlen);
		while(contador_edificio < len_ed[grupo] && grupo < lenlen && fila < dim){
			//printf("\n2do while\n");
			//printf("\nciudad[%d][%d] = %d\n",fila, columna,ciudad[fila][columna]);
			//printf("Busco el siguiente numero:\n");
			//printf("\tEs distinto de 0? ");
			// Moverme al siguiente numero

			// Este if no se está ejecutando
			if(ciudad[fila][columna] != 0){
				//printf("Si\n");
				//printf("\tMe muevo al siguiente numero\n");
				
				// Busco x, es x?
				//printf("\t\tBusco %d, es %d? ", edificios[grupo][contador_edificio], edificios[grupo][contador_edificio]);
				//printf("\n\t\tedificios[grupo][contador_edificio] = %d ->", edificios[grupo][contador_edificio]);
				
				
				if(ciudad[fila][columna] == edificios[grupo][contador_edificio]){  // ciudad[fila][columna] == edificios[grupo][contador_edificio]
					//printf(" Si \n");
					fila++; // Bajo
					//printf("\t\tBajo\n");
					contador_edificio++;  // Busco el sgte edificio
					
				} else{
					//printf("No\n");
					desplazar(ciudad, dim, fila);
					//printf("Desplazo\n");
					//fila++;
				}
				
			}else{
				//printf("No\n");
				//printf("Bajo\n");
				fila++;
			}

			



		//imprimirArray2D(ciudad, dim);
		//printf("\n\n");
		}

		
		
		// Fin del grupo
		//printf("\tFin del grupo\n\n", grupo);
		// Si no es vacío, desplazar
		//printf("Es vacio?");
		if(grupo < lenlen-1){
			while(ciudad[fila][columna] != 0 && grupo < lenlen){
			//printf(" No\n");
			//printf("Desplazar\n");
			desplazar(ciudad, dim, fila);
			}
		} ////////////////////////////////////////////// AQUI PODRÍA HABER ALGO
		
		//imprimirArray2D(ciudad, dim);
		// Me muevo al siguiente grupo
		grupo++;
	}
}


void columna_cero(int ** ciudad, int dim, int columna){
	// Función que cambia a valor cero una columna (reemplaza valores)
	for(int i = 0; i < dim; i++){
		ciudad[i][columna] = 0;
	}
	return;
}


void insertar_columna_cero(int ** ciudad, int dim, int c){
	// Función que inserta una columna nula (desplaza elementos)
	for(int h = 0; h < dim; h++){
		desplazar(ciudad, dim, h);
	} columna_cero(ciudad, dim, c);
	//imprimirArray2D(ciudad, dim);
	return;
}



int contar(char * frase, char caracter){
	// Función que cuenta las veces que aparece un caracer en un string
	int contador = 0;
	for(int i = 0; i < strlen(frase); i++){
		if(frase[i] == caracter){
			contador++;
		}
	}
	return contador;
}


int * len_cada_grupo(char * token, int * len_grupos){
	// Función que devuelve un array con la cantidad de edificios por fila
	// Cantidad de grupos
	int cantidad_grupos = contar(token, '-') + 1;
	// Creo filas
	len_grupos = (int*) malloc(sizeof(int) * cantidad_grupos);

	
	// Copiar info principal
	char len[500]; strcpy(len, token);

	// Primer Token
	char * grupoX = strtok(len, "-");  //printf("primer grupox = %s\n\n", grupoX);
	int num = atoi(grupoX); //printf("%d ", num);
	len_grupos[0] = num; //printf("int * len_grupos = [%d", num);

	
	// Resto de tokens
	int i = 1; 
	while(grupoX != NULL && i < cantidad_grupos){
		//printf("i = %d\n", i);
		grupoX = strtok(NULL, "-");
		//printf("grupox = %s\n", grupoX);
		if(grupoX != NULL){
			num = atoi(grupoX);
			//printf("%d ", num);
			len_grupos[i] = num;
			//printf(" %d",num);
			i++;
		}

	} //printf("]\n");
	return len_grupos;
}


int ** edificios(char * token){
	// Función que devuelve un lista con sub listas de tamaño(primer numero de una linea del archivo)
	// Y que en cada casilla está inserto un edificio
	// Creo array de salida
	int ** salida;
	
	// Cantidad de grupos
	int cantidad_guiones = contar(token, '-') + 1;

	//printf("cantidad de guiones = %d\n", cantidad_guiones);
	salida = (int**) malloc(sizeof(int*) * cantidad_guiones);
	
	// Adjudicar por edificios en cada grupo
	char copia[500]; strcpy(copia, token);
	int * lista_lens = (int*) malloc(sizeof(int) * cantidad_guiones);

	// Primer token
	char * len = strtok(copia, "-");
	//printf("Primer token = %s\n", len);
	int tamano = atoi(len);
	//printf("Primer tamano = %d\n", tamano);
	salida[0] = (int*) malloc(sizeof(int) * tamano);
	lista_lens[0] = tamano;

	// Resto de tokens
	int iterador = 1;
	while(len != NULL && iterador < cantidad_guiones){
		len = strtok(NULL, "-");
		if(len != NULL){
			tamano = atoi(len);
			//printf("tamano = %d\n", tamano);
			salida[iterador] = (int*) malloc(sizeof(int) * tamano);
			lista_lens[iterador] = tamano;
			iterador++;
		}
	}


	// Añadir edificios a la lista //
	char linea[500]; strcpy(linea, token);
	//printf("Token inicial: %s\n\n", token);

	// Hacer n-1 tokens por guion
	char * string_edificios = strtok(linea, "-");
	//printf("Primer token por guion %s\n", string_edificios); // 4
	int z = 1;
	while(z < cantidad_guiones){
		string_edificios = strtok(NULL, "-");
		//printf("Resto de tokens: %s\n", string_edificios);
		z++;
	}

	//2 2 2 2 1 1 2 1
	// Primer token


	// ERROR: LISTA LENS

	//printf("Token de entrada: %s\n", string_edificios);
	//printf("\n\nAsignacion de edificios:\n");
	char * tok = strtok(string_edificios, " ");  // separar por edificios
	//printf("char * tok = %s\n", tok);
	
	int y;
	//printf("Lista lens:\n");
	//printf("[%d, %d, %d]\n", lista_lens[0], lista_lens[1], lista_lens[2]);
	for(int u = 0; u < cantidad_guiones; u++){
		y = 0;
		//printf("\nlista_lens[u] = %d", lista_lens[u]);
		while(y < lista_lens[u] && tok != NULL){

			
			char * yyy = strtok(NULL, " ");
			
			if(yyy != NULL){////////////////////////
				salida[u][y] = atoi(yyy);
				//printf("%s\n", yyy);
				//printf("\nsalida[%d][%d] = %d\n",u,y, salida[u][y]);
			}
			y++;
		

		}

	}

	// imprimir_matriz_X2D(salida, cantidad_guiones, lista_lens);

	// Imprimir array
	/*
	printf("Edificios:\n");
	for(int v = 0; v < cantidad_guiones; v++){  // Fila
		for(int r = 0; r < lista_lens[v]; r++){  // Columna
			printf("%d ", salida[v][r]);
		}
		printf("\n");
	}*/

	//printf("Lista lens222:\n");
	//printf("[%d, %d, %d]\n", lista_lens[0], lista_lens[1], lista_lens[2]);

	// Tenemos entonces 2 cosas listas dentro de acá
	// Listado de edificios separados por grupos
	// Lista de lens

	// Se podría invocar la función que añade los grupos acá?

	// Solo me falta el len de Lista de lens
	/* ¿Como lo calculo?
			Es la cantidad de guiones

	// Entonces estamos listos para invocar la función que acomoda
	// Los edificios*/



	//printf("Fin de edificios\n");
	return salida;
}

int es_vacio(char * listado_1){
	// Función que devuelve 1 si un string es columna vacio
	// 0 si no
	// Si es columna cero
	int boolean = strcmp(listado_1, "0");
	if(boolean == 0){
		boolean = 1;
	}else{
		boolean = 0;
	}
	return boolean;
}




void acomodar_columnas(char * info, int ** ciudad, int dim){
	// Función que junta todas las funciones anteriores y acomoda todas las columnas de la matriz
	// Quitar las filas de info
	char listado[500]; strcpy(listado, info);  // Copio info
	char * listado_1 = strtok(listado, "\n"); // N
	int g = 0;
	while(g < dim){
		listado_1 = strtok(NULL, "\n");
		g++;}  // Resultado: ultima linea de fila

	// Guardar info de columnas en lista
	char ** lista_columna = (char**) malloc(sizeof(char*) * dim);
	for(int g = 0; g < dim; g++){
		lista_columna[g] = strtok(NULL, "\n");
	}
	
		
	// Proceso
	int c = 0; //printf("\n\n# Proceso #\n");
	while(c < dim && listado_1 != NULL){ // Itero por columna

		////listado_1 = strtok(NULL, "\n");  // Info columna
		listado_1 = lista_columna[c];
		// ¿Por qué listado_1 se vuelve null en la segunda ejecución?
		/* ¿que hacer?
				Revisar todas las funciones que la invoquen para ver que función la deja inutil*/

		//printf("c = %d\n",c);
		//printf("Token columna = '%s' ", listado_1);

		// Si la linea no es nula
		//printf("Es nula?");
		if(listado_1 != NULL){
			//printf(" No\n");

			// Si es columna cero
			//printf("Es columna cero? ");
			if(es_vacio(listado_1)){  // REVISAR
				//printf("Si\n");
				insertar_columna_cero(ciudad, dim, c);// Columna cero
			}else{
				//printf("No\n");
				int * len_grupos = len_cada_grupo(listado_1, len_grupos);  // [1,2,3]
				int lenlen = contar(listado_1, '-') + 1; //printf("lenlen = %d\n",lenlen); // REVISAR [3]
				int ** eds = edificios(listado_1);  // REVISAR [[1],[2,3],[4,5,6]]
				acom(ciudad, eds, len_grupos, lenlen, dim, c);  // REVISAR
			}
		}else{
			//printf(" Si\n");
		}


		c++;
		//imprimirArray2D(ciudad, dim);


	} // Fin del while
	return;

}



void escribir_salida1(int ** ciudad, int dim, FILE * salida1){
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			fprintf(salida1, "%d ", ciudad[i][j]);
		} fprintf(salida1, "\n");
	} return;
}
