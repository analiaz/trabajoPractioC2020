#include <stdlib.h>
#include "LeerArchivo.h"
#include "mat.h"
#include <stdbool.h>  

error_t e;

// Asigna el formato a la matriz
error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  if (!m) return E_ALLOC_ERROR;
  m->fmt = fmt;
  return E_OK;      
}

// Devuelve el formato de la matriz
error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  if (!m) return E_ALLOC_ERROR;
  *fmt = m->fmt;
  return E_OK;      
}


error_t read_matrix(FILE *fp, matrix_t **m)
{
	int auxFormat = matrix_file_handler_read_header(fp); // pido el fromato de la matriz (si es 0 = formato M1)
	
  if(!auxFormat){ // Si el formato es M1
		
		t_matrix_file_handler_dimensions dim = matrix_file_handler_m1_dimensions(fp); // asigno dimesion (fila, columna) de la matriz leido desde el archivo
		*m = init_matrix(dim.rows, dim.columns); 

    if ((*m) == NULL){return E_ALLOC_ERROR;}
		set_ffmt_matrix(*m, auxFormat); 
		
    
    char * linea = malloc(1024 * sizeof(char)); // guarda para leer del archivo
		unsigned int row = 0, col = 0; // mantener una guia de en que posicion se guarda cada elemento que se leedl archivo
		char separador[] = " "; // contiene los caracteres que se utilizan como separadores de los valores que vienen en el archivo en este caso solamente "un espacio en blanco"
		
    //se usa matrix_file_handler_read_line (de LeerArchivo.h), se carga la matrix en un loop mientras archivo != EOF (que contenga algo) entra
    while(!feof(fp)){ 
			if (matrix_file_handler_read_line(linea, 0, fp)){ 
        //dentro de la funcion se encuentra fgets que devuelve lo leido del archivo, un valor asignado en linea,si hubo un error retorna NULL
				//una linea puede traer mas de un valor, entonces se separa por "separador" hasta que se lea un EOL

				char *ptr = strtok(linea, separador); // lee linea hasta encontrar separador, retornando lo que leyo y dejando en linea el resto de la cadena 
				T_TYPE value = V_NULL; // se quedara con el valos de sscanf

        bool flag = true;
				while(ptr != NULL && flag){ 
					printf("%s \n", ptr); 
					int retVal = sscanf(ptr, "%lf", &value); // se convierte el valor leido a flotante 
					printf("%lf \n", value); // testea la correcta convercion
					

					if ( (e = (set_elem_matrix(row, col, value, m))) != E_OK ) {fclose(fp); free(linea);  return e; }; // se intenta agregar elelemento a la matriz
					printf("agrego %lf a la matriz \n",value);
          if (++col == dim.columns){ // chequea si llego al final de la fila y por consiguiente si tiene que cambiar
						col = 0;
            printf("cambio de fila\n");

						if (++row == dim.rows) { flag = false;} //printf("se fue de rango\n"); fclose(fp); return E_READ_ERROR;}  // verifica que no se vaya de rango en las filas 
          }
					
					ptr = strtok(NULL, separador); // se lee otra parte de la linea hasta encontrar el separador, siendo el primer parametro null para tomar desde el punto que dejo en la vez anterior
				} 
			}
		}
    free(linea);
    fclose(fp); 
		return E_OK;
	}	
	//Si no es M1 el archivo solo se cierra el archivo y se devuelve el error de no implementacion
	else { 
    fclose(fp); 
    return E_NOTIMPL_ERROR;
  }      
}

