#include "list.h"

// Please: complete me

list_t ls_create()
{
  return (list_t) NULL;
}

void ls_free(/*@inout@*/ list_t *self)
{
  // Please: complete me
}

int ls_to_file(FILE *fp, const /*@in@*/ list_t self)
{
  // Please: complete me
  return -1;
}

bool ls_is_empty(const /*@in@*/ list_t self){
   return self == NULL;
}

int ls_length(const /*@in@*/ list_t self){

}

int ls_includes(/*@in@*/ list_t self, const /*@in@*/ DATATYPE elem){

}

DATATYPE ls_head(const /*@in@*/ list_t self){
  return header;
}

list_t ls_tail(const /*@in@*/ list_t self){
  return tail;
}

/*
 * ls_add_...
 * 
 * Return: 0: con 'exito 
 *        -1: error (probablemente malloc)
 */

//error_t ls_add(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem);
int ls_add(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem){
  return ls_add_back(self, elem);
}

int ls_add_front(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem){
  list_node_t* newNode = (list_node_t*)malloc(sizeof(list_node_t)); 
  if (newNode == NULL) return 0;
   
  newNode->data = data;  
  newNode->next = NULL;  
  //chequea si la lista esta vacia
  if(header == NULL) {  
    header = newNode;  
    tail = newNode;  
    return 1;
  }  
  else { 
    newNode->next = header; 
    header = newNode;
    return 1;
  }  
}


int ls_add_back(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem){
  list_node_t* newNode = (list_node_t*)malloc(sizeof(list_node_t)); 
  if (newNode == NULL) return 0;
   
  newNode->data = data;  
  newNode->next = NULL;  
  //chequea si la lista esta vacia
  if(header == NULL) {  
    header = newNode;  
    tail = newNode;  
    return 1;
  }  
  else { 
    tail->next = newNode;
    tail = newNode;
    return 1;
  }
}

/* Precond: !ls_empty(self) */
DATATYPE ls_remove(/*@inout@*/ list_t *self);

/*
 * status code:
 * 0: OK operaci'on con 'exito
 * -1: error, lista vac'ia
 * En el caso de status=-1 el valor del par'ametro 
 * elem debe ser ignroado
 */
void ls_remove_status(/*@inout@*/ list_t *self, 
                      /*@out@*/   DATATYPE *elem, 
                      /*@out@*/   int *status){

                      }
