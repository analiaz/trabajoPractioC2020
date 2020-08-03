#include "error-mat.h"

int output_error(FILE *fp, error_t e)
{
  switch (e)
    {
  case E_OK:
    return fprintf(fp, "NO hay error (OK)");
  case E_READ_ERROR:
    return fprintf(fp, "Error de lectura (READ)");
  case E_FORMAT_ERROR:
    return fprintf(fp, "Error de formato (FORMAT)");
  case E_ALLOC_ERROR:
    return fprintf(fp, "Error de memoria (ALLOC)");
  case E_SIZE_ERROR:
    return fprintf(fp, "Error de dimension (SIZE)");
  case E_WRITE_ERROR:
    return fprintf(fp, "Error de escritura (WRITE)");
  case E_NOTIMPL_ERROR:
    return fprintf(fp, "No implmenetado aun (NOTIMPL)");
  case E_FILE_ERROR:
    return fprintf(fp, "Error de archivo (FILE)");    
  case ERROR_INCOMPATIBLE_MATRICES:
    return fprintf(fp, "Error de tamaño en matrices (SUM o MULT");
  default:
    return fprintf(fp, "Error desconocido (UNKNOWN)");
    }
}

/*** EOF ***/