error_t write_matrix(FILE *fp, const matrix_t *m)
{
  if (!m) {fclose(fp); return E_ALLOC_ERROR;} // se verifica que exista m

  fprintf(fp, "M%d \n## Matriz %d x %d \n",m->fmt+1 ,m->rows, m->cols); // se imprime la cabecera del archivo (formato y dimenciones)
  fprintf(fp, "%d %d \n", m->rows, m->cols ); //se imprime filas y columnas
  T_TYPE val = V_NULL;

  // se recorre lamatriz para ir copiando esta en el archivo
  for(int i = 0; i <= get_rows(m); ++i) {
    for (int j = 0; j <= get_cols(m); ++j){
      if ((e = (get_elem_matrix(i, j, &val, m))) != E_OK) {fclose(fp); return e;}
      fprintf(fp, "%f ", val);
    }
    fprintf(fp, "\n");
  }
  
	fclose(fp);      

  return E_OK;      
}

error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
  if (!m_src) return E_ALLOC_ERROR; // se verifica que exista m_src

  if (create_and_fill_matrix(get_rows(m_src) + 1, get_cols(m_src) + 1, V_NULL, m_dst)){ // se crea la matriz de destino con la fila y columna de la matriz de inicio m_src
    
    T_TYPE res = V_NULL;
    //recorro la matriz de entrada m_src y cargo en m_dst
    for (int i = 0; i <= get_rows(m_src); ++i){
      for (int j = 0; j <= get_cols(m_src); ++j){
        if((e = (get_elem_matrix(i, j, &res, m_src)) == E_OK)){ // recupera el valor de la matriz de entrada
            if( (e = (set_elem_matrix(i, j, res, m_dst))) != E_OK){ return e;} //setea el valor en la matriz de destino
        } else return e;
      }
    } return E_OK;
  } else return E_ALLOC_ERROR;
}

error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  // se verific que las matrices existan
  if (!mb) return E_ALLOC_ERROR;
  if (!ma) return E_ALLOC_ERROR;

  // para realizar la suma de matrices las dimenciones deben ser iguales
  if (check_dimetions(ma, get_rows(mb), get_cols(mb))){
  	// creo variable de contenido para llevar la suma
    T_TYPE val_ma = V_NULL;
    T_TYPE val_mb = V_NULL;
    T_TYPE res_mc = V_NULL;
    
    if (!create_and_fill_matrix(get_rows(mb) + 1, get_cols(mb) + 1, V_NULL, mc)){ // utilizo los valores de fila y columna de mb(podria haber elegido  ma) para crear mc
      // recorro ambas matrices (ma y mb) obtengo sus valores, los sumo y guardo en res_mc 
      for ( int i = 0; i <= get_rows(ma); ++i){
        for (int j = 0; j <= get_cols(ma); ++j) {
          if (!(get_elem_matrix(i, j, &val_ma, ma)) && !(get_elem_matrix(i, j, &val_mb, mb))){
              res_mc = val_ma + val_mb;
              if ((e = (set_elem_matrix(i, j, res_mc, mc))) != E_OK) return e; // se verifica que se haya seteado bien mc
          } else return E_READ_ERROR;
        }
      } return E_OK;
  	} else return E_ALLOC_ERROR;
  } else return ERROR_INCOMPATIBLE_MATRICES;
}     

error_t sum_inplace(const matrix_t *m_src, matrix_t *m_dst) // idem sum con la diferencia de que no existe una matriz resultado y lo qu se hace es pisar los valores en m_dst
{
  
  if (!m_src) return E_ALLOC_ERROR;
  if (!m_dst) return E_ALLOC_ERROR;

  if (check_dimetions(m_src, get_rows(m_dst), get_cols(m_dst) == E_OK)){
  	
    T_TYPE res_src = V_NULL;
    T_TYPE res_dst = V_NULL;
	  T_TYPE res = V_NULL;
    
    for (int i = 0; i <= get_rows(m_src); ++i){
      for (int j = 0; j <= get_cols(m_src); ++j) {
        if (!(get_elem_matrix(i, j, &res_src, m_src)) && !(get_elem_matrix(i, j, &res_dst, m_dst))){
     			res = res_src + res_dst;
        	if ((e = (set_elem_matrix(i, j, res, &m_dst))) != E_OK)return e;
      	} else return E_READ_ERROR;
    	} 
    } return E_OK;
  }
  return ERROR_INCOMPATIBLE_MATRICES;      
}

