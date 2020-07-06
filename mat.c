#include <stdlib.h>
#include "mat.h"
#include "list.h"

error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  if (!m) return E_ALLOC_ERROR;
  m->ffmt = fmt;
  return E_OK      
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  if (!m) return E_ALLOC_ERROR;
  fmt = m->ffmt;
  return E_OK;      
}

// abria que modularizar
error_t read_matrix(FILE *fp, matrix_t *m)
{
	FILE arch = fopen(fp, 'r'); //chequear parametros
	int auxFormat = matrix_file_handler_read_header(arch);
	if(!auxFormat){
		//Esto es un modulo
		t_matrix_file_handler_dimensions dim = matrix_file_handler_m1_dimensions(arch);
		m = init_matrix(dim->rows, dim->colums);
		clear_matrix(&m);
		set_ffmt_matrix(&m, auxFormat);
		//Termina el modulo
		char * linea = NULL;
		//usando el read line de LeerArchivo.h y cargar la matrix en un loop mientras arch != EOF
		unsigned int row, col = 0;
		char separador[] = " ";
		while(arch != EOF){ //puede haber otra manera pero esto tendria que estar bien
			if (matrix_file_handler_read_line(linea, 0, arch)){ //fgets devuelve lo mismo que lo que asigna a linea,
																					//si hubo un error retorna NULL
				//una linea puede traer mas de un valor, se debe separar por " " hasta que se lea un EOL
				//¿hay que chequear que la linea no sea un comentario?
				//Esto es un modulo
				char *ptr = strtok(linea, separador);
				while(ptr != NULL){
					printf("'%s'\n", ptr);
					//ya tenes el valor a guardar en la matris
					T_TYPE value = atof(ptr); // pasa el string a flotante
					set_elem_matrix(row, col, value, &m);
					if (++col == dim->colums){
						col = 0;
						if (++row == dim->rows) return E_SIZE_ERROR;
					}
					//guardó el valor en la matris, EN TEORIA, y vuelve a leer
					ptr = strtok(NULL, separador); //El primer parametro es NULL dado que strtok recuerda el string y donde estaba en el (pareciera)
				}
				//Termina el modulo
			}
		}
		return E_OK;
	}	
	//Si no es M1 el archivo, en este caso no se hace nada
	else return -E_NOTIMPL_ERROR;      
}

error_t write_matrix(FILE *fp, const matrix_t *m)
{
   FILE arch = fopen(fp, 'w');
	//hay que conseguir el formato y escribirlo
	//escribir "m->rows" x "m->colums"
	//¿Comentarios?
	//for i
		//for j
			//escribir "valor[i][j] "
  	//escribir EOL
	fclose(fp);      

  return -E_NOTIMPL_ERROR;      
}

