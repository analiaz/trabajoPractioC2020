#include <stdio.h>
#include <stdlib.h>

static void usage(char *argv[], int code)
{
  printf("usage: %s <in-file1> <out-file> ... \n",argv[0]);
 exit(code);
}


int main(int argc, char *argv[])
{
 char *arg_1;
 FILE *fp;
 FILE *fp2; 
 //char *arg_2; // Not used
 char *arg_o;
 double dvalue;
 char   buf[1024];
 int rows,cols;
 

 if (argc < 3)
  {
    usage(argv, EXIT_FAILURE);
  }
 
 // Open file
 arg_1 = argv[1];
 arg_o = argv[2];
 
 if (! (fp = fopen(arg_1,"r")) )
   {
     perror("Error al abrir archivo de lectura");
     exit(EXIT_FAILURE);  
   }
 
 if (! (fp2 = fopen(arg_o,"w")) )
   {
     perror("Error al abrir archivo de escritura");
     exit(EXIT_FAILURE);  
   }
 
 //check the matrix header format
 buf[0] = buf[1] = 0;
 if (!fgets(buf, sizeof(buf), fp))
    {
      fprintf(stderr, "Error al leer header format\n");
      return -1;      
    }
 if (buf[0] != 'M' || (buf[1] != '1' && buf[1] != '2'))
   {
     fprintf(stderr, "Error de formato, debe ser 'M1 o M2'\n");
     return -2;
   }
 fprintf(fp2,"%c%c\n",buf[0],buf[1]);
 
 /****** 
 //Skip comments checking
 // discard_comments(fp);
 ******/
 
 //read matrix size information
 if (fscanf(fp, "%d %d", &rows, &cols) != 2) {
   fprintf(stderr, "Error en dimensiones \n");
   return -3;
 }
 fprintf(fp2, "%d %d\n",rows,cols);
 
 // Para M2 (fread((double*)&dvalue, sizeof(double), 1, fp) == sizeof(double))
 while (fscanf(fp,"%lf ",&dvalue) == 1)
   {
     fprintf(fp2, "%lf ",dvalue);
   }
 fclose(fp);
 fclose(fp2); 
 return (0);
}



