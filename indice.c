/*matrix.h, list.h, matrix.c, lista.c*/
//index.c

#include <stdio.h>
#include "list.h"
#include "mat.h"
#include <stdlib.h>
#include <string.h>
#include "LeerArchivo.h"


void procesar_funciones(char *arch1, char *arch2, char *archS, char *op, int scalar = 0){
    matrix_t *ma, *mb, ms;

    switch (ope) {
        case 'dup' : 
            /*leer la matriz
            dup_matr que recibe una matriz y devuelveotra matriz
            escribo la matriz (devolviendola en un file) */
            FILE *f = fopen(&arch1,'r');
            if ( e = (read_matrix(&f, *ma)) != E_OK) return e;
            if (e = (dup_matrix(*ma, &ms)) != E_OK) return e;
            FILE *f2 = fopen(&archS,'w');
            if (e = (write_matrix(&archS, *ms)) != E_OK) return e;
            return E_OK;
        case 'sum' :
            FILE *f1 = fopen(&arch1,'r');
            FILE *f2 = fopen(&arch2,'r');
            if (e = (read_matrix(&f1, *ma)) != E_OK) return e;
            if (e = (read_matrix(&f2, *mb)) != E_OK) return e;
            if (e = (sum(*ma, *mb, &ms)) != E_OK) return e;
            FILE *f3 = fopen(&archS,'w');
            if (e = (write_matrix(&archS, *ms)) != E_OK) return e;
            return E_OK;
        break;
        case 'mult_scalar' :
            FILE *f1 = fopen(&arch1,'w');
            if (e = (read_matrix(&f1, *ma)) != E_OK) return e;
            if (e = (mult_scalar(scal, *ma, *ms)) != E_OK) return e;       
            FILE *f2 = fopen(&archS,'w');
            if (e = (write_matrix(&archS, *ms)) != E_OK) return e;
            return E_OK;
        break;
        case 'mult' :
            FILE *f1 = fopen(&arch1,'r');
            FILE *f2 = fopen(&arch2,'r');
            if (e = (read_matrix(&f1, *ma)) != E_OK) return e;
            if (e = (read_matrix(&f2, *mb)) != E_OK) return e;
            if (e = mult(*ma, *mb, &ms)) != E_OK) return e;
            FILE *f3 = fopen(&archS,'w');
            if (e = (write_matrix(&archS, *ms)) != E_OK) return e;
            return E_OK;
        break;
        case 'idty' :
            FILE *f1 = fopen(&arh1, 'r');
            if (e = (read_matrix(&f1, *ma)) != E_OK) return e; 
            if (e = (idty_matrix(get_cols(*ma),&ms)) != E_OK) return e;
            FILE *f2 = fopen(&archS,'w');
            if (e = (write_matrix(&archS, *ms)) != E_OK) return e;
            return E_OK;
        break;
        case 'null' :
            FILE *f1 = fopen(&arh1, 'r');
            if (e = (read_matrix(&f1, *ma)) != E_OK) return e; 
            if (e = (null_matrix(get_cols(*ma),&ms)) != E_OK) return e;
            FILE *f2 = fopen(&archS,'w');
            if (e = (write_matrix(&archS, *ms)) != E_OK) return e;
            return E_OK;
        break;
            case 'cmp' :
            FILE *f1 = fopen(&arch1,'r')
            FILE *f2 = fopen(&archS,'r');
            if (e = (read_matrix(&f1, *ma)) != E_OK) return e;
            if (e = (read_matrix(&f2, *mb)) != E_OK) return e;
            int n = cmp_matrix(*ma, *mb);
            if (e = (create_and_fill_matrix(1, 1, n, &ms)) != E_OK) return e;     
            if ( e = (write_matrix(&archS, *ms)) != E_OK) return e;
            return E_OK;
        break;
        default: return E_FORMAT_ERROR;
    }
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
void calcular_(){
    char *arch1, *arch2, *ope, *archS;
    double scal;

    if (argv[3] == "+") {
        ope = "sum";
        arch1 = argv[2]; 
        arch2 = argv[4];
        archS = rgv[6];
    } else if (argv[3] == "*"){
        ope = "mult";
        arch1 = argv[2]; 
        arch2 = argv[4];
        archS = rgv[6];        
    } else if (argv[3] == ".*") {
        ope = "mult_scalar";
        arch1 = argv[2];
        scal = argv[4];
        archS = argv[6];       
    } else if (argv[3] == "id") {
        ope = "idty_matrix";
        arch1 = argv[2];
        archS = argv[5];
    } else
        printf("Se a introducido mal alguna orden porfavor ingrese de nuevo");
    }

    procesar_funciones(arch1, arch2, archS, ope, scal);

    return E_OK;
    
}


int main(int argc, char *argv[]){

    double matrix1[][], matrix2[][];
    
    char *operador[];

    error_t e;

// -1 nom_arch -2 nom_arch -p operacion -out nom_arch

// -1 nom_arch -s numero -p multi_scalar -out nom arch

// -1 nom_arch -s numero (hay que convertirlo a numero atoi ostrtol)

// si llega --help mostar solo lista de comandos y termina el programa?

    if(argc >= 2){
        
        if (argv[1] == "--calc") {
            calcular_();
        }

        char *arch1, *arch2, *ope, *archS;
        double scal;

        for (i=1; i <= argc; ++i){
            operador1 = argv[i];  // ahora guarde un comando
            switch (operador1) {
                case '--in1': 
                case '-1': 
                    arch1 = argv[++i]; // validar si hay un file
                    matrix_file_handler_from_filename(&arch1);
                    break;
                case '--in2': 
                case '-2': 
                    arch2 = argv[++i];
                    matrix_file_handler_from_filename(&arch2);
                    break;
                case '--out':
                case '-o':
                    archS = argv[++i];
                    break;
                case '--scalar':
                case '-s':
                    scal = argv[++i];
                    break;
                case '--op':
                case '-p':
                    ope = argv[++i];
                    break;
                case '--help':
                        // mostrar en consola la lista de argumentos
                    return E_OK;
                default: return E_FORMAT_ERROR;
            }
        }
        procesar_funciones(*arch1, *arch2, *archS, *op, scalar);
    } else {
        return E_FORMAT_ERROR;

}return E_OK;

  /*	matrix1, matrix2
    archSalida, operacion


  read_matrix(arch1, &matrix1);
  chequear la cantidad de elementos (suponiendo que los argumentos vienen el el orden correcto)
  
    si -1 almaceno el nombre del archivo y llamo a reed matrix 
 		si -2 llamo a matrix de nuevo
    si -o se guard el nombre del archivo con el resultado
    si -s tomar N y mandar a la func escalar -1 y el N
		si -p operacion  
      case()
*/
}


/*  


test.m1

M1
## esto es un comentario
# va a a ser una matriz de 2x 3
2 3
1,2 1,3 1,4
2,3 4,4 4,5 
*/