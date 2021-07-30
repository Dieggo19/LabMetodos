// IMPORTACIONES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_1.h"
#include "funciones_2.h"
#define tab printf("\t");
#define xd printf("xd");

// Variable global
int ** ciudad;

struct estado{
    int id;
    int ** ciudad;
    int pos[2];  // x y
    int transicion;
    struct estado * estado_anterior;
}typedef estado;


// Listados
estado * abierto; int dim_abierto = 1;
estado * cerrado; int dim_cerrado = 0;
estado * solucion; int dim_solucion = 1;

int id = 0;

// Funciones de ciudad
int dim; int ** ciudad_final;

int ** copiar_ciudad(int ** ciudad){
    int ** aux;
    aux = (int**) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        aux[i] = (int*) malloc(sizeof(int) * dim);
        for(int j = 0; j < dim; j++){
            aux[i][j] = ciudad[i][j];
        }
    } return aux;
}

int comparar_ciudades(int ** x, int ** y){
    int i = 0;
    while(i < dim){
        int j = 0;
        while(j < dim){
            if(x[i][j] != y[i][j]){
                return 0;
            } j++;
        }
        i++;
    } return 1;
}



// Funciones sobre listados
estado * quitar_estado(estado * lista, int * dim, estado elemento){  // Usar por valor
    /*Crear una lista nueva con dimensión dim-1
    añadir todos los elementos menos el que se busca
    */
    // Crear array
    estado * aux; 
    aux = (estado*) malloc(sizeof(estado) * (*dim-1));

    int i = 0;
    int j = 0;

    while(i < *dim && j < *dim-1){
        if(lista[i].id != elemento.id){
            aux[j] = lista[i];
            j++;
        }
        i++;
    }
    *dim -= 1;
    return aux;
}

estado * agregar_estado(estado * lista, int *dim, estado elemento){
    // Adjudicar más memoria
    estado * aux;
    aux = (estado*) malloc(sizeof(estado) * (*dim+1));

    // Copiar elementos
    for(int i = 0; i < *dim; i++){
        aux[i] = lista[i];
    }
    
    // Añadir al final
    aux[*dim] = elemento;
    *dim += 1;
    return aux;
}

int esta_en_listado(estado e, estado * listado, int dim_listado){
    int i = 0;
    while(i < dim_listado){
        if(comparar_ciudades(e.ciudad, listado[i].ciudad)){
            return 1;
        }
        i++;
    } return 0;
}

void llenar_lista_soluciones(estado * sol){
    if(sol->id == 0){
        return;
    }
    solucion = agregar_estado(solucion, &dim_solucion, *sol);
    llenar_lista_soluciones(sol->estado_anterior);
}

/// TRANSICIONES ///
estado subir(estado m){ // ID: 1
    //m.ciudad[m.pos[0]][m.pos[1]] > 0 &&
    if(m.pos[0] > 0 &&
       m.ciudad[m.pos[0]-1][m.pos[1]] > 0){
        // Crear nuevo estado
        estado salida;
        id++;
        salida.id = id;
        salida.ciudad = copiar_ciudad(m.ciudad);
        salida.pos[0] = m.pos[0] - 1;
        salida.pos[1] = m.pos[1];
        salida.transicion = 1;
        salida.estado_anterior = &m;

        // Modificar ciudad
        salida.ciudad[m.pos[0]][m.pos[1]] -= 1;
        return salida;
    }
    //printf("No se puede realizar esta accion\n");
    return m;
}

estado bajar(estado m){ // ID: 2
    // m.ciudad[m.pos[0]][m.pos[1]] > 0 &&
    if(m.pos[0] < dim-1 && 
       m.ciudad[m.pos[0] + 1][m.pos[1]] > 0){
        // Crear nuevo estado
        estado salida;
        id++;
        salida.id = id;
        salida.ciudad = copiar_ciudad(m.ciudad);
        salida.pos[0] = m.pos[0] + 1;
        salida.pos[1] = m.pos[1];
        salida.transicion = 2;
        salida.estado_anterior = &m;

        // Modificar ciudad
        salida.ciudad[m.pos[0]][m.pos[1]] -= 1;
        return salida;
    }
    //printf("No se puede realizar esta accion\n");
    return m;

}

