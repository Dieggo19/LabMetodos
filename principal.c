// IMPORTACIONES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_1.h"
#include "funciones_2.h"



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
		int dim = obtener_primer_numero(info);
		printf("Dimension de la matriz: %d\n", dim);

		// PROCESAMIENTO: Crear ciudad
		int ** ciudad; printf("Creando ciudad...\n");
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
		// RECORRIDO AUTOMATICO
	}else{
		// RECORRIDO MANUAL
	}


	// SALIDA
	printf("Programa finalizado.");
	return 0;
}