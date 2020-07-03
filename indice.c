/*matrix.h, list.h, matrix.c, lista.c*/
//index.c

#include <stdio.h>
#include "matrix.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "LeerArchivo.h"

typedef int error_t;
#define 	E_OK    	 0
#define	    E_READ_ERROR 1
#define   E_FORMAT_ERROR 2
#define   E_ALLOC_ERROR  3
#define   E_SIZE_ERROR   4
#define   E_WRITE_ERROR  5

int main(int argc, char *argv[]){

    double matrix1[][], matrix2[][];
    
    char *operador[];


// -1 nom_arch -2 nom_arch -p operacion -out nom_arch

// -1 nom_arch -s numero -p multi_scalar -out nom arch

// -1 nom_arch -s numero (hay que convertirlo a numero atoi ostrtol)

// si llega --help mostar solo lista de comandos y termina el programa?
    if(argc >= 2){
        char arch1, arch2, ope, salida, archS;
        double scal;
        
        for (i=1; i <= argc; ++i){
            operador1 = argv[i]  // hay un comando
            switch (operador1) {
                case '--in1': 
                case '-1': 
                    arch1 = argv[++i]; // validar si hay un file
                    break;
                case '--in2': 
                case '-2': 
                    arch2 = argv[++i];
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

        switch (ope) {
            case 'dup' : 
                /*leer la matriz
                dup_matr que recibe una matriz y devuelveotra matriz
                escribo la matriz (devolviendola en un file) */
            break;
            case 'sum' :
            break;
            case 'mult_scalar' :
            break;
            case 'mult' :
            break;
            case 'idty' :
            break;
            case 'null' :
            break;
            case 'cmp' :
            break;
        default: return E_FORMAT_ERROR;
        }

    } else {
        return E_FORMAT_ERROR;
    }

    return E_OK;
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