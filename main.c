#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}


/*Compara 2 'Elemento' que contienen como valor un 'int'*/
int cmp_int(const void* a, const void* b) 
{
    int n1 = *(int *)a;
    int n2 = *(int *)b;
    // Se comparan los elementos
    if(n1 > n2)
    {
        return 1;
    }
    if(n1 < n2)
    {
        return -1;
    }
    return 0;
}


//funcion auxiliar para hacer swap
void swap(void * a, void * b, size_t size){
    void * tmp = malloc(size);
    memcpy(tmp,a,size);
    memcpy(a,b,size);
    memcpy(b,tmp,size);
    free(tmp);
}

//funcion auxiliar para ordenar un arreglo
void bsort(void* base, size_t num, size_t size,int (*compar)(const void*, const void*)){
    int i = 0;
    int j = 1;
    for (i = 0; (i <num); i++)
    { 
        for (j = i+1; j < num; j++)
        { 
            char * aux = (char*)base + size*i;
            char *aux2 = (char*)base + size*j;
            if(compar(aux,aux2)>0)
            {
                swap(aux,aux2,size);
            }
        }
    }
}


/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)) {
  int len = (int) longitud(lista);
    Elemento* l = (*lista);
    int arr [len];
    int i = 0;
    while (i<len)
    {
        arr[i] =  *((int*)l->valor);
        l = l->siguiente;
        i++;
    }
    for(i = 0; i < len; i++)
    {
        printf("%d, ", arr[i] );
    }
    printf("\n");
    bsort(arr,len,sizeof(int),&cmp_int);

    for(i = 0; i < len; i++)
    {
        printf("%d, ", arr[i] );
    }
    printf("\n");
    i = 0;
    l = (*lista);
    for(i = 0; i < len; i++)
    {
        l->valor = &arr[i];
        l = l->siguiente;
    }

}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista ls) {
    Elemento *temp = *ls;
    while(temp != NULL) {
        Elemento *aux = temp;
        temp = temp->siguiente;
        free(aux->valor);
        free(aux);
    }
    free(ls);   //liberamos la lista
    ls = NULL;
}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion) {
    if (*lista == NULL || posicion < 0)
    {
     return NULL;
    }
    Elemento *temp = *lista, *ret;
    if (posicion == 0) 
    {       
        *lista = temp->siguiente;
        return temp;
    }
    while (--posicion) 
    {
        temp = temp->siguiente;
        if (temp->siguiente == NULL)
        {
            return NULL;
        }
    }
    ret = temp->siguiente;
    temp->siguiente = temp->siguiente->siguiente;
    return ret;
}

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_int(Lista lista) 
{
    Elemento *temp = *lista;
    
    while (temp != NULL) 
    {
        printf("%i ", *(int*)temp->valor);
        temp = temp->siguiente;
    }
    
}

/*Crea una lista vacía*/
Lista crea_lista() 
{
    Lista lista = (Lista) malloc(sizeof(Lista));
    *lista = NULL;      //lista esta vacia
    return lista;
}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
int inserta_elemento(Lista lista, void *valor) {
   
    Elemento *nuevo = (Elemento*) malloc(sizeof(Elemento));
    nuevo->siguiente = NULL;
    nuevo->valor = valor;
   
    if (*lista == NULL) 
    {  
        *lista = nuevo;
        return 1;
    }

    int size = 0;
    Elemento *temp = *lista;    
    while (temp->siguiente != NULL) 
    {
        temp = temp->siguiente;
        size++;
    }
    temp->siguiente = nuevo;
    return size;

}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
    Elemento *temp = *lista;
    size_t size = 0;
    while (temp->valor!= NULL) {
        
        temp = temp->siguiente;
        size++;
    }
    return size;
}
