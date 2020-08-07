# define MAXINTTOSTR 8
#endif

#define PRNMASK(string) "%s "string
// PRNMASK(DATATYPEPRMASK)

typedef struct list_node {
         DATATYPE           elem;
         struct list_node   *next;
} list_node_t;

typedef list_node_t *list_t;

typedef list_node_t* header;

typedef list_node_t* tail;

list_t ls_create();

bool ls_is_empty(const /*@in@*/ list_t self);

int ls_length(const /*@in@*/ list_t self);

int ls_includes(/*@in@*/ list_t self, const /*@in@*/ DATATYPE elem);

DATATYPE ls_head(const /*@in@*/ list_t self);

list_t ls_tail(const /*@in@*/ list_t self);

/*
 * ls_add_...
 * 
 * Return: 0: con 'exito 
 *        -1: error (probablemente malloc)
 */

//error_t ls_add(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem);
int ls_add(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem);

int ls_add_front(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem);

int ls_add_back(/*@inout@*/ list_t *self, const /*@in@*/ DATATYPE elem);

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
                      /*@out@*/   int *status);

void ls_free(/*@inout@*/ list_t *self);

int ls_to_file(FILE *fp, const /*@in@*/ list_t self);

#endif /* list.h */