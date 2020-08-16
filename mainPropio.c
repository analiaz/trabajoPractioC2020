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
       	printf(" \n");
    }
}

int main(int argc, char *argv[]){
    printf("%d ", argc);
    for (int i = 0; i < argc; ++i){
        printf("%s \n",argv[i]);
    }
    char* arch1 = "Tests/test1.m";
    matrix_t* matrisTest = NULL;
    matrix_t* matrisTest2 = NULL;
    matrix_t* matrisTest3 = NULL;
    matrix_t* matrisDup = NULL;
    matrix_t* res = NULL;
    matrix_t* null_prub = NULL;
    matrix_t* idt_prub = NULL;

    FILE* f = fopen(arch1, "r");
    if (f == NULL) {
         printf("No se pudo leer el archivo \n"); // error de que no se puede leer el archivo
    }    
    if((err = create_and_fill_matrix(2, 2, 3.5, &matrisTest)) == E_OK)	imprimir_Mat(matrisTest);
    else printf("No se pudo leer la matris o el archivo \n");
    printf("-------\n");
    if((err = create_and_fill_matrix(2, 2, 3.5, &matrisTest2)) == E_OK)	imprimir_Mat(matrisTest);
    printf("---comp----\n");
    if (cmp_matrix(matrisTest, matrisTest2)) printf("Las matrices son iguales \n");
    else printf("las matrices son distintas \n");
   
    printf("\n---mult----\n");
    if ((err = mult(matrisTest, matrisTest2,&res))== E_OK) imprimir_Mat(res);  //funciona mal, no multiplica bien
    else printf("mult no funciona");
    printf("----resize_matrix-----");
    if ((err = resize_matrix(3, 3, &matrisTest)) == E_OK) imprimir_Mat(matrisTest); 
    else printf("no funciona resize");

    printf("---sum----\n");
    if ((err = sum(matrisTest,matrisTest2,&res))== E_OK) imprimir_Mat(res);
    else {
        printf("la suma no funciono, %d \n", err);
    }
    printf("---sum-implace---- \n");
    if ((err = sum_inplace(matrisTest,matrisTest2)) == E_OK) imprimir_Mat(matrisTest2);
    else printf("la suma-implace no funciono %d \n ", err);
    printf("---mult-scalar----\n");
    if ((err = mult_scalar(2.0, matrisTest, &matrisTest2))== E_OK) imprimir_Mat(matrisTest2); 
    else printf(" no funciona");
    printf("---mult-scalar-implace----\n");
    if ((err = mult_scalar_inplace(2.0, matrisTest))== E_OK) imprimir_Mat(matrisTest); 
    else printf(" no funciona ");
    printf("---null----\n");
    if ((err = null_matrix(2, &null_prub)) == E_OK) imprimir_Mat(null_prub);
    else printf("no funciona");

    printf("----clear_matrix------\n");
    if ((err = clear_matrix(matrisTest)) == E_OK) imprimir_Mat(matrisTest);
    else printf("no funciona clear");
/*
    t_list *l = NULL; 

    printf("--------matrix2list----\n");
    if ((err = matrix2list(matrisTest,l)))
    else printf("no funciona clear\n");
*/
  
/*
    printf("\n-----get_col-----------\n");

    printf("\n-------get_row---------\n");
*/
    printf("\n-----free_matrix-----\n");
    if ((err = free_matrix(&matrisTest2))== E_OK){}
    


    printf("\n---dup----\n");
    if ((err = dup_matrix(matrisTest,&matrisDup))== E_OK) imprimir_Mat(matrisDup); 
    else printf("no funciona duplicar");

    printf("\n---idty----\n");
    if ((err = idty_matrix(2, &idt_prub)) == E_OK) imprimir_Mat(idt_prub);
    else printf("no funciona idty\n");

    printf("---read_matrix----\n");
    if ((err = read_matrix(f, &matrisTest3)) == E_OK) imprimir_Mat(matrisTest3);
    else printf("no funciona read");    

    printf("---write_matrix----\n");
    
    char* arch2 = "Tests/prueba.m";
    FILE* f1 = fopen(arch2, "w");
    if ((err = write_matrix(f1, matrisTest3)) == E_OK) printf("se creo \n\n");
    else printf("no funciona read");    



    return 0;
}
