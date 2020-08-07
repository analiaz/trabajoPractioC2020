#ifndef _T_LIST_H
#define _T_LIST_H

typedef double t_data;

typedef struct t_list_node {
 struct t_list_node *next;
 t_data data;
} * t_list;

typedef struct t_list_node t_list_node;


/* Crea una nueva lista, que puede usarse de inmediato */
void list_create(t_list *l);

/* Busca eun elemento en la lista y retorna verdadero si existe */
short list_find(t_list, t_data e);

/* Devuelve verdadero si la lista est	a */
short list_is_empty(const t_list l);

/* Agrega un elemento a la lista. Luego lo retorna */
t_data list_add(t_list *, t_data e);

/* Elimina un elemento de la lista y luego lo retorna */
t_data list_delete(t_list *, t_data e);

/* Libera las estructuras internas usadas por este tipo de dato */
void list_free(t_list *l);

#endif