estado izquierda(estado m){ // ID: 3
    //m.ciudad[m.pos[0]][m.pos[1]] > 0 &&
    if(m.pos[1] > 0 && 
       m.ciudad[m.pos[0]][m.pos[1] - 1] > 0){
        // Crear nuevo estado
        estado salida;
        id++;
        salida.id = id;
        salida.ciudad = copiar_ciudad(m.ciudad);
        salida.pos[0] = m.pos[0];
        salida.pos[1] = m.pos[1] - 1;
        salida.transicion = 3;
        salida.estado_anterior = &m;
        // Modificar ciudad
        salida.ciudad[m.pos[0]][m.pos[1]] -= 1;
        return salida;
    }
    //printf("No se puede realizar esta accion\n");
    return m;

}

estado derecha(estado m){ // ID: 4
    //m.ciudad[m.pos[0]][m.pos[1]] > 0 &&
    if(m.pos[1] < dim-1 &&
       m.ciudad[m.pos[0]][m.pos[1] + 1] > 0){
        // Crear nuevo estado
        estado salida;
        id++;
        salida.id = id;
        salida.ciudad = copiar_ciudad(m.ciudad);
        salida.pos[0] = m.pos[0];
        salida.pos[1] = m.pos[1] + 1;
        salida.transicion = 4;
        salida.estado_anterior = &m;
        // Modificar ciudad
        salida.ciudad[m.pos[0]][m.pos[1]] -= 1;
        return salida;
    }
    //printf("No se puede realizar esta accion\n");
    return m;
}

void imprimir_accion(int direccion){
    if(direccion == 0){
        printf("Subir\n");
    }else if(direccion == 1){
        printf("Izquierda\n");
    }else if(direccion == 2){
        printf("Derecha\n");
    }else if(direccion == 3){
        printf("Abajo\n");
    } return;
}

void verificar_estado(estado b){
    //printf("Esta en ambos listados? -> ");
    if(esta_en_listado(b, abierto, dim_abierto) == 0
    && esta_en_listado(b, cerrado, dim_cerrado) == 0){
        //printf("No\nAgregar estado a abierto\n\n");
        // Agregar a a abierto
        abierto = agregar_estado(abierto, &dim_abierto, b);
    }else{ // Borrar
        //printf("Si\n\n");
    }
}

void aplicar_transiciones(estado e){
    int s = 0;
    estado a;
    while(s < 4){
        //printf("Case %d: ", s);
        //imprimir_accion(s);
        if(s == 0){
            // Norte
            //printf("Subir\n");
            a = subir(e);
        }else if(s == 1){
            // Oeste
            //printf("Izquierda\n");
            a = izquierda(e); 

        }else if(s == 2){
            // Este
            //printf("Derecha\n");
            a = derecha(e);

        }else if(s == 3){
            // Sur
            //printf("Bajar\n");
            a = bajar(e);
        }

        // si a no está ni en abiertos ni en cerrados agregar a en
        // abiertos
        verificar_estado(a);        
        s++;
    }
}

// FUNCIONES COMUNES PARA EL BEE
void imprimir_ciudad(int ** ciudad, int dim){
    printf("Ciudad:\n");
    for(int i = 0; i < dim; i++){
        printf("\t");
        for(int j = 0; j < dim; j++){
            printf("%d ", ciudad[i][j]);
        } printf("\n");
    }
    printf("\n\n");
}

void imprimir_estado_inicial(estado e){
    printf("Estado inicial:\n");
    printf("Id: %d\n", e.id);
    imprimir_ciudad(e.ciudad, dim);
}

