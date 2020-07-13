#include <stdlib.h>
#include "LeerArchivo.h"
#include "mat.h"
#include <stdbool.h>  

error_t e;

error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  if (!m) return E_ALLOC_ERROR;
  m->fmt = fmt;
  return E_OK;      
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  if (!m) return E_ALLOC_ERROR;
  *fmt = m->fmt;
  return E_OK;      
}

// abria que modularizar
error_t read_matrix(FILE *fp, matrix_t *m)
{
	int auxFormat = matrix_file_handler_read_header(fp);
	if(!auxFormat){
		//Esto es un modulo
		t_matrix_file_handler_dimensions dim = matrix_file_handler_m1_dimensions(fp); 
		m = init_matrix(dim.rows, dim.columns);
		clear_matrix(m);
		set_ffmt_matrix(m, auxFormat);
		//Termina el modulo
		char * linea = NULL;
		//usando el read line de LeerArchivo.h y cargar la matrix en un loop mientras arch != EOF
		unsigned int row, col = 0;
		char separador[] = " ";
		while(!feof(fp)){ //devuelve !=0 si encuentra endoffile sino 0 
			if (matrix_file_handler_read_line(linea, 0, fp)){ //fgets devuelve lo mismo que lo que asigna a linea,
																					//si hubo un error retorna NULL
				//una linea puede traer mas de un valor, se debe separar por " " hasta que se lea un EOL
				//¿hay que chequear que la linea no sea un comentario?
				//Esto es un modulo
				char *ptr = strtok(linea, separador);
				while(ptr != NULL){
					printf("'%s'\n", ptr);
					//ya tenes el valor a guardar en la matris
					T_TYPE value = atof(ptr); // pasa el string a flotante
					if ( (e = (set_elem_matrix(row, col, value, &m))) != E_OK ) return e;
					if (++col == dim.columns){
						col = 0;
						if (++row == dim.rows) return E_SIZE_ERROR;
					}
					//guardó el valor en la matris, EN TEORIA, y vuelve a leer
					ptr = strtok(NULL, separador); //El primer parametro es NULL dado que strtok recuerda el string y donde estaba en el (pareciera)
				}
				//Termina el modulo
			}
		}
    fclose(fp);
		return E_OK;
	}	
	//Si no es M1 el archivo, en este caso no se hace nada
	else return -E_NOTIMPL_ERROR;      
}

error_t write_matrix(FILE *fp, const matrix_t *m)
{
	//hay que conseguir el formato y escribirlo
	//escribir "m->rows" x "m->colums"
	//¿Comentarios?
	//for i
		//for j
			//escribir "valor[i][j] "
  	//escribir EOL
  if (!m) return E_ALLOC_ERROR;
  fprintf(fp, "M1 \n ## Matriz %d x %d \n ",m->rows, m->cols);
  fprintf(fp, "%d %d \n", m->rows, m->cols );
  T_TYPE val = V_NULL;
  for(int i = 0; i <= get_rows(m); ++i) {
    for (int j = 0; j <= get_cols(m); ++j){
      if ((e = (get_elem_matrix(i, j, &val, m))) != E_OK) return e;
      fprintf(fp, "%f", val);
    }
    fprintf(fp, "\n");
  }
  
	fclose(fp);      

  return E_OK;      
}

error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
  if (!m_src) return E_ALLOC_ERROR;
  if (create_and_fill_matrix(get_rows(m_src), get_cols(m_src), V_NULL, m_dst)){
    T_TYPE res = V_NULL;
    error_t e;
    for (int i = 0; i <= get_rows(m_src); ++i){
      for (int j = 0; j <= get_cols(m_src); ++j){
        if((e = (get_elem_matrix(i, j, &res, m_src)) == E_OK)){
            if( (e = (set_elem_matrix(i, j, res, m_dst))) != E_OK){}
            else return E_NOTIMPL_ERROR;
        }
        return e;
      }
    } return E_OK;
  } else return E_ALLOC_ERROR;
}

error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  if (!mb) return E_ALLOC_ERROR;
  if (!ma) return E_ALLOC_ERROR;
  if (check_dimetions(ma, get_rows(mb), get_cols(mb))){
  	T_TYPE res_ma = V_NULL;
    T_TYPE res_mb = V_NULL;
    T_TYPE res_mc = V_NULL;
    if (!create_and_fill_matrix(get_rows(mb), get_cols(mb), V_NULL, mc)){ 
      for ( int i = 0; i <= get_rows(ma); ++i){
        for (int j = 0; j <= get_cols(ma); ++j) {
          if (!(get_elem_matrix(i, j, &res_ma, ma)) && !(get_elem_matrix(i, j, &res_mb, mb))){
              res_mc = res_ma + res_mb;
              if ((e = (set_elem_matrix(i, j, res_mc, mc))) != E_OK) return e; else return E_NOTIMPL_ERROR;
          } else return E_READ_ERROR;
        }
      } return E_OK;
  	} else return E_ALLOC_ERROR;
  } else return ERROR_INCOMPATIBLE_MATRICES;
}     

error_t sum_inplace(const matrix_t *m_src, matrix_t *m_dst)
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
  if (!mb) return E_ALLOC_ERROR;
  if (!mc) return E_ALLOC_ERROR;
  if (check_dimetions(mb, get_rows(*mc), get_cols(*mc) == E_OK)){
  	T_TYPE res = V_NULL;
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

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst)
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
  for (int i = 0 ; i <= rows; ++i){
    for (int j = 0; j <= cols; ++j){
      if ((e = (set_elem_matrix(i,j,a,mb))) != E_OK) return e;
    }
  }
  return E_OK;      
}

unsigned int get_rows(const matrix_t *ma)
{
  if (ma !=NULL){
    return ma->rows;
  } else
    return 0;
}

