//Main realizado para testear la libreria mat.h como parte de la practica de...

#include <stdio.h>
#include "list/list.h"
#include "mat.h"
#include <stdlib.h>
#include <string.h>
#include "LeerArchivo.h"
#include "error-mat.h"

error_t err;

void imprimir_Mat(matrix_t* m){
	T_TYPE val = V_NULL;
	for(int i = 0; i <= get_rows(m); ++i) {
    	for (int j = 0; j <= get_cols(m); ++j){
      		if ( (err = get_elem_matrix(i, j, &val, m)) != E_OK) return ;
      		printf("%f ", val);
    	}
    	printf("\n");
    }
}

int main(int argc, char *argv[]){
    
    char* arch1 = "../Test/Test1.m";
    matrix_t* matrisTest = NULL;

    FILE* f = fopen(arch1, "r");
    if((err = read_matrix(f, matrisTest)) == E_OK)	imprimir_Mat(matrisTest);
    else printf("No se pudo leer la matris o el archivo \n");
    return 0;
}
