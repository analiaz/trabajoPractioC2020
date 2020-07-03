#include <stdio.h>
#include <stdlib.h>

static void usage(char *argv[], int code)
{
  printf("usage: %s <in-file1> ... \n",argv[0]);
 exit(code);
}


int main(int argc, char *argv[])
{
 char *arg_1;
 FILE *fp;
 char *arg_2; // Not used
 char *arg_o; // Not used 
 double dvalue;
 char   buf[1024];
 int rows,cols;
 

 if (argc < 2)
  {
    usage(argv, EXIT_FAILURE);
  }
 
 // Open file
 arg_1 = argv[1];

 //if ( (fp = fopen(arg_1,"r")) == NULL ) 
   if (! (fp = fopen(arg_1,"r")) )
   {
     perror("Error al abrir archivo");
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
     fprintf(stderr, "Error de formato, debe ser ('M1 o M2')\n");
     return -2;
   }

 /****** 
 //Skip comments checking
 // discard_comments(fp);
 ******/
 
 
 //read matrix size information
 if (fscanf(fp, "%d %d", &rows, &cols) != 2) {
   fprintf(stderr, "Error en dimensiones \n");
   return -3;
 }
 int i = 0;
 // (fread((T_TYPE*)&dvalue, sizeof(T_TYPE), 1, fp) == sizeof(T_TYPE))
 while (fscanf(fp,"%lf ",&dvalue) == 1)
   {
     printf("%lf ",dvalue);
     i++;
   }
 
 fclose(fp); 
 return (0);
}