error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc)
{
  // se verifica que existan las matrices
  if (!mb) return E_ALLOC_ERROR;
  if (!mc) return E_ALLOC_ERROR;

  // en la multiplicacion escalar las columnas de mb y mc tiene que ser iguales
  if (check_dimetions(mb, get_rows(*mc), get_cols(*mc) == E_OK)){ 
  	
    T_TYPE res = V_NULL;
    // recorro las matrices y multiplico por el escalar guardando en mc
    for (int i = 0 ; i <= get_rows(*mc); ++i){
      for (int j = 0; j <= get_cols(*mc); ++j) {
          if ((e=(get_elem_matrix(i, j, &res, mb))) == E_OK){
          	res *= a;
      			if ((e = (set_elem_matrix(i, j, res, mc))) != E_OK) return e;
          } else return e;
      }
    }
  	return E_OK;    
  } else return ERROR_INCOMPATIBLE_MATRICES;      
}

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst) // idem mult_scalar pero se aplica la multiplicacion a una sola matriz
{
  if (!m_dst) return E_ALLOC_ERROR;

  T_TYPE res = V_NULL;
  
  for (int i = 0 ; i <= get_rows(m_dst); ++i){
    for (int j = 0; j <= get_cols(m_dst); ++j){
      if((e =(get_elem_matrix(i,j, &res, m_dst))) == E_OK){
        res *= a;
        if((e = (set_elem_matrix(i,j, res, &m_dst))) != E_OK) return e;
      } else return e;
    }
  } return E_OK;          
}

error_t create_and_fill_matrix(unsigned int rows, unsigned int cols, T_TYPE a, matrix_t **mb)
{
  *mb = init_matrix(rows, cols); 
  for (int i = 0 ; i < rows; ++i){
    for (int j = 0; j < cols; ++j){
      if ((e = (set_elem_matrix(i,j,a,mb))) != E_OK) return e; 
    }
  }
  return E_OK;      
}

unsigned int get_rows(const matrix_t *ma)
{
  if (ma !=NULL){
    return ma->rows-1; //para solventar el recorrido en el for -1, Revisar con un test
  } else
    return 0; //no hay matriz nx1
}

unsigned int get_cols(const matrix_t *ma)
{
  if (ma !=NULL)
    return ma->cols-1; //para solventar el recorrido en el for -1, Revisar con un test
  else
    return 0;
};

error_t null_matrix(unsigned int n, matrix_t **mc)
{
  return create_and_fill_matrix(n, n, V_NULL, mc);
};


error_t idty_matrix(unsigned int n, matrix_t **m) // diagonal en 1
{
  null_matrix(n, m);
  for (int i= 0 ; i < n; i++) {
  	if (!set_elem_matrix(i,i,1,m)) return E_SIZE_ERROR;
  }
  return E_OK;      
}

error_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  if (!ma) return E_ALLOC_ERROR;
  if (!mb) return E_ALLOC_ERROR;
  if (check_dimetions(ma, get_rows(mb), get_cols(mb) == E_OK)){
  	if ((e = (create_and_fill_matrix(get_rows(ma) + 1, get_cols(mb) + 1, V_NULL, mc))) == E_OK) {  
	  	T_TYPE valA, valB, sum = 0;
     	for (int i = 0; i <= get_rows(ma); ++i) { 
        for (int j = 0; j <= get_cols(mb); ++j) {
          for (int k = 0; k <= get_rows(mb); ++k) {
            if ((e = (get_elem_matrix(i, k, &valA, ma))) != E_OK) return e;
            if ((e = (get_elem_matrix(k, j, &valB, mb))) != E_OK) return e;
            sum = sum + (valA * valB); //sumatoria de multiplicaciones
          }
          if ((e = (set_elem_matrix(i, j, sum, mc)))!= E_OK) return e;
          sum = 0;
     		}
    	} return E_OK;
    } return E_ALLOC_ERROR;
  }
  return ERROR_INCOMPATIBLE_MATRICES;
} 

