/*matrix.h, list.h, matrix.c, lista.c*/
//index.c

#include <stdio.h>
#include "list/list.h"
#include "mat.h"
#include <stdlib.h>
#include <string.h>
#include "LeerArchivo.h"
#include "error-mat.h"


error_t procesar_funciones(FILE *f1, FILE *f2, char *archS, char *op, T_TYPE scalar){
    matrix_t *ma = NULL, *mb = NULL, *ms = NULL;
    error_t e;
    // TEST if (strcmp(string, "B1") == 0)  {   // do something }  else if (strcmp(string, "xxx") == 0) {   // do something else } /* more else if clauses */ else /* default: */ { }
    if (strcmp(op,"dup") == 0){ 
        /*leer la matriz
        dup_matr que recibe una matriz y devuelveotra matriz
        escribo la matriz (devolviendola en un file) */
        if ( (e = (read_matrix(f1, &ma))) != E_OK) return e;
        if ( (e = (dup_matrix(ma, &ms))) != E_OK) return e;
        FILE *fout = fopen(archS,"w");
        if ( (e = (write_matrix(fout, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op,"sum") == 0) {
        if ((e = (read_matrix(f1, &ma))) != E_OK) return e;
        if ((e = (read_matrix(f2, &mb))) != E_OK) return e;
        if ((e = (sum(ma, mb, &ms))) != E_OK) return e;
        FILE *f3 = fopen(archS,"w");
        if ((e = (write_matrix(f3, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op, "mult_scalar") == 0){
        if ((e = (read_matrix(f1, &ma))) != E_OK){printf("fallo el read"); return e;}
        if ((e = create_and_fill_matrix(get_rows(ma)+1, get_cols(ma)+1, 0.0, &ms)) != E_OK) return e;
        if ((e = (mult_scalar(scalar, ma, &ms))) != E_OK){printf("fallo multiescalar"); return e;};       
        FILE *fout = fopen(archS,"w");
        if ((e = (write_matrix(fout, ms))) != E_OK){printf("fallo write"); return e;}
        return E_OK;
    } else if (strcmp(op,"mult") == 0) {
        if ((e = (read_matrix(f1, &ma))) != E_OK) return e;
        if ((e = (read_matrix(f2, &mb))) != E_OK) return e;
        if ((e = (mult(ma, mb, &ms))) != E_OK) return e;
        FILE *f3 = fopen(archS,"w");
        if ((e = (write_matrix(f3, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op, "idty") == 0){ 
        if ((e = (read_matrix(f1, &ma))) != E_OK) return e; 
        if ((e = (idty_matrix(get_cols(ma)+1,&ms))) != E_OK) return e;
        FILE *fout = fopen(archS,"w");
        if ((e = (write_matrix(fout, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op,"null") == 0) {
        if ((e = (read_matrix(f1, &ma))) != E_OK) return e; 
        if ((e = (null_matrix(get_cols(ma),&ms))) != E_OK) return e;
        FILE *fout = fopen(archS,"w");
        if ((e = (write_matrix(fout, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op,"cmp") == 0){
        if ((e = (read_matrix(f1, &ma))) != E_OK) return e;
        if ((e = (read_matrix(f2, &mb))) != E_OK) return e;
        int n = cmp_matrix(ma, mb);
        if ((e = (create_and_fill_matrix(1, 1, n, &ms))) != E_OK) return e;
        FILE *f3 = fopen(archS,"w");     
        if ( (e = (write_matrix(f3, ms))) != E_OK) return e;
        return E_OK;
    } else { 
        printf("Se a introducido mal alguna orden porfavor ingrese de nuevo");
    } return E_FORMAT_ERROR;
}

/*
● --calc archivo1 op​ archivo2 = archivo_salida
○ Donde ​ op​ puede ser:
■ +​ equivale a ​ sum
■ *​ equivale a ​ mult
● --calc archivo1 .* scalar = archivo_salida
○ Donde “​ scalar” es un número en punto flotante, esta operación equivale a
mult_scalar​
.
● --calc archivo1 id = archivo_salida
○ id​ equivale a ​ ”idty”
*/

// controlar que respeta el formato
error_t calcular_(char *argv[]){
    char  *ope, *archS;
    double scal;

    FILE *f1, *f2;

    if (strcmp(argv[3],"+")== 0) {
        ope = "sum";
        f1 = fopen(argv[2],"r");
        if (f1 == NULL){
            printf("Direccion de archivo invalido\n");
            return E_READ_ERROR;
        } 
        f2 = fopen(argv[4],"r");
        if (f2 == NULL){
            printf("Direccion de archivo invalido\n");
            return E_READ_ERROR;
        } 
        archS = argv[6];
    } else if (strcmp(argv[3],"*")== 0){
        ope = "mult";
        f1 = fopen(argv[2],"r");
        if (f1 == NULL){
            printf("Direccion de archivo invalido\n");
            return E_READ_ERROR;
        } 
        f2 = fopen(argv[4],"r");
        if (f2 == NULL){
            printf("Direccion de archivo invalido\n");
            return E_READ_ERROR;
        } 
        archS = argv[6];        
    } else if (strcmp(argv[3],".*") == 0) { //no se como escapar el asterisco
        ope = "mult_scalar";
        f1 = fopen(argv[2], "r");
        if (f1 == NULL){
            printf("Direccion de archivo invalido\n");
            return E_READ_ERROR;
        } 
        int ret = sscanf(argv[4], "%lf", &scal);
        archS = argv[6];       
    } else if (strcmp(argv[3],"id")== 0) {
        ope = "idty";
        f1 = fopen(argv[2],"r");
        if (f1 == NULL){
            printf("Direccion de archivo invalido\n");
            return E_READ_ERROR;
        } 
        archS = argv[5];
    } else printf("Se a introducido mal alguna orden porfavor ingrese de nuevo");
    
    return procesar_funciones(f1, f2, archS, ope, scal);

    
}


int main(int argc, char *argv[]){
    
    char *operador;
/*
    ejemplo de formato
     -1 nom_arch -2 nom_arch -p operacion -out nom_arch

     -1 nom_arch -s numero -p multi_scalar -out nom arch

     -1 nom_arch -s numero (hay que convertirlo a numero atoi ostrtol)

     si llega --help mostar solo lista de comandos y termina el programa?
*/
    if(argc >= 2){
        
        if (strcmp(argv[1],"--calc") == 0) {
            if (argc >= 6 && argc <= 7 ) return calcular_(argv);// no controlado los parametros
            else printf("el formato es erroneo");
            return 0;
        }
        FILE *f1, *f2;
        char *ope, *archS;
        double scal;

        for(int i= 1; i < argc; ++i){
            operador = argv[i];  // ahora guarde un comando, se queda con la direccion del primer caracter
            printf("%s\n", operador);
            if (strcmp(operador,"--in1") == 0 || (strcmp(operador,"-1")== 0)){
                // valida si hay un file antes de pasar a procesar funciones
                f1 = fopen(argv[++i],"r");
                if (f1 == NULL){
                    printf("Direccion de archivo invalido\n");
                    return E_READ_ERROR;
                } 
            } else if ((strcmp(operador,"--in2")== 0 || (strcmp(operador,"-2") == 0))){
                // valida si hay un file antes de pasar a procesar funciones
                f2 = fopen(argv[++i],"r");
                if (f2 == NULL){
                    printf("Direccion de archivo invalido\n");
                    return E_READ_ERROR;
                } 
            } else if ((strcmp(operador,"--out") == 0 || (strcmp(operador,"-o")== 0))){
                archS = argv[++i];                
            } else if ((strcmp(operador,"--scalar") == 0 || (strcmp(operador,"-s")== 0))){
                int ret = sscanf(argv[++i], "%lf", &scal);
            } else if ((strcmp(operador, "--op") == 0 || (strcmp(operador, "-p")== 0))){
                  ope = argv[++i];
            } else if (!(strcmp(operador, "--help"))){
                printf("--in1|-1 nombre_archivo\n");
                printf("--in2|-2 nombre_archivo\n");
                printf("--out|-o nombre_archivo\n");
                printf("--scalar|-s número\n");
                printf("--op|-p (dup|sum|mult_scalar|mult|idty|null|cmp)\n");
                return 0;
            } else {printf("Se a introducido mal algun argumento para mas informacion --help\n"); return 0;}
        }
        procesar_funciones(f1, f2, archS, ope, scal);
    } else {
        printf("argumentos insuficientes");
        return E_FORMAT_ERROR;

}return E_OK;

}