error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
    if (!m_src) return E_ALLOC_ERROR;
  	if (create_and_fill_matrix(get_row(&m_src), get_col(&m_src), V_NULL, &m_dst){
      T_TYPE res = 0.0;
      for ( int i = 0; i <= get_rows(&m_src), ++i){
        for (int j = 0; j <= get_cols(&m_src), ++j) {
       		if(!(get_elem_matrix(i, j, &res, &m_src)){
          	if (!(set_elem_matrix(i, j, res, &m_dst))) {} else return E_NOTIMPL_ERROR;
          }
        }
      } return E_OK
      
    } return E_ALLOC_ERROR;
   
}

error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  if (!mb) return E_ALLOC_ERROR;
  if (!ma) return E_ALLOC_ERROR;
  if (check_dimentions(*ma, get_rows(&mb), get_cols(&mb)){
  	T_TYPE res_ma = 0.0;
    T_TYPE res_mb = 0.0;
    T_TYPE res_mc = 0.0;
    if (create_and_fill_matrix(get_row(&mb), get_col(&mb), V_NULL, &mc) { 
      for ( int i = 0; i <= get_rows(&ma), ++i){
        for (int j = 0; j <= get_cols(&ma), ++j) {
          if (!(get_elem_matrix(i, j, &res, &ma)) && !(get_elem_matrix(i, j, &res, &mb))){
              res_mc = res_ma + res_ mb;
              if (!(set_elem_matrix(i, j, res_mc, &mc))) {} else return E_NOTIMPL_ERROR;
          } else return E_NOTIMPL_ERROR;
      }
  	} else return E_ALLOC_ERROR;
    }
  } else {
  	return -E_NOTIMPL_ERROR;
  }
  return E_OK;
}     
}

error_t sum_inplace(const matrix_t *m_src, matrix_t *m_dst)
{
  	if (!m_src) return E_ALLOC_ERROR;
  if (!m_dst) return E_ALLOC_ERROR;
  if (check_dimentions(*m_src, get_rows(&m_src), get_cols(&m_src)){
  	T_TYPE res_src = 0.0;
    T_TYPE res_dst = 0.0;
		T_TYPE res = 0.0;
    for ( int i = 0; i <= get_rows(&m_src), ++i){
      for (int j = 0; j <= get_cols(&m_src), ++j) {
        if (!(get_elem_matrix(i, j, &res_src, &m_src)) && !(get_elem_matrix(i, j, &res_dst, &m_dst))){
     			res = res_src + res_dst;
        	if (!(set_elem_matrix(i, j, res, &m_dst))){} else return E_NOTIMPL_ERROR;
      	} else { return E_NOTIMPL_ERROR }
    	} 
    } return E_OK
  }
  return -E_NOTIMPL_ERROR;      
   
}

error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc)
{
  	if (!mb) return E_ALLOC_ERROR;
  if (!mc) return E_ALLOC_ERROR;
  if (check_dimentions(*mb, get_rows(&mc), get_cols(&mc)){
  	T_TYPE res = 0.0;
    for (int i = 0 ; i <= get_rows(&mc); ++i){
      for (int j = 0; j <= get_cols(&mc); ++j) {
          if (!(get_elem_matrix(i, j, &res, &mb))){
          	res *= a;
      			if (!(set_elem_matrix(i, j, res, &mc)));
          } else return -E_NOTIMPL_ERROR;
      }
    }
  	return E_OK;    
  } else {  
  	return E_NOTIMPL_ERROR;      
  }
}

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst)
{
  if (!m_dst) return E_ALLOC_ERROR;
    T_TYPE res = 0.0;
  	for (int i = 0 ; i <= get_rows(&m_dst); ++i){
      for (int j = 0; j <= get_cols(&m_dst); ++j) {
  			if (!(get_elem_matrix(i,j, &res, &m_dst))){
        	res *= a;
          if (!(set_elem_matrix(i,j, res, &m_dst)));
           } else return -E_NOTIMPL_ERROR
      }
  	return E_OK;    
  } else {  
  	return -E_NOTIMPL_ERROR;      
  };      
};

error_t create_and_fill_matrix(unsigned int rows, unsigned int cols, T_TYPE a, matrix_t **mb)
{
  mb = init_matrix(rows, cols);

  for (int i = 0 ; i <= row; ++i){
    for (int j = 0; j <= cols; ++j){
      set_elem_matrix(i,j,a,&mb);
    };
  };

  return E_OK;      
};

unsigned int get_rows(const matrix_t *ma)
{
  if (ma !=NULL){
    return ma->rows;
  } else
    return 0;
  };
};

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
  /**
	1 0 0
	0 1 0
	0 0 1
	Matriz identidad
	**/
  null_matrix(n, m);
  for (i=0 ; i <=n; i++) {
  	if (set_element_matrix(i,i,1,m) != E_OK) return //error
  }

  return E_OK;      
}

