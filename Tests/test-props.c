/***
 *   
 * FILE NAME:   test-props.c
 *
 * PURPOSE:     
 *
 * Programa de referencia de uso de biblioteca de matrices.           
 *
 * FILE REFERENCES:        
 *
 *            Name               I/O       Description             
 *            ----               ---       -----------
 * @file      <fname>            <i|o|io>  <fdesc>
 * 
 * EXTERNAL REFERENCES:
 *
 *            Name               I/O       Description             
 *            ----               ---       -----------
 * @external  <eref>             <i|o|io>  <edesc> 
 *
 * MAIN: 
 *
 * $Author:   user$ email@domain
 *
 * $Revision: 1.1$
 *
 * $Date:     DD/MM/YYYY$
 *
 * REQUIREMENTS/FUNCTIONAL SPECIFICATIONS:
 *
 * <freqs>
 *
 * NOTES:
 *
 * <notes>
 *
 * DEVELOPMENT HISTORY:
 *
 * Date        Author     Revision    Release   Description  
 * ----        ------     --------    -------   -----------
 * DD/MM/YYYY  user          0.1       -      Start
 *
 *	                                   
 */

#include <stdio.h>                      /* printf */
#include <stdlib.h>                     /* exit */
#include <getopt.h>                     /* getopt */
#include <stdbool.h>                    /* Booleans */
#include <mat.h>
#include <error-mat.h>
#include <list.h>

extern char *optarg;
extern int  opterr;
//extern int optind, opterr, optopt;

// Please, complete me
#define OP_ARG_1          '1'
#define OP_ARG_1_LONG     "in1"

#define OP_ARG_2          '2'
#define OP_ARG_2_LONG     "in2"

#define OP_ARG_O          'o'
#define OP_ARG_O_LONG     "out"

#define OP_ARG_S          's'
#define OP_ARG_S_LONG     "scalar"

#define OP_ARG_OPS        'p'
#define OP_ARG_OPS_LONG   "op"

#define OP_HLP            'h'
#define OP_HLP_LONG       "help"

#define SCALAR (0.5)

// Please, complete me
#define OPTION_STRING "1:h"

// Please, complete me
static struct option long_options[] = 
              {
              {OP_ARG_1_LONG  , required_argument, 0, (int) OP_ARG_1 },
	      {OP_HLP_LONG,     no_argument,       0, (int) OP_HLP },
              {0, 0, 0, 0}
              };

static void usage(char *argv[], int code)
{
  // PROGRAMA --in1 file1.txt --in2 file2.txt -o salida.txt --op sum ...
  // Please, complete me.
  //printf("usage: %s {{--in1|-1} <in-file1>} {{--in2|-2} <in-file2>} {{--out|-o} <out-file>} {--op|-p} ... \n",argv[0]);
  printf("usage: %s {{--in1|-1} <in-file1>} ... \n",argv[0]);
 exit(code);
}

/***
 * Parse Common arguments
 */
static int parse_args(/*@ in @*/  int  argc, 
	 	      /*@ in @*/  char *argv[],
		      /*@ out @*/ char **arg_1,
		      /*@ out @*/ char **arg_2,
		      /*@ out @*/ char **arg_o)
{
     int  res;
     int arg_1_count  = 0;
     /***
     int arg_2_count  = 0;
     int arg_o_count  = 0;
     ***/
     
     opterr = 0; // Supress getopt errors
     *arg_1      = NULL; 
     *arg_2      = NULL;
     *arg_o      = NULL;     
          
     while ( (res = getopt_long(argc, argv, OPTION_STRING, long_options, NULL)) != -1 )
     //while ( (res = getopt(argc, argv, OPTION_STRING)) != -1 )
     {
      if  (res == (int) OP_ARG_1)
	{
          // Take care, RO
	  *arg_1 = optarg;
          arg_1_count++; 
	}
      else if  (res == (int) OP_HLP)
	{
	  return (int) false;
	}
      else 
	{ 
          // Invalid Option, res ==  '?' 
	  return (int) false;
	}
     }
     /***
     if ((arg_1_count>1) || (arg_2_count>1) || (flag_c_count>1))
       {
	 return (int) false;	  
       }
     ***/
     return (int) ( (*arg_1 != NULL) && (arg_1_count == 1) );
}



static int test_props(FILE *fp)
{

  matrix_t   ma;
  matrix_t  *mb;
  matrix_t  *mc;
  matrix_t  *md;
  matrix_t  *me;
  matrix_t  *mf;  
  matrix_t  *m0;
  matrix_t  *m1;  
  matrix_t  *maux1, *maux2; 
  double     f;
  list_t     l;
  FILE       *fpout = stdout;
  error_t    e;
  
  if ( (e = read_matrix(fp, &ma)) == E_OK )
    {
      fprintf(stderr,"ma=\n"); write_matrix(fpout, &ma);
      fprintf(stderr,"-----------------\n");
      dup_matrix(&ma,&mb);
      fprintf(stderr,"mb=\n"); write_matrix(fpout, mb);
      fprintf(stderr,"-----------------\n");
        
  //////////// SUM 

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

  // List test
  create_and_fill_matrix(get_rows(&ma), get_cols(&ma), 3.0, &md);
  set_elem_matrix(3,3,1000.0,&md);
  set_elem_matrix(5,5,2000.0,&md);
  set_elem_matrix(6,6,2000.0,&md);    
  write_matrix(fpout, md);
  printf("-------------\n");
  for(int i=0;i<get_rows(md);i++)
    {
      for(int j=0;j<get_cols(md);j++)
	{
	  get_elem_matrix(i,j,&f,md);
	  printf("%f ",f);
	}
      printf("\n");
    }
  printf("-------------\n");
  l = ls_create();
  matrix2list(md, &l);
  ls_to_file(fpout, l);
  printf("\n-------------\n");
  ls_free(&l);
  free_matrix(&md);
  clear_matrix(&ma);
  write_matrix(fpout, &ma);
  free_matrix(&mb);
  free_matrix(&mc);
  free_matrix(&m0);
  free_matrix(&m1);  
  return 0;
    }
  else
    {
      output_error(stderr, e);      
      return -1;
    }
}


int main(int argc, char *argv[])
{
 char *arg_1;
 FILE *fp1;
 char *arg_2; // Not used
 char *arg_o; // Not used 

 if (!parse_args(argc, argv, &arg_1, &arg_2, &arg_o))
  {
    usage(argv, EXIT_FAILURE);
  }

 // Open file
 if (! (fp1 = fopen(arg_1,"r")) )
   {
     output_error(stderr, E_FILE_ERROR);
     perror(" ");
     exit(E_FILE_ERROR);  
   }

 // Should we check return value? 
 test_props(fp1);

 fclose(fp1); 
 return (0);
}