error_t set_elem_matrix(unsigned int row, unsigned int col, T_TYPE value, matrix_t **m){
	if (!(*m)) return E_ALLOC_ERROR;
  if (is_within_limits(*m, row, col)){
   		(*m)->data[row + row * ((*m)->cols - 1) + col] = value; //acceso directo a la posicion donde se debe almacenar el valor
    	return E_OK;
  	} else return E_SIZE_ERROR;        
}

error_t get_elem_matrix(unsigned int row, unsigned int col, T_TYPE *value, const matrix_t *m)
{
  if (!(m)) return E_ALLOC_ERROR;
  if (is_within_limits(m, row, col)){
    *value = m->data[row + (row * (m->cols - 1)) + col];// devuelvo el valor almacenado haciendo un accceso directo
    return E_OK;
  }else {
  return E_SIZE_ERROR;      
  }
}

int cmp_matrix(const matrix_t *ma, const matrix_t *mb)
{
  if ( check_dimetions(ma, get_rows(mb), get_cols(mb))){
    for(int i=0;i<(mb->rows)*(mb->cols);i++){ // como mi matriz esta alamcenada de manera que es un arreglo unidimencional, multiplico para obtener el largo exacto 
     	if (mb->data[i] - ma->data[i] > V_DELTA_PRECS){ // como lo de adentro es una flotante busco tener un acercamiento a 0 con V_DELTA_PRECS
        	return 0; //false 
        }
    }
    return 1; // true
  }
  return 0;
}

error_t free_matrix(matrix_t **m)
{
  if (!(*m)) return E_ALLOC_ERROR;
  for (int i = 0; i <= get_rows(*m); ++i){
    for (int j =0; j <= get_cols(*m); ++j){
     	free((*m)->data + (sizeof(T_TYPE) * ( i + i * (j-1) + j)));
      printf("se libero memoria %d, %d \n", i, j); //Libera la memoria ocupada por el elemento almacenado en data 
    }
  }
  (*m)->data = NULL;
  free(*m);
  *m = NULL;
  return E_OK;      
}

error_t clear_matrix(matrix_t *m)
{
  if (!m) return E_ALLOC_ERROR;
  for (int i = 0; i < m->rows;i++){
  	for (int j = 0; j < m->cols;j++){
    	if ((e= (set_elem_matrix(i, j, V_NULL, &m))) != E_OK) return e;
    }
  }
  return E_OK;         
}
  
error_t get_row(unsigned int pos, const matrix_t *ma, t_list *l)
{
  if (!ma) return E_ALLOC_ERROR;
  if (row_within_limits(ma, pos)) { // se chequea que al menos exista la fila pos
    if (list_is_empty(*l)){  
      list_create(l);
    }
    T_TYPE aux = 0;
    for (int i = 0 ; i < get_rows(ma); ++i){ 
      if ((e = (get_elem_matrix(pos, i, &aux, ma))) == E_OK){
      	list_add(l,aux);
      }else return e;
    }
    return E_OK;
  }
  return E_SIZE_ERROR;   
}

error_t get_col(unsigned int pos, const matrix_t *ma, t_list *l)
{
  if (!ma) return E_ALLOC_ERROR;
  if (col_within_limits(ma, pos)) {
    if (list_is_empty(*l)){
      list_create(l);
    }
    T_TYPE aux = 0;
    for (int i = 0 ; i < get_cols(ma); ++i){
      if ((e = (get_elem_matrix(i, pos, &aux, ma))) == E_OK){
      	list_add(l,aux);
      } else return e;
    }
    return E_OK;
  }
  return E_SIZE_ERROR;    
}