error_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
    if (!ma) return E_ALLOC_ERROR;
  if (!mb) return E_ALLOC_ERROR;
  if (check_dimentions(*ma, get_rows(&mb), get_cols(&mb)){
   if (create_and_fill_matrix(get_row(&ma), get_col(&mb), V_NULL, &mc) {  
		 int sum = 0;
     T_TYPE valA, valB = 0;
     for (int i = 0; i < get_rows(&ma); ++i) {
      for (int j = 0; j < get_cols(&mb); ++j) {
        for (int k = 0; k < get_rows(&mb); ++k) {
          get_elem_matrix(i, k, &valA, &ma);
          get_elem_matrix(k, j, &valB, &mb);
          sum = sum + (valA * valB);
        }
        set_elem_matrix(i, j, sum, &mc);
        sum = 0;
      }
     }
     return E_OK;
   }
    return E_ALLOC_ERROR;
  } 
  return E_SIZE_ERORR;      
      
}

error_t set_elem_matrix(unsigned int row, unsigned int col, T_TYPE value, matrix_t **m)
{
  if (check_dimetions(*m, row, col) == E_OK){
   m->data[row + row * (m->cols - 1) + col] = value;
    return E_OK;
  } else {
    return E_SIZE_ERROR;
  }
        
}

error_t get_elem_matrix(unsigned int row, unsigned int col, T_TYPE *value, const matrix_t *m)
{
    //To DO checkear dimenciones row == m->rows y col = m->cols
  if (check_dimetions(*m, row, col) == E_OK){
    value = m->data[row + row * (m->cols - 1) + col];
    return E_OK;
  }else {
  return E_SIZE_ERROR;      
  }
}

int cmp_matrix(const matrix_t *ma, const matrix_t *mb)
{
  if ( (mb->rows != ma->rows) || (mb->cols != ma->cols) ){
      return 0;
    } else{
      	for(int i=0;i<(mb->rows)*(mb->cols);i++){
	  			//if ( mb->contents[i] !=  ma->contents[i])
	  			//if ((mb->contents[i] - ma->contents[i]) >=  V_DELTA_PRECS)
        	if (mb->contents[i] - ma->contents[i]) >=  V_DELTA_PRECS){
          	return 0; //false 
        	};
      	};
        return 1; // true
  	};
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
    	m[i][j] = 0;
    }
  }
  return E_OK;         
}
  
error_t get_row(unsigned int pos, const matrix_t *ma, list_t *l)
{
  if (check_cant_row == E_OK) {
    if (list_is_empty(l)){
      list_create(&l);
    };
    if (!m) return E_ALLOC_ERROR;
    T_TYPE aux = 0;
    for (int i = 0 ; i <= ma->col; ++i){
      aux =  get_elem_matrix(pos, i, &aux, &ma);
      list_add(&l,aux);
    }
    return E_OK
  }
  return -E_NOTIMPL_ERROR;      
}

error_t get_col(unsigned int pos, const matrix_t *ma, list_t *l)
{
  if (check_cant_row == E_OK) {
    if (list_is_empty(l)){
      list_create(&l);
    };
    if (!m) return E_ALLOC_ERROR;
    T_TYPE aux = 0;
    for (int i = 0 ; i <= ma->row; ++i){
      aux =  get_elem_matrix(i, pos, &aux, &ma);
      list_add(&l,aux);
    }
    return E_OK
  }
  return -E_NOTIMPL_ERROR;      
}

error_t matrix2list(const matrix_t *ma, list_t *l)
{
  if (!ma) return E_ALLOC_ERROR;
  list_create(&l);
  for (int i=0; i <= ma->row; ++i){
    for (int j= 0; ma->col; j++){
      aux =  get_elem_matrix(i, pos, &aux, &ma);
      list_add(&l,aux);
    };
  };
  return E_OK;

}

error_t resize_matrix(unsigned int newrows, unsigned int newcols, matrix_t **ma)
{
  clear_matrix(*ma);
  return -E_NOTIMPL_ERROR;  
}

/*** EOF mat.c ***/
matrix_t init_matrix(uint32_t nrows, uint32_t ncols)
{
  matrix_t *m = NULL;
  m = malloc(sizeof(matrix_t));
  if (!m) {
    /*error */
  };
  m->data = NULL;
  m->data = malloc(nrows * ncols * sizeof(T_TYPE));
  if (!m->data) {
    /*error*/
  };
  m->rows = nrows;
  m->cols = ncols;

  return m;
}

error_t check_cant_row(const matrix_t *ma, int row){

  if (ma->row == row){
     return E_OK;
   } else {
    return E_SIZE_ERROR;
   }
};


error_t check_cant_col(const matrix_t *ma, int col){

  if (ma->col == col){
     return E_OK;
   } else {
    return E_SIZE_ERROR;
   }

};


error_t check_dimetions(const matrix_t *ma, int row, int col){
    
    if (check_cant_row(&ma,row) != E_OK ) && (check_cant_col(&ma, col) != E_O){
      return E_SIZE_ERROR;
    } else {
      return E_OK;
    };


};

}