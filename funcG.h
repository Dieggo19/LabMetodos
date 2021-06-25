#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Leer una entrada y retornar puntero con la info (string)
char * LeerEntrada(char * nombre_archivo){
    // Creo el flujo
    FILE * flujo = fopen(nombre_archivo, "rb");

    // Contar numero de caracteres
    fseek(flujo, 0, SEEK_END);  // Me voy al final del archivo
    int num_elementos = ftell(flujo);  // Cuento la cantidad de caracteres
    rewind(flujo);  // Vuelvo al principio

    /// Adjudicar memoria para la variable que guarda la info
    char * cadena = (char*) calloc(sizeof(char), num_elementos);
    // Trabajo pesado
    int num_elementos_leidos = fread(cadena, sizeof(char), num_elementos, flujo);
    
    // Cerrar el archivo
    fclose(flujo);
    printf("\n\n el archivo se ha leido correctamente");
    return cadena;  // En esta variable está todo, es un puntero
    // Esta salida es imprimible: printf("%s", cadena);
}



