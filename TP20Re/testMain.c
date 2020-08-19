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
    matrix_t* resS1 = NULL;
    matrix_t* resS2 = NULL;
    matrix_t* resI1 = NULL;
    matrix_t* resI2 = NULL;
    matrix_t* res01 = NULL;    
    matrix_t* resAso1 = NULL;
    matrix_t* resAso2 = NULL;
    matrix_t* resAso3 = NULL;
    matrix_t* null_prub = NULL;  
    matrix_t* idt_prub = NULL;

    FILE* f = fopen(arch1, "r");
    if (f == NULL) {
         printf("No se pudo leer el archivo \n"); 
    }    

    if((err = create_and_fill_matrix(2, 2, 3.5, &matrisTest)) == E_OK)	imprimir_Mat(matrisTest);
    else printf("No se pudo leer la matris o el archivo \n");
    printf("-------\n");
    if((err = create_and_fill_matrix(2, 2, 3.5, &matrisTest2)) == E_OK)	imprimir_Mat(matrisTest);
    printf("---comp----\n");
    if (cmp_matrix(matrisTest, matrisTest2)) printf("Las matrices son iguales \n");
    else printf("las matrices son distintas \n");

/*Propiedades Matematicas*/

    //////////// SUM 

    // Conmutativa 
    // A + B = C
    sum(matrisTest,matrisTest2,&resS1);
    // B + A = D
    sum(matrisTest2,matrisTest,&resS2);
    // C == D , D == C
    fprintf(stderr,"ma + mb == mb + ma :%d %d\n",cmp_matrix(resS1,resS2), cmp_matrix(resS2,resS1));
    FILE *f1 = fopen("write1", "w"); 
    write_matrix(f1, resS1);
    fprintf(stderr,"-----------------\n");
    FILE *f2 = fopen("write2", "w");
    write_matrix(f2, resS2);
    fprintf(stderr,"-----------------\n");
    free_matrix(&resS2);
    free_matrix(&resS1);
    fprintf(stderr,"-----------------\n");

    // Asociativa
    // A + (B + C) = D
    dup_matrix(matrisTest,&resAso1);
    sum(matrisTest2,resAso1,&resAso2);
    sum(matrisTest,resAso2,&resAso3);

    // (A + B) + C = E
    free_matrix(&resAso2);
    sum(matrisTest,matrisTest2,&resAso2); 
    sum(resAso2,resAso1,&resS1);
    // D == E , E == D
    fprintf(stderr,"ma + (mb + mc) == (ma + mb) + mc :%d %d\n",cmp_matrix(resAso3,resS1), cmp_matrix(resS1,resAso3));
    FILE *f3 = fopen("asociativa1", "w");
    write_matrix(f3, resAso3);
    fprintf(stderr,"-----------------\n");
    FILE *f4 = fopen("asociativa2", "w");
    write_matrix(f4, resS1);
    fprintf(stderr,"-----------------\n");
    free_matrix(&resAso3);
    free_matrix(&resS1);
    free_matrix(&resAso2);  
 
 ////////// Mult

 // Identidad Multiplicativa
  // D = A * I
  idty_matrix(get_cols(matrisTest)+1,&idt_prub);  
  mult(matrisTest, idt_prub, &resI1);
  // E = I * A
  mult(idt_prub, matrisTest, &resI2);
  FILE *f5 = fopen("idtMult1", "w");
  write_matrix(f5, resI1);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"(ma * m1) = (m1 * ma) = ma :%d %d %d\n",cmp_matrix(matrisTest,resI1), cmp_matrix(resI1,matrisTest), cmp_matrix(resI1,resI2));
  free_matrix(&resI1);
  free_matrix(&resI2);

// Nulo Multiplicativo
  // D = A * 0 
  null_matrix(get_cols(matrisTest2)+1,&null_prub);  
  mult(matrisTest2,null_prub, &resS1);
  // E = 0 * A
  mult(null_prub, matrisTest2, &resS2);
  FILE * f6 = fopen("NuloMulti", "w");  
  write_matrix(f6, resS1);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"(ma * m0) = (m0 * ma) = ma :%d %d\n",cmp_matrix(resS1,resS2), cmp_matrix(resS2,resS1));
  free_matrix(&resS1);
  free_matrix(&resS2);

  // Nulo Multiplicativo escalar
  // D = esc(0) * A  = 0
  mult_scalar(0.0, matrisTest, &res01);
  FILE * f7 = fopen("NuloMultiEsc", "w");    
  write_matrix(f7, res01);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"(0 * ma) = m0 :%d %d\n",cmp_matrix(res01,null_prub), cmp_matrix(null_prub,res01));
  fprintf(stderr,"-----------------\n");
  free_matrix(&resS1);

    return 0;
}