error_t matrix2list(const matrix_t *ma, t_list *l) // guarda en la lista toda la matriz
{
  if (!ma) return E_ALLOC_ERROR;
  list_create(l);
 // if (l) {
    T_TYPE aux;
    for (int i = 0; i < get_rows(ma); ++i){
      for (int j = 0; j < get_cols(ma); j++){
        if ((e = (get_elem_matrix(i, j, &aux, ma))) == E_OK){
          list_add(l,aux);
        } else return e;
      }
    }
//  }
  return E_OK; 
  }

error_t resize_matrix(unsigned int newrows, unsigned int newcols, matrix_t **ma)
{
  // hacerlo lindo con realloc
  if (!(*ma)) return E_ALLOC_ERROR;
  if (ma == NULL) return E_ALLOC_ERROR; 
  T_TYPE *aux = NULL; //realloc((*ma)->data, newrows * newcols * sizeof(T_TYPE); La informacion de la matris seria incorrecta si se usa realloc() [porque mi matriz esta tomado como un arreglo]
                    //solo funcionaria si se desea, solamente, agregar o retirar filas 
	aux = malloc(newrows * newcols * sizeof(T_TYPE)); // aloco memoria para una nueva matriz de newcol x newrow
  if (!aux) {
    return E_ALLOC_ERROR;
  };
  T_TYPE val = V_NULL;
  int pos;
  /**
  int filas = (*ma)->rows;
  //Checkea si debe completar nuevos valores
  if (newrows > filas)
  {
    int filasVacias =  newrows - filas;
  }
  **/
  for (int i = 0; i < newrows; ++i ){
    for (int j = 0; i < newcols; ++j){
    	pos = i + i * (j - 1) + j; 
      	if ((e = (get_elem_matrix(i, j, &val, *ma))) == E_OK){
        	aux[pos] = val;
        	free((*ma)->data + (sizeof(T_TYPE) * pos)); //Libera la memoria ocupada por el elemento almacenado en data
      	} else {
      		aux[pos] = V_NULL;
      	} 
    }
  }

  (*ma)->data = aux;
  (*ma)->cols = newcols;
  (*ma)->rows = newrows;

  return E_OK;  
}

matrix_t *init_matrix(unsigned int nrows, unsigned int ncols)
{
  matrix_t *m = NULL;
  m = malloc(sizeof(matrix_t));
  if (!m) {
   
   return NULL;
  }

  m->data = NULL;
  m->data = malloc(nrows * ncols * sizeof(T_TYPE));
  if (!m->data) {
    return NULL;
  }
//  m->fmt = malloc(sizeof(matrix_fmt_t)); No anda
  m->rows = nrows;
  m->cols = ncols;

  return m;
}

bool row_within_limits(const matrix_t *m, unsigned int cant){
  if (!m) return E_ALLOC_ERROR;
	return m->rows >= cant; 
}

bool col_within_limits(const matrix_t *m, unsigned int cant){
	if (!m) return E_ALLOC_ERROR;
  return m->cols >= cant;
}

bool is_within_limits(const matrix_t *m, unsigned int row, unsigned int col){
	if (!m) return E_ALLOC_ERROR;
  return row_within_limits(m, row) && col_within_limits(m, col);
}

error_t check_cant_row(const matrix_t *ma, int row){

  if (ma->rows == row){
     return E_OK;
   } else {
    return E_SIZE_ERROR;
   }
};


error_t check_cant_col(const matrix_t *ma, int col){

  if (ma->cols == col){
     return E_OK;
   } else {
    return E_SIZE_ERROR;
   }

};


error_t check_dimetions(const matrix_t *ma, int row, int col){
    
    if ((check_cant_row(ma,row) != E_OK  && check_cant_col(ma, col) != E_OK)){
      return E_SIZE_ERROR;
    } else {
      return E_OK;
    }
}