// IMPORTACIONES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_1.h"
// Agrega acá: ' #include "funciones_2.h  '



int main(int argc, char const *argv[])
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
		// DIEGO ACUÑA (BORRAR ESTE COMENTARIO DESPUÉS)

		// Funcion que lee archivo:
		// LeerEntrada("nombre_archivo.in", puntero_de_dimension (tipo int))



		/*


			                <CODIGO>


		*/
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






