// IMPORTACIONES
#include <stdio.h>
// CONSTANTES
// ESTRUCTURAS
// FUNCIONES
void mostrarfunc(){
	// Función que muestra por pantalla las opciones
}
// XDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
// PRINCIPAL
int main(){
	// ENTRADA
	printf("Ejecucion iniciada");
	int encendido = 1;
	int hacer; mostrarfunc(); scanf("%d", &hacer);
	
	// PROCESAMIENTO
	while(encendido == 1){
		switch(hacer){
				// Opciones...
			case 10:
				encendido = 0;
		}
	}
	
	// SALIDA
	printf("Ejecucion finalizada");
	return 0;
}
