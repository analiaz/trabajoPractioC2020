#include <stdlib.h>
#include "mat.h"
#include "list.h"

error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t read_matrix(FILE *fp, matrix_t *m)
{
  return -E_NOTIMPL_ERROR;      
}

error_t write_matrix(FILE *fp, const matrix_t *m)
{
  return -E_NOTIMPL_ERROR;      
}

error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
  return -E_NOTIMPL_ERROR;      
}

error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  return -E_NOTIMPL_ERROR;      
}

error_t sum_inplace(const matrix_t *m_src, matrix_t *m_dst)
{
  return -E_NOTIMPL_ERROR;      
}

error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc)
{
  return -E_NOTIMPL_ERROR;      
}

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst)
{
  return -E_NOTIMPL_ERROR;      
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
  return -E_NOTIMPL_ERROR;      
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