unsigned int get_cols(const matrix_t *ma)
{
  if (ma !=NULL)
    return ma->cols;
  else
    return 0;
};

error_t null_matrix(unsigned int n, matrix_t **mc)
{
  return create_and_fill_matrix(n, n, V_NULL, mc);
};


error_t idty_matrix(unsigned int n, matrix_t **m)
{
  null_matrix(n, m);
  for (int i=0 ; i <=n; i++) {
  	if (!set_elem_matrix(i,i,1,m)) return E_SIZE_ERROR;
  }
  return E_OK;      
}

error_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  if (!ma) return E_ALLOC_ERROR;
  if (!mb) return E_ALLOC_ERROR;
  if (check_dimetions(ma, get_rows(mb), get_cols(mb) == E_OK)){
  	if (!create_and_fill_matrix(get_rows(ma), get_cols(mb), V_NULL, mc)) {  
		T_TYPE valA, valB, sum = 0;
     	for (int i = 0; i < get_rows(ma); ++i) {
        for (int j = 0; j < get_cols(mb); ++j) {
          for (int k = 0; k < get_rows(mb); ++k) {
            if ((e = (get_elem_matrix(i, k, &valA, ma))) != E_OK) return e;
            if ((e = (get_elem_matrix(k, j, &valB, mb))) != E_OK) return e;
            sum = sum + (valA * valB);
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
	if (is_within_limits(*m, row, col)){
   		(*m)->data[row + row * ((*m)->cols - 1) + col] = value;
    	return E_OK;
  	} else return E_SIZE_ERROR;        
}

error_t get_elem_matrix(unsigned int row, unsigned int col, T_TYPE *value, const matrix_t *m)
{
  if (is_within_limits(m, row, col)){
    *value = m->data[row + (row * (m->cols - 1)) + col];
    return E_OK;
  }else {
  return E_SIZE_ERROR;      
  }
}

int cmp_matrix(const matrix_t *ma, const matrix_t *mb)
{
  if ( check_dimetions(ma, get_rows(mb), get_cols(mb))){
    for(int i=0;i<(mb->rows)*(mb->cols);i++){
     	if (mb->data[i] - ma->data[i] >=  V_DELTA_PRECS){
        	return 0; //false 
        }
    }
    return 1; // true
  }
  return 0;
}

error_t free_matrix(matrix_t **m)
{
  free(*m);
  return -E_NOTIMPL_ERROR;      
}

error_t clear_matrix(matrix_t *m)
{
  if (!m) return E_ALLOC_ERROR;
  for (int i = 0; i <= m->rows;i++){
  	for (int j = 0; j <= m->cols;j++){
    	if ((e= (set_elem_matrix(i, j, V_NULL, &m))) != E_OK) return e;
    }
  }
  return E_OK;         
}
  
error_t get_row(unsigned int pos, const matrix_t *ma, t_list *l)
{
  if (!ma) return E_ALLOC_ERROR;
  if (row_within_limits(ma, pos)) {
    if (list_is_empty(*l)){
      list_create(l);
    }
    T_TYPE aux = 0;
    for (int i = 0 ; i <= get_rows(ma); ++i){
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
    for (int i = 0 ; i <= get_cols(ma); ++i){
      if ((e = (get_elem_matrix(i, pos, &aux, ma))) == E_OK){
      	list_add(l,aux);
      } else return e;
    }
    return E_OK;
  }
  return E_SIZE_ERROR;      
}

error_t matrix2list(const matrix_t *ma, t_list *l)
{
  if (!ma) return E_ALLOC_ERROR;
  list_create(l);
  T_TYPE aux;
  for (int i=0; i <= get_rows(ma); ++i){
    for (int j= 0; j <= get_cols(ma); j++){
      if ((e = (get_elem_matrix(i, j, &aux, ma))) == E_OK){
        list_add(l,aux);
      } else return e;
    }
  }
  return E_OK;

}

error_t resize_matrix(unsigned int newrows, unsigned int newcols, matrix_t **ma)
{
  // crear un T_TYPE* aux
	// asignar espacio a aux de newrows * newcols
	//copiar los valodres de ma->data en aux
	//free(ma->data)
	//ma->data = &aux
  //TO DO refactorizar init_matrix y usar las nuevas funciones aca
  T_TYPE *aux;
	aux = malloc(newrows * newcols * sizeof(T_TYPE));
  if (!aux) {
    exit(E_ALLOC_ERROR);
  };
  T_TYPE val = V_NULL;
  for (int i = 0; i <= newrows; ++i ){
    for (int j = 0; i <= newcols; j++){
      if ((e = (get_elem_matrix(i, j, &val, *ma))) == E_OK){
        aux[newrows + newrows * ((*ma)->cols - 1) + newcols] = val;
      } else return e; 
    }
  }
  (*ma)->data = aux; //ignoro completamente el hecho de que queda memoria no liberada
  (*ma)->cols = newcols;
  (*ma)->rows = newrows;

  return E_OK;  
}

matrix_t *init_matrix(unsigned int nrows, unsigned int ncols)
{
  matrix_t *m = NULL;
  m = malloc(sizeof(matrix_t));
  if (!m) {
    exit(E_ALLOC_ERROR);
  };
  m->data = NULL;
  m->data = malloc(nrows * ncols * sizeof(T_TYPE));
  if (!m->data) {
    exit(E_ALLOC_ERROR);
  };
  m->rows = nrows;
  m->cols = ncols;

  return m;
}

bool row_within_limits(const matrix_t *m, unsigned int cant){
	return m->rows <= cant;
}

bool col_within_limits(const matrix_t *m, unsigned int cant){
	return m->cols <= cant;
}

bool is_within_limits(const matrix_t *m, unsigned int row, unsigned int col){
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