void imprimir_estado(estado e){
    printf("Id: %d\n", e.id);
    printf("Transicion: %d\n", e.transicion);
    imprimir_ciudad(e.ciudad, dim);
}

void imprimir_solucion(estado * solucion){
    for(int i = dim_solucion - 2; i >= 0; i--){
        imprimir_accion(solucion->transicion);
    }
    return;
}

void imprimir_listado(estado * listado, int dim_listado){
    if(dim_listado == 0){
        printf("NULL");
    }else if(dim_listado == 1){
        if(listado[0].id > 1000){
            printf("[NULL]");    
        }else{
            printf("[%d]", listado[0].id);
        }
    }else{
        for(int i = 0; i < dim_listado; i++){
            if(i == 0){
                printf("[%d,", listado[i].id);
            }else if(i > 0 && i < dim_listado - 1){
                printf(" %d,", listado[i].id);
            }else{
                printf(" %d]");
            }
        } 
    }
    printf("\n");
    return;
}

int cantidad_estados_anteriores(estado * p, int contador){
    if(p->id == 0){ // Estado inicial
        return contador;
    }
    contador++;
    cantidad_estados_anteriores(p->estado_anterior, contador);
}

void imprimir_soluciones(){
    for(int i = dim_solucion; i >= 0; i++){
        imprimir_accion(solucion[i].transicion);
    }
    return;
}

