include "LeerArchivo.h"

void my_debug(const char *msg, ...) {
#ifdef MY_DEBUG
  va_list ap;
  printf(">>>>>>DEBUG\n");
  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);
  printf(">>>>>>END DEBUG\n");
#endif
}


void matrix_file_handler_manage_error(const char *msg, ...) {
  va_list ap;
  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}

char * matrix_file_handler_read_line(char * buffer, size_t size, FILE * f) {
   char * aux = fgets(buffer, MAX_LENGTH, f);
   if (aux) {
     if (strlen(aux)>0) aux[strlen(aux) - 1]=0;
   }
   return aux;
}

int matrix_file_handler_is_comment(const char * line) {
  return strlen(line) >0 && line[0] == '#';
}

int matrix_file_handler_read_header(FILE *f) {
char buffer[MAX_LENGTH];
  while (1) {
    if (matrix_file_handler_read_line(buffer, MAX_LENGTH, f)){
      if (!matrix_file_handler_is_comment(buffer)) {
        int i;
        for(i=0; matrix_file_handler_codes[i];i++) {
          if(!strcasecmp(buffer, matrix_file_handler_codes[i])) {
            return i;
          }
        }
        matrix_file_handler_manage_error("El codigo del archivo no es valido. Se esperaba M1 o M2, se recibe %s\n", buffer);
      }
    }else matrix_file_handler_manage_error("Se alcanzó el fin de archivo sin un codigo M1 o M2\n");
  }
}

t_matrix_file_handler_dimensions matrix_file_handler_m1_dimensions(FILE *f) {
  t_matrix_file_handler_dimensions d;
  char buffer[MAX_LENGTH];
  while (1) {
    if (matrix_file_handler_read_line(buffer, MAX_LENGTH, f)){
      if (!matrix_file_handler_is_comment(buffer)) {
        int ret = sscanf(buffer, "%ld %ld", &d.rows, &d.columns);
        if (ret !=2) matrix_file_handler_manage_error("Error leyendo la dimension. Se esperaban dos enteros, se recibió %s\n", buffer);
        return d;
      }
    }else matrix_file_handler_manage_error("Se alcanzó el fin de archivo sin encontrar las dimensiones\n");
  }
}

void matrix_file_handler_by_type_m1(FILE *f) {
  t_matrix_file_handler_dimensions d = matrix_file_handler_m1_dimensions(f);
  my_debug("La matriz tiene %d filas por %d columnas\n", d.rows, d.columns);
}

void matrix_file_handler_from_filename(const char * file){
  FILE * f;
  int header_type;
  t_matrix_file_handler_by_type matrix_file_handler_by_type[] = { matrix_file_handler_by_type_m1, NULL};
  if (!(f=fopen(file,"rb"))) {
      fprintf(stderr, "No hemos podido abrir el archivo %s: %s\n", file, strerror(errno));
      exit(EXIT_FAILURE);
  }
  header_type = matrix_file_handler_read_header(f);
  my_debug("El tipo del archivo es %d\n", header_type);
  matrix_file_handler_by_type[header_type](f);
  fclose(f);
}