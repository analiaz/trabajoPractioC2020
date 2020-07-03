#include "list.h"
#include <stdlib.h>

// completar
void list_create(t_list *l){
  *l = NULL;
}

short list_find(t_list l, t_data e){
  while(l)
  {
    if (l->data == e) return 1;
    l = l->next;
  }
  return 0;
}

short list_is_empty(const t_list l){
  return l == NULL;
}

// fijarse que devuelve un floatt deberia ser un error ponele
t_data list_add(t_list *l, t_data e){
  t_list_node *node = malloc(sizeof(t_list_node));
  node->data = e;
  node->next = NULL;
  if (*l == NULL) *l = node;
  else {
    t_list_node *n = *l;
    while (n->next) n = n->next;
    n->next = node;
  }
  return e;
}

t_data  list_delete(t_list *l, t_data e){
  if (list_find(*l,e))
  {
    t_list_node *prev = NULL, *node = *l;
    while(node->data != e && node)
    {
      prev = node;
      node = node->next;
    }
    if (!prev) *l = node->next;
    else
    {
      prev->next = node->next;
    }
    free(node);
  }
  return e;
}

/* Libera las estructuras internas usadas por este tipo de dato */
void list_free(t_list *l) {
t_list_node *node = *l;
  while(node)
  {t_list_node *aux;
    aux = node;
    node = node->next;
    free(aux);
  }
  *l=NULL;
}