int main()
{	// Pedir tipo de entrada
	printf("\nEjecucion iniciada\n"); printf("Que archivo desea leer?\n");
	printf("1) Entrada.in\n2) Entrada2.in\n: "); int respuesta;
	entrada_respuesta(&respuesta); 

	// Lectura de archivo y generación de archivo opuesto
	if(respuesta == 1){
		//           Entrada.in           // 
		int len;
		char * info = LeerEntrada("Entrada.in", &len);
		
		// Obtener dimensión de la matriz
		dim = obtener_primer_numero(info);
		printf("Dimension de la matriz: %d\n", dim);

		// PROCESAMIENTO: Crear ciudad
		printf("Creando ciudad...\n");
		ciudad = (int**) malloc(sizeof(int*) * dim);
		for(int j = 0; j < dim; j++){// Convertir en 2D
			ciudad[j] = (int*) malloc(sizeof(int) * dim);}
		rellenar_matriz(ciudad, dim); // Rellenar con ceros

		// Rellenar filas
		printf("Agregando edificios...\n");
		insertar_filas(info, ciudad, dim);
		

		// Acomodar columnas
		printf("Acomodando columnas...\n");
		acomodar_columnas(info, ciudad, dim);
		imprimirArray2D(ciudad, dim);
			
		
	}else{
		//			Entrada2.in 			//
        int n = 0;
        int **mapa = leerEntrada(&n);
        FILE *ArchivoSalida = fopen("Salida2.in", "w");
        printf("\n");
        

        // IMPRIMIR DATOS OBTENIDOS
        printf("ENTRADA\n");
        fprintf(ArchivoSalida, "%d\n", n);
        printf("%d\n", n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ", mapa[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
        
        //RECORRER FILAS 
        printf("SALIDA\n");
        printf("%d\n", n);
        for (int i = 0; i < n; i++)
        {
            int acum = 0;
            for (int j = 0; j < n; j++)
            {
                if(mapa[i][j] != 0){
                    acum++;
                }
            }
            fprintf(ArchivoSalida, "%d ", acum);
            printf("%d ", acum);
        // printf("\n");
            for (int j = 0; j < n; j++)
            {
                if(mapa[i][j] != 0){
                fprintf(ArchivoSalida, "%d ", mapa[i][j]);
                printf("%d ", mapa[i][j]);
                }
            }
            fprintf(ArchivoSalida, "\n");
            printf("\n");
        }

        //RECORRER COLUMNAS
        for(int i = 0; i < n; i++)
        {
            int contador = 0;
            for (int j = 0; j < n; j++)
            {
                if(mapa[j][i] != 0){
                    contador++;
                }
            }
            fprintf(ArchivoSalida, "%d ", contador);
            printf("%d ", contador);
            for (int j = 0; j < n; j++)
            {
                if(mapa[j][i] != 0){
                fprintf(ArchivoSalida, "%d ", mapa[j][i]);
                printf("%d ", mapa[j][i]);
                }
            }
            fprintf(ArchivoSalida, "\n");
            printf("\n");
        }
        fclose(ArchivoSalida);
        printf("\nArchivo creado correctamente, revise salida2.in\n\n");
		
	}



	// RECORRER CIUDAD
	printf("Desea recorrer de manera automatica o manual?"
		   "\n1) Automatica\n2) Manual\n: "); int modo;
	entrada_respuesta(&modo);

	if(modo == 1){
		// RECORRIDO AUTOMATICO (BEE) DANIEL CATALÁN
        // LISTADOS
        abierto = (estado*) malloc(sizeof(estado) * dim_abierto);
        // cerrado = (estado*) malloc(sizeof(estado) * dim_cerrado);
        

        // ESTADO INICIAL
        imprimir_ciudad(ciudad, dim);
        
        // Agregar estado inicial a listado abierto
        abierto[0].id = id;
        abierto[0].ciudad = copiar_ciudad(ciudad);
        // Posicion
        abierto[0].pos[0] = 0;
        abierto[0].pos[1] = 4;
        abierto[0].transicion = 0;
        estado anterior;
        anterior.id = -1;
        abierto[0].estado_anterior = &anterior;
        //imprimir_estado_inicial(abierto[0]);

        // ESTADO FINAL (rellenar con ceros)
        ciudad_final = (int**) malloc(sizeof(int*) * dim);
        for(int i = 0; i < dim; i++){
            ciudad_final[i] = (int*) malloc(sizeof(int) * dim);
            for(int j = 0; j < dim; j++){
                ciudad_final[i][j] = 0;
            }
        }

        


        // ALGORITMO
        int itera = 1;
        int e_s = 0;
        while(dim_abierto > 0){
            //printf("%d iteracion", itera);
            //printf("\nlistados iniciales:\n"); 
            //printf("Abierto = "); imprimir_listado(abierto, dim_abierto);
            //printf("Cerrado = "); imprimir_listado(cerrado, dim_cerrado);

            estado e = abierto[0];
            //printf("Estado de al frente: %d\n", e.id); 
            //imprimir_estado(e);
            
            abierto = quitar_estado(abierto, &dim_abierto, e);
            //printf("Quitarlo del listado abierto:\n");
            //printf("Abierto = "); imprimir_listado(abierto, dim_abierto);

            // Ver si es estado objetivo
            //printf("Es solucion? ->");
            if(comparar_ciudades(e.ciudad, ciudad_final)){
                //printf("Si");
                
                // Devolver secuencia de acciones que llevaron a e
                //int dim_sol = cantidad_estados_anteriores(e, 0);
                llenar_lista_soluciones(&e);
                imprimir_soluciones();
                e_s = 1;
                break;
            }

            //printf("Agregarlo al listado cerrado: \n");
            cerrado = agregar_estado(cerrado, &dim_cerrado, e);
            //printf("Cerrado = "); imprimir_listado(cerrado, dim_cerrado);
            // Para cada posible acción a
            //printf("Aplicando transiciones...\n");
            aplicar_transiciones(e);
            itera++;
        }
        printf("\nFin de la busqueda\n");
        if(e_s == 0){
            printf("No existe solucion\n");
        }




	}else{
		// RECORRIDO MANUAL
	}


	// SALIDA
    FILE * salida1 = fopen("primerasalida.out", "w");
    escribir_salida1(ciudad, dim, salida1);
    fclose(salida1);
	printf("Programa finalizado.");
	return 0;
}