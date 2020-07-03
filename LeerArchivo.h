#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#define MAX_LENGTH 4096

typedef void (* t_matrix_file_handler_by_type)(FILE *);
enum matrix_file_handler_type{ m1, m2 };
const char * matrix_file_handler_codes[] = { "m1", "m2", NULL };

typedef struct {
  unsigned long int rows;
  unsigned long int columns;
} t_matrix_file_handler_dimensions;

void my_debug(const char *msg, ...);

void matrix_file_handler_manage_error(const char *msg, ...);

char * matrix_file_handler_read_line(char * buffer, size_t size, FILE * f);

int matrix_file_handler_is_comment(const char * line);

int matrix_file_handler_read_header(FILE *f);

t_matrix_file_handler_dimensions matrix_file_handler_m1_dimensions(FILE *f);

void matrix_file_handler_by_type_m1(FILE *f);

void matrix_file_handler_from_filename(const char * file);
