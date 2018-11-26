#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"



static Node* getNode(LinkedList* lista, int nodeIndex);
static int addNode(LinkedList* lista, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void){
    LinkedList* lista;
    lista = (LinkedList *)malloc(sizeof(LinkedList));
    if(lista != NULL){
        lista->size=0;
        lista->pFirstNode = NULL;
    }
    return lista;
}

/** \brief Retorna la cantidad de elementos de la lista
 * \param lista LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 */
int ll_len(LinkedList* lista){
    int returnAux = -1;
    if(lista != NULL){
        returnAux = lista->size;
    }
    return returnAux;
}

/** \brief Coloca el iterador en el primer nodo
 *  \param lista LinkedList* Puntero a la lista
 */
void ll_startIterator(LinkedList* lista){
    if(lista != NULL){
        lista->actualNode = lista->pFirstNode;
    }
}

/** \brief  Toma el siguiente elemento de la lista utilizando el nodo declarado estaticamente
 *          Y coloca el nodo en el siguiente indice de la lista
 *  \param void
 *  \return void*   Retorna (NULL) en el caso de no conseguir un nuevo elemento o si el siguiente elemento es NULL
 *                  Y retorna el puntero al elemento si existe.
 */
void* ll_getNext(LinkedList* lista){
    void* returnAux = NULL;
    if(lista->actualNode != NULL){
        returnAux = lista->actualNode->pElement;
        lista->actualNode = lista->actualNode->pNextNode;
    }
    return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 * \param lista LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 */
static Node* getNode(LinkedList* lista, int nodeIndex){
    Node* pNode = NULL;
    int contador;
    if(lista != NULL && ll_len(lista) > 0 && nodeIndex < ll_len(lista) && nodeIndex >= 0){
        pNode = lista->pFirstNode;//caso particular
        for(contador=0;contador< nodeIndex;contador++){ //reccore hasta uno antes del proximo
            pNode = pNode -> pNextNode;//nodo tiene la direccion del proximo nodo
        }
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 * \param lista LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 */
Node* test_getNode(LinkedList* lista, int nodeIndex){
    return getNode(lista, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param lista LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
static int addNode(LinkedList* lista, int nodeIndex,void* pElement){ //size de la lista es la cantidad de nodos //index nodo es donde esta el nodo en la lista.
    int returnAux = -1;
    Node* newNode = malloc(sizeof(Node));
    if(lista != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(lista)){
       //estoy en condiciones de agregar un nodo.
       //para agregar un nodop tengo que preguntar en que posicion esta.
        if(lista->pFirstNode == NULL && nodeIndex == 0){
            //agregar el primer nodo.
            lista->pFirstNode = newNode;
            newNode->pElement = pElement;
            lista->size = ll_len(lista) + 1;
            returnAux = 0;
        }
        else{
            if(lista->pFirstNode != NULL && nodeIndex == 0){
                //agrego un nodo al principio de la lista
                Node* oldFirstNode = lista->pFirstNode;
                lista->pFirstNode = newNode;
                lista->pFirstNode->pNextNode = oldFirstNode;
                newNode->pElement = pElement;
                lista->size = ll_len(lista) + 1;
                returnAux = 0;
            }
            else{
               if(lista->pFirstNode != NULL && nodeIndex > 0 && nodeIndex < ll_len(lista)){
                    //agrego entre dos nodos
                    Node* oldNodeInIndex = getNode(lista,nodeIndex);//traigo al ocupa de nodeIndex
                    newNode->pNextNode = oldNodeInIndex;   //el nuevo nodo tiene como siguiente al ocupa
                    Node* previousNode = getNode(lista,nodeIndex - 1);  //traigo el nodo anterior a nodeIndex
                    previousNode->pNextNode = newNode;   //el nodo anterior a nodeIndex  tiene como siguiente al nuevo
                    newNode->pElement = pElement;
                    lista->size = ll_len(lista) + 1;
                    returnAux = 0;
                }
                else{
                    if(lista->pFirstNode != NULL && nodeIndex == ll_len(lista)){
                        //agrego al final
                        Node* lastNode = getNode(lista,nodeIndex - 1);//traigo al ultimo nodo
                        lastNode->pNextNode = newNode;   //el ultimo nodo tiene como siguiente al nuevo
                        newNode->pElement = pElement;
                        lista->size = ll_len(lista) + 1;
                        returnAux = 0;
                    }
                }
            }
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param lista LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int test_addNode(LinkedList* lista, int nodeIndex,void* pElement){
    return addNode(lista,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 */
int ll_add(LinkedList* lista, void* pElement){
    int returnAux = -1;
    int tam = ll_len(lista);
    if(lista!= NULL){
        addNode(lista, tam, pElement);
        returnAux = 0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param lista LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al tam de la lista)
                            (pElement) Si funciono correctamente
 */
void* ll_get(LinkedList* lista, int index){
    void* returnAux = NULL;
    Node* nodoAux;
    int tam = ll_len(lista);
    if(lista != NULL && index >= 0 && index < tam && tam > 0){
        nodoAux = getNode(lista,index);
        returnAux = nodoAux->pElement;
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 * \param lista LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al tam de la lista)
                        ( 0) Si funciono correctamente
 */
int ll_set(LinkedList* lista, int index,void* pElement){
    int returnAux = -1;
    Node* nodoAux;
    int tam = ll_len(lista);
    if(lista != NULL && index >= 0 && index < tam && tam > 0){
        nodoAux = getNode(lista,index);
        nodoAux->pElement = pElement;
        returnAux = 0;
    }
    return returnAux;
}

/** \brief Elimina un elemento de la lista
 * \param lista LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al tam de la lista)
                        ( 0) Si funciono correctamente
 */
int ll_remove(LinkedList* lista,int index){
    int returnAux = -1;
    Node* nodoAux = getNode(lista,index);
    if(lista != NULL && index >= 0 && index < ll_len(lista)){
        if(index == 0){
            //borro el primer nodo.
            lista->pFirstNode = nodoAux->pNextNode;
            free(nodoAux);
            lista->size = ll_len(lista) - 1;
            returnAux = 0;
        }
        else{
            //borro entre dos nodos
            Node* previousNode = getNode(lista,index - 1);
            previousNode->pNextNode = nodoAux->pNextNode;
            free(nodoAux);
            lista->size = ll_len(lista) - 1;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 * \param lista LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 */
int ll_clear(LinkedList* lista){
    int returnAux = -1;
    int contador;
    int tam = ll_len(lista);
    if(lista != NULL){
        for(contador = 0;contador < tam;contador++){
            ll_remove(lista,contador);
        }
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 * \param lista LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 */
int ll_deleteLinkedList(LinkedList* lista){
    int returnAux = -1;
    if(lista != NULL){
        ll_clear(lista);
        free(lista);
        returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 * \param lista LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 */
int ll_indexOf(LinkedList* lista, void* pElement){
    int returnAux = -1;
    Node* nodoAux;
    int contaodr;
    int tam = ll_len(lista);
    if(lista!=NULL){
        for(contaodr = 0;contaodr < tam; contaodr++){
            nodoAux = getNode(lista,contaodr);
            if(nodoAux ->pElement == pElement){
                returnAux = contaodr;
            }
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 * \param lista LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 */
int ll_isEmpty(LinkedList* lista){
    int returnAux = -1;
    if(lista != NULL && lista->size == 0){
        returnAux = 1;
    }
    else{
        if(lista != NULL && lista->size > 0){
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 * \param lista LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int ll_push(LinkedList* lista, int index, void* pElement){
    int returnAux = -1;
    if(lista!=NULL && index >= 0 && index <= ll_len(lista)){
        addNode(lista, index, pElement);
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 * \param lista LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 */
void* ll_pop(LinkedList* lista,int index){
    void* returnAux = NULL;
    void* auxElement;
    if(lista!=NULL && index >= 0 && index < ll_len(lista)){
        auxElement = ll_get(lista,index);
        ll_remove(lista, index);
        returnAux = auxElement;
    }
    return returnAux;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 * \param lista LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* lista, void* pElement){
    int returnAux = -1;
    if(lista != NULL){
        returnAux = 0;
        if(ll_indexOf(lista,pElement)!= -1){
            returnAux = 1;
        }
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (lista2)
            estan contenidos en la lista (lista)
 * \param lista LinkedList* Puntero a la lista
 * \param lista2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (lista2) estan contenidos en la lista (lista)
                        ( 0) si los elementos de (lista2) NO estan contenidos en la lista (lista)
*/
int ll_containsAll(LinkedList* lista, LinkedList* lista2){
    int returnAux = -1;
    int contador;
    void* pElement;
    if(lista != NULL && lista2 != NULL){
      returnAux = 1;
      for(contador = 0; contador < ll_len(lista2); contador++){
         pElement = ll_get(lista2,contador);
         if(!ll_contains(lista,pElement)){
             returnAux = 0;
         }
      }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* lista,int from,int to){
    LinkedList* cloneArray = NULL;
    void *pElement;
    int contador;
    if(lista != NULL && from >= 0 && to <= lista->size){
        cloneArray = ll_newLinkedList();
        for(contador=from;contador < to;contador++){
            pElement = ll_get(lista,contador);
            ll_add(cloneArray,pElement);
        }
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* lista){
    return ll_subList(lista,0,ll_len(lista));
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* lista, int (*pFunc)(void* ,void*), int order){
    int returnAux = -1;
    int contador;
    int flagSwap;
    Node* auxNode;
    if(lista != NULL && ll_len(lista)> 0 && pFunc != NULL && (order == 1 || order == 0)){
        do{
            contador = 0;
            auxNode = getNode(lista,contador);//hago un nodo auxiliar con el indice de contador(0).
            flagSwap = 0;//lo inicializo
            for(contador=0;contador<ll_len(lista)-1;contador++){
                if(contador!= 0){
                    auxNode = auxNode->pNextNode;
                }
                if((order == 0 && auxNode->pElement != NULL && auxNode->pNextNode->pElement != NULL && (*pFunc)(auxNode->pElement,auxNode->pNextNode->pElement)== -1)|| //pregunta si el orden es decendente y el primer elemento y el segundo son distintos de Null y, (si la funcion criterio devuelve -1 significa que el primer elemento es mas chico que el segundo)
                   (order == 1 && auxNode->pElement != NULL && auxNode->pNextNode->pElement != NULL && (*pFunc)(auxNode->pElement,auxNode->pNextNode->pElement)== 1))   //pregunta si el orden es acendente y el primer elemento y el segundo son distintos de Null y, (si la funcion criterio devuelve 1 significa que el primer elemento es mas grande que el segundo)
                   {
                   flagSwap = 1;//es para saber si se itero en esa vuelta
                   ll_swapElement(lista, auxNode);//hace el swap
                }

            }
        }while(flagSwap == 1);
        returnAux = 0;
    }
    return returnAux;
}

/** \brief Intercambia los elementos de dos nodos consecutivos
 * \param pList LinkedList* Puntero a la lista
 * \param pAnterior Es el primer nodo que se va a intercambiar, el segundo lo obtenemos de su pNextNode
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o alguno de los nodos es NULLL
                                ( 0) Si ok
 */
int ll_swapElement(LinkedList* lista, Node* pAnterior){
    int returnAux = -1;
    Node* pSiguiente = pAnterior->pNextNode;
    void* auxElement = NULL;
    if(lista != NULL && pAnterior != NULL && pSiguiente != NULL){
        auxElement = pAnterior->pElement;
        pAnterior->pElement = pSiguiente->pElement;
        pSiguiente->pElement = auxElement;
        returnAux = 0;
    }
    return returnAux;
}

/** \brief Filtra los elementos de una LinkedList y guarda en una nueva los que cumplen con el criterio indicado
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio que devuelve un 1 si se debe guardar en la nueva lista
 *                                                                     0 si no cumple con el criterio
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o el puntero a la funcion es NULL
                                ( 0) Si ok
 */
LinkedList* ll_filter(LinkedList* lista, int (*pFunc)(void* pElement)){
    void* auxElement = NULL;
    LinkedList* returnAux = NULL;
    int contador;
    if(lista != NULL && ll_len(lista) > 0 && pFunc != NULL){
        returnAux = ll_newLinkedList();
        ll_startIterator(lista);
        for(contador=0; contador<ll_len(lista); contador++){
            auxElement = ll_getNext(lista);
            if((*pFunc)(auxElement) == 1){
                ll_add(returnAux, auxElement);
            }
        }
    }
    return returnAux;
}

/** \brief
 * \param
 * \param
 * \return
 */
int ll_map(LinkedList* lista, int (*pFunc)(void*)){
    int returnAux = -1;
    int contador;
    void* auxElement = NULL;
    if(lista != NULL && ll_len(lista) > 0 && pFunc != NULL){
        ll_startIterator(lista);
        for(contador=0; contador<ll_len(lista); contador++){
            auxElement = ll_getNext(lista);
            if((*pFunc)(auxElement) == 0){
                returnAux = 0;
            }
            else{
                break;
            }
        }
    }
    return returnAux;
}
