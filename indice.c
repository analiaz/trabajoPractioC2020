/*matrix.h, list.h, matrix.c, lista.c*/
//index.c

#include <stdio.h>
#include "list/list.h"
#include "mat.h"
#include <stdlib.h>
#include <string.h>
#include "LeerArchivo.h"
#include "error-mat.h"

static int test (char *fp, double SCALAR){
  
  matrix_t   ma;
  matrix_t  *mb;
  matrix_t  *mc;
  matrix_t  *md;
  matrix_t  *me;
  matrix_t  *mf;  
  matrix_t  *m0;
  matrix_t  *m1;  
  matrix_t  *maux1, *maux2; 
  FILE       *fpout = stdout;
  error_t    e;
  
  FILE *f = fopen(fp,"r");
  if ( (e = read_matrix(f, &ma)) == E_OK )
    {
      fprintf(stderr,"ma=\n"); write_matrix(fpout, &ma);
      fprintf(stderr,"-----------------\n");
      dup_matrix(&ma,&mb);
      fprintf(stderr,"mb=\n"); write_matrix(fpout, mb);
      fprintf(stderr,"-----------------\n");

        // Conmutativa 
        // A + B = C
        sum(&ma,mb,&mc);
        // B + A = D
        sum(mb,&ma,&md);
        // C == D , D == C
        fprintf(stderr,"ma + mb == mb + ma :%d %d\n",cmp_matrix(mc,md), cmp_matrix(md,mc));
        fprintf(stderr,"mc=\n"); write_matrix(fpout, mc);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"md=\n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        free_matrix(&mc);  
        free_matrix(&md);

        // Asociativa
        // A + (B + C) = D
        dup_matrix(&ma,&mc);
        sum(mb,mc,&maux1);
        sum(&ma,maux1,&md);

        // (A + B) + C = E
        free_matrix(&maux1);
        sum(&ma,mb,&maux1); 
        sum(maux1,mc,&me);
        // D == E , E == D
        fprintf(stderr,"ma + (mb + mc) == (ma + mb) + mc :%d %d\n",cmp_matrix(md,me), cmp_matrix(me,md));
        fprintf(stderr,"md=\n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"me=\n"); write_matrix(fpout, me);
        fprintf(stderr,"-----------------\n");
        free_matrix(&md);
        free_matrix(&me);
        free_matrix(&maux1);  

        // Elemento neutro
        // A + 0 = D
        null_matrix(get_cols(&ma),&m0);
        fprintf(stderr,"m0=\n"); write_matrix(fpout, m0);
        fprintf(stderr,"-----------------\n");  
        sum(&ma, m0, &md);
        // A == D == A
        fprintf(stderr,"(ma + m0) = ma :%d %d\n",cmp_matrix(&ma,md), cmp_matrix(md,&ma) );
        fprintf(stderr,"md=\n"); write_matrix(fpout, md);  
        fprintf(stderr,"-----------------\n"); 
        free_matrix(&md);

        //Inverso Aditivo
        // A + -A = 0
        mult_scalar(-1, &ma, &md);
        fprintf(stderr,"-ma=\n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        // D = A + -A
        printf("(%d)\n",sum_inplace(&ma, md));
        //printf("(%d)\n",sum(&ma, md, &me));  
        fprintf(stderr,"(ma + -ma) = 0 :%d %d\n",cmp_matrix(m0,md), cmp_matrix(md,m0) );
        fprintf(stderr,"md=\n"); write_matrix(fpout, md);
        //fprintf(stderr,"me=\n"); write_matrix(fpout, me);  
        fprintf(stderr,"-----------------\n");
        free_matrix(&md);
        //free_matrix(&me);

        //////////// MULT  SCALAR
        // A + B = F
        sum(&ma,mb,&mf);
        // c * F = c * (A + B) = F
        mult_scalar_inplace(SCALAR, mf);
        fprintf(stderr,"%f * mf=\n",SCALAR); write_matrix(fpout, mf);
        fprintf(stderr,"-----------------\n");

        // D = c * A
        mult_scalar(SCALAR, &ma, &md);
        // E = c * B  
        mult_scalar(SCALAR, mb, &me);
        // E = D + E = c * A + c * B 
        sum_inplace(md,me);
        fprintf(stderr,"%f * ma +  %f * mb =\n",SCALAR,SCALAR); write_matrix(fpout, me);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"%f * (ma + mb) = %f * ma + %f * mb :%d %d\n",SCALAR,SCALAR,SCALAR,cmp_matrix(mf,me), cmp_matrix(me,mf) );
        free_matrix(&md);
        free_matrix(&me);
        free_matrix(&mf);  

        // Identidad Multiplicativa
        // D = A * I
        idty_matrix(get_cols(&ma),&m1);  
        mult(&ma, m1, &md);
        // E = I * A
        mult(m1, &ma, &me);
        fprintf(stderr,"ma * m1 \n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"(ma * m1) = (m1 * ma) = ma :%d %d %d\n",cmp_matrix(&ma,md), cmp_matrix(md,&ma), cmp_matrix(md,me));
        free_matrix(&md);
        free_matrix(&me);

        // Nulo Multiplicativo
        // D = A * 0 
        //null_matrix(get_cols(&ma),&m0);  
        mult(&ma, m0, &md);
        // E = 0 * A
        mult(m0, &ma, &me);
        fprintf(stderr,"md = \n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"(ma * m0) = (m0 * ma) = ma :%d %d\n",cmp_matrix(me,md), cmp_matrix(md,me));
        free_matrix(&md);
        free_matrix(&me);

        // Nulo Multiplicativo escalar
        // D = esc(0) * A  = 0
        mult_scalar(0.0, &ma, &md);
        fprintf(stderr,"md = \n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"(0 * ma) = m0 :%d %d\n",cmp_matrix(md,m0), cmp_matrix(md,m0));
        fprintf(stderr,"-----------------\n");
        free_matrix(&md);

        // Asociativa de la mult
        // A * (B * C) = D  
        mult(mb,mc,&maux1);
        mult(&ma,maux1,&md);

        // (A * B) * C = E
        free_matrix(&maux1);
        mult(&ma,mb,&maux1); 
        mult(maux1,mc,&me);

        // D == E , E == D
        fprintf(stderr,"ma * (mb * mc) == (ma * mb) * mc :%d %d\n",cmp_matrix(md,me), cmp_matrix(me,md));
        fprintf(stderr,"md=\n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"me=\n"); write_matrix(fpout, me);
        fprintf(stderr,"-----------------\n");
        free_matrix(&md);
        free_matrix(&me);
        free_matrix(&maux1);  

        // Dist de la mult con respecto a la suma
        // A * (B + C) = D  
        sum(mb,mc,&maux1);
        mult(&ma,maux1,&md);

        // (A * B)  + (A * C)  = E
        // E = E + F
        free_matrix(&maux1);
        mult(&ma,mb,&maux1); 
        mult(&ma,mc,&maux2);
        sum(maux1,maux2,&me);  

        // D == E , E == D
        fprintf(stderr,"ma * (mb + mc) == (ma * mb) + (ma * nc) :%d %d\n",cmp_matrix(md,me), cmp_matrix(me,md));
        fprintf(stderr,"md=\n"); write_matrix(fpout, md);
        fprintf(stderr,"-----------------\n");
        fprintf(stderr,"me=\n"); write_matrix(fpout, me);
        fprintf(stderr,"-----------------\n");
        free_matrix(&md);
        free_matrix(&me);
        free_matrix(&maux1);  
        free_matrix(&maux2);  

        return 0;
    } else {   
        output_error(stderr, e);      
        return -1;
    }
}



error_t procesar_funciones(char *arch1, char *arch2, char *archS, char *op, T_TYPE scalar){
    matrix_t *ma = NULL, *mb = NULL, *ms = NULL;
    error_t e;
    // TEST if (strcmp(string, "B1") == 0)  {   // do something }  else if (strcmp(string, "xxx") == 0) {   // do something else } /* more else if clauses */ else /* default: */ { }
    if (strcmp(op,"dup") == 0){ 
        /*leer la matriz
        dup_matr que recibe una matriz y devuelveotra matriz
        escribo la matriz (devolviendola en un file) */
        FILE *f = fopen(arch1,"r");
        if ( (e = (read_matrix(f, ma))) != E_OK) return e;
        if ( (e = (dup_matrix(ma, &ms))) != E_OK) return e;
        FILE *f2 = fopen(archS,"w");
        if ( (e = (write_matrix(f2, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op,"sum") == 0) {
        FILE *f1 = fopen(arch1,"r");
        FILE *f2 = fopen(arch2,"r");
        if ((e = (read_matrix(f1, ma))) != E_OK) return e;
        if ((e = (read_matrix(f2, mb))) != E_OK) return e;
        if ((e = (sum(ma, mb, &ms))) != E_OK) return e;
        FILE *f3 = fopen(archS,"w");
        if ((e = (write_matrix(f3, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op, "mult_scalar") == 0){
        FILE *f1 = fopen(arch1,"w");
        if ((e = (read_matrix(f1, ma))) != E_OK) return e;
        if ((e = (mult_scalar(scalar, ma, &ms))) != E_OK) return e;       
        FILE *f2 = fopen(archS,"w");
        if ((e = (write_matrix(f2, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op,"mult") == 0) {
        FILE *f1 = fopen(arch1,"r");
        FILE *f2 = fopen(arch2,"r");
        if ((e = (read_matrix(f1, ma))) != E_OK) return e;
        if ((e = (read_matrix(f2, mb))) != E_OK) return e;
        if ((e = (mult(ma, mb, &ms))) != E_OK) return e;
        FILE *f3 = fopen(archS,"w");
        if ((e = (write_matrix(f3, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op, "idty") == 0){ 
        FILE *f1 = fopen(arch1, "r");
        if ((e = (read_matrix(f1, ma))) != E_OK) return e; 
        if ((e = (idty_matrix(get_cols(ma),&ms))) != E_OK) return e;
        FILE *f2 = fopen(archS,"w");
        if ((e = (write_matrix(f2, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op,"null") == 0) {
        FILE *f1 = fopen(arch1, "r");
        if ((e = (read_matrix(f1, ma))) != E_OK) return e; 
        if ((e = (null_matrix(get_cols(ma),&ms))) != E_OK) return e;
        FILE *f2 = fopen(archS,"w");
        if ((e = (write_matrix(f2, ms))) != E_OK) return e;
        return E_OK;
    } else if (strcmp(op,"cmp") == 0){
        FILE *f1 = fopen(arch1,"r");
        FILE *f2 = fopen(archS,"r");
        if ((e = (read_matrix(f1, ma))) != E_OK) return e;
        if ((e = (read_matrix(f2, mb))) != E_OK) return e;
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
error_t calcular_(char *argv[]){
    char *arch1, *arch2, *ope, *archS;
    double scal;

    if (strcmp(argv[3],"+")== 0) {
        ope = "sum";
        arch1 = argv[2]; 
        arch2 = argv[4];
        archS = argv[6];
    } else if (strcmp(argv[3],"*")== 0){
        ope = "mult";
        arch1 = argv[2]; 
        arch2 = argv[4];
        archS = argv[6];        
    } else if (strcmp(argv[3],".*") == 0) {
        ope = "mult_scalar";
        arch1 = argv[2];
        scal = atof(argv[4]); //ascci a doble
        archS = argv[6];       
    } else if (strcmp(argv[3],"id")== 0) {
        ope = "idty_matrix";
        arch1 = argv[2];
        archS = argv[5];
    } else printf("Se a introducido mal alguna orden porfavor ingrese de nuevo");
    
    return procesar_funciones(arch1, arch2, archS, ope, scal);

    
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
            return calcular_(argv);
        }

        char *arch1, *arch2, *ope, *archS;
        double scal;

        for(int i= 1; i <= argc; ++i){
            operador = argv[i];  // ahora guarde un comando
            if (strcmp(operador,"--in1") == 0 || (strcmp(operador,"-1")== 0)){
                arch1 = argv[++i]; // validar si hay un file
                matrix_file_handler_from_filename(arch1);
            } else if ((strcmp(operador,"--in2")== 0 || (strcmp(operador,"-2") == 0))){
                arch2 = argv[++i];
                matrix_file_handler_from_filename(arch2);
            } else if ((strcmp(operador,"--out") == 0 || (strcmp(operador,"-o")== 0))){
                archS = argv[++i];                
            } else if ((strcmp(operador,"--scalar") == 0 || (strcmp(operador,"-s")== 0))){
                scal = atof(argv[++i]);
            } else if ((strcmp(operador, "--op") == 0 || (strcmp(operador, "p")== 0))){
                  ope = argv[++i];
            } else if ((strcmp(operador, "--help"))){
                printf("--in1|-1 nombre_archivo");
                printf("--in2|-2 nombre_archivo");
                printf("--out|-o nombre_archivo");
                printf("--scalar|-s número");
                printf("--op|-p (dup|sum|mult_scalar|mult|idty|null|cmp)");
            } else printf("Se a introducido mal algun argumento para mas informacion --help");
        }
        test(arch1,scal);
        procesar_funciones(arch1, arch2, archS, ope, scal);
    } else {
        printf("argumentos insuficientes ");
        return E_FORMAT_ERROR;

}return E_OK;

}


