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

void test_row(){
    double values[] = {0,1,2,0,5.6,2,5,6.3,7,199.999,342.4,0.0};
    matrix_t a, *b = NULL;
    a.cols = 4;
    a.rows = 3;
    a.data = values;
    int res = 0;
    t_list l = NULL, c = NULL;
    if (!(res = get_row(1, b, &l))){
        printf("ERROR: get_row (punteros nulos) %d\n", res);
        list_free(&l);
    }
    if ((res = get_row(1, &a, &l)) != 0){
        printf("ERROR: get_row %d\n", res);
    } else {
        int i = 4;
        for(t_list a = l; a != NULL; a = a->next){
            if(a->data != values[i]){
                printf("ERROR: get_row [%d] = %f esperaba %f\n", i, a->data, values[i]);
            }
            i++;
        }
        if(i != 8){
            printf("ERROR: get_row no copio la fila %d\n", i);
        }
    }
    list_free(&l);

    list_add(&l, 500);
    c = l;
    if ((res = get_row(1, &a, &l)) != 0){
        printf("ERROR: get_row %d\n", res);
    } else {
        int i = 4;
        for(t_list a = l; a != NULL; a = a->next){
            if(a->data != values[i]){
                printf("ERROR: get_row [%d] = %f esperaba %f\n", i, a->data, values[i]);
            }
            i++;
        }
        if(i != 8){
            printf("ERROR: get_row no copio la fila %d\n", i);  
        }
    }
    if (c != l){
        list_free(&c);
    }
    list_free(&l);

    if ((res = get_row(3, &a, &l)) == 0){
        printf("ERROR: get_row fuera de rango %d\n", res);
        list_free(&l);
    }
}

void test_col(){
    double values[] = {0,1,2,0,5.6,2,5,6.3,7,199.999,342.4,0.0};
    matrix_t a, *b = NULL;
    a.cols = 4;
    a.rows = 3;
    a.data = values;
    int res = 0;
    t_list l = NULL, c = NULL;
    if (!(res = get_col(1, b, &l))){
        printf("ERROR: get_col (punteros nulos) %d\n", res);
        list_free(&l);
    }
    if ((res = get_col(1, &a, &l)) != 0){
        printf("ERROR: get_col %d\n", res);
    } else {
        int i = 1;
        for(t_list a = l; a != NULL; a = a->next){
            if(i >= 12 || a->data != values[i]){
                printf("ERROR: get_col [%d] = %f esperaba %f\n", i, a->data, (i<12)?values[i]:-1);
            }
            i+=4;
        }
        if(i != 13){
            printf("ERROR: get_col no copio la columna %d\n", i);
        }   
    }
    list_free(&l);

    list_add(&l, 500);
    c = l;
    if ((res = get_col(1, &a, &l)) != 0){
        printf("ERROR: get_col %d\n", res);
    } else {
        int i = 1;
        for(t_list a = l; a != NULL; a = a->next){
            if(i >= 12 || a->data != values[i]){
                printf("ERROR: get_col [%d] = %f esperaba %f\n", i, a->data, (i<12)?values[i]:-1);
            }
            i+= 4;
        }
        if(i>13 || i<=9){
            printf("ERROR: get_col no copio la columna %d\n", i-4);
        }
    }
    if (c != l){
        list_free(&c);
    }
    list_free(&l);

    if ((res = get_col(4, &a, &l)) == 0){
        printf("ERROR: get_col fuera de rango %d\n", res);
        list_free(&l);
    }
}

void test_list(){
    double values[] = {0,1,2,0,5.6,2,5,6.3,7,199.999,342.4,0.0};
    matrix_t a, *b = NULL;
    a.cols = 4;
    a.rows = 3;
    a.data = values;
    int res = 0;
    t_list l = NULL, c = NULL;
    if ((res = matrix2list(b, &l)) == 0){
        printf("ERROR: matrix2list (punteros nulos) %d\n", res);
        list_free(&l);
    }
    if ((res = matrix2list(&a, &l)) != 0){
        printf("ERROR: matrix2list %d\n", res);
    } else {
        int i = 0;
        t_list a = l;
        for(; a != NULL; a = a->next){
            if(i >= 12 || a->data != values[i]){
                printf("ERROR: matrix2list [%d] = %f esperaba %f\n", i, a->data, (i<12)?values[i]:-1);
            }
            i++;
        }
        if(i!=12){
            printf("ERROR: matrix2list no copio matriz %d\n", i);
        }
    }
    list_free(&l);

    list_add(&l, 500);
    c = l;
    if ((res = matrix2list(b, &l)) == 0){
        printf("ERROR: matrix2list (punteros nulos) %d\n", res);
        list_free(&l);  
    }
    if ((res = matrix2list(&a, &l)) != 0){
        printf("ERROR: matrix2list %d\n", res);
    } else {
        int i = 0;
        t_list a = l;
        for(; a != NULL; a = a->next){
            if(i >= 12 || a->data != values[i]){
                printf("ERROR: matrix2list [%d] = %f esperaba %f\n", i, a->data, (i<12)?values[i]:-1);
            }
            i++;
        }
        if(i!=12){
            printf("ERROR: matrix2list no copio matriz %d\n", i);
        }
    }
    if (c != l){
        list_free(&c);
    }
    list_free(&l);
}

int main(int argc, char *argv[]){
    void (*ptr[])() = {
        test_row,
        test_col,
        test_list
    };
    
    for (int i = 0; i < sizeof(ptr)/sizeof(void*); i++){
        (*ptr[i])();
    }

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
