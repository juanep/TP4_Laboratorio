#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


/** \brief Coloca el iterador en el primer nodo
 *
 *  \param this LinkedList* Puntero a la lista
 */
void ll_startIterator(LinkedList* this)
{
    if(this != NULL)
    {
        this->actualNode = this->pFirstNode;
    }
}

/** \brief  Toma el siguiente elemento de la lista utilizando el nodo declarado estaticamente
 *          Y coloca el nodo en el siguiente indice de la lista
 *  \param void
 *  \return void*   Retorna (NULL) en el caso de no conseguir un nuevo elemento o si el siguiente elemento es NULL
 *                  Y retorna el puntero al elemento si existe.
 */
void* ll_getNext(LinkedList* this)
{
    void* returnAux = NULL;
    if(this->actualNode != NULL)
    {
        returnAux = this->actualNode->pElement;
        this->actualNode = this->actualNode->pNextNode;
    }
    return returnAux;
}

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;

}


/** \brief  Obtiene un nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int i;
    if(this != NULL && ll_len(this) > 0 && nodeIndex < ll_len(this) && nodeIndex >= 0)
    {
        pNode = this->pFirstNode;//caso particular
        for(i=0;i< nodeIndex;i++)//reccore hasta uno antes del proximo
        {
            pNode = pNode -> pNextNode;//nodo tiene la direccion del proximo nodo
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement) //size de la lista es la cantidad de nodos //index nodo es donde esta el nodo en la lista.
{
    int returnAux = -1;
    Node* newNode = malloc(sizeof(Node));

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
       //estoy en condiciones de agregar un nodo.
       //para agregar un nodop tengo que preguntar en que posicion esta.
        if(this->pFirstNode == NULL && nodeIndex == 0)//D
        {
            //agregar el primer nodo.
            this->pFirstNode = newNode;
            newNode->pElement = pElement;
            this->size = ll_len(this) + 1;
            returnAux = 0;
        }
        else if(this->pFirstNode != NULL && nodeIndex == 0)//A
        {
            //agrego un nodo al principio de la lista
            Node* oldFirstNode = this->pFirstNode;
            this->pFirstNode = newNode;
            this->pFirstNode->pNextNode = oldFirstNode;
            newNode->pElement = pElement;
            this->size = ll_len(this) + 1;
            returnAux = 0;
        }
        else if(this->pFirstNode != NULL && nodeIndex > 0 && nodeIndex < ll_len(this))//B
        {
            //agrego entre dos nodos
            Node* oldNodeInIndex = getNode(this,nodeIndex);//traigo al ocupa de nodeIndex
            newNode->pNextNode = oldNodeInIndex;   //el nuevo nodo tiene como siguiente al ocupa
            Node* previousNode = getNode(this,nodeIndex - 1);  //traigo el nodo anterior a nodeIndex
            previousNode->pNextNode = newNode;   //el nodo anterior a nodeIndex  tiene como siguiente al nuevo
            newNode->pElement = pElement;
            this->size = ll_len(this) + 1;
            returnAux = 0;
        }
        else if(this->pFirstNode != NULL && nodeIndex == ll_len(this))//C
        {
             //agrego al final
            Node* lastNode = getNode(this,nodeIndex - 1);//traigo al ultimo nodo
            lastNode->pNextNode = newNode;   //el ultimo nodo tiene como siguiente al nuevo

            newNode->pElement = pElement;
            this->size = ll_len(this) + 1;
            returnAux = 0;
        }


    }
    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this!= NULL)
    {
        addNode(this,len,pElement);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* nodoAux;
    int len = ll_len(this);


    if(this != NULL && index >= 0 && index < len && len > 0)
    {
        nodoAux = getNode(this,index);
        returnAux = nodoAux->pElement;
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* nodoAux;
    int len = ll_len(this);

    if(this != NULL && index >= 0 && index < len && len > 0)
    {
        nodoAux = getNode(this,index);
        nodoAux->pElement = pElement;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* nodoAux = getNode(this,index);

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
       //estoy en condiciones de borrar un elemento
       //para borrar un nodo tengo que preguntar en que posicion esta.
        if(index == 0)//D
        {
            //borro el primer nodo.
            this->pFirstNode = nodoAux->pNextNode;
            free(nodoAux);
            this->size = ll_len(this) - 1;
            returnAux = 0;
        }

        else if(index > 0)//B
        {
            //borro entre dos nodos
            Node* previousNode = getNode(this,index - 1);
            previousNode->pNextNode = nodoAux->pNextNode;
            free(nodoAux);
            this->size = ll_len(this) - 1;
            returnAux = 0;
        }

    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
    int len = ll_len(this);

    if(this != NULL)
    {
        for(i = 0;i < len;i++)
        {
            ll_remove(this,i);
        }
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        ll_clear(this);
        free(this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* nodoAux;
    int i;
    int len = ll_len(this);

    if(this!=NULL)
    {
        for(i = 0;i < len; i++)
        {
            nodoAux = getNode(this,i);
            if(nodoAux ->pElement == pElement)
            {
                returnAux = i;
            }
        }

    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL && this->size == 0)
    {
        returnAux = 1;
    }
    else if(this != NULL && this->size > 0)
    {
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL && index >= 0 && index <= ll_len(this))
    {
        addNode(this,index,pElement);
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* auxElement;

    if(this!=NULL && index >= 0 && index < ll_len(this))
    {
        auxElement = ll_get(this,index);
        ll_remove(this,index);
        returnAux = auxElement;
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = 0;
        if(ll_indexOf(this,pElement)!= -1)
        {
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    void* pElement;

    if(this != NULL && this2 != NULL)
    {
      returnAux = 1;
      for(i = 0; i < ll_len(this2); i++)
      {
         pElement = ll_get(this2,i);
         if(!ll_contains(this,pElement))
         {
             returnAux = 0;
         }
      }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void *pElement;
    int i;

    if(this != NULL && from >= 0 && to <= this->size)
    {
        cloneArray = ll_newLinkedList();
        for(i=from;i < to;i++)
        {
            pElement = ll_get(this,i);
            ll_add(cloneArray,pElement);
        }

    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    return ll_subList(this,0,ll_len(this));
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;
    int i;
    int flagSwap;
    Node* auxNode;

    if(this != NULL && ll_len(this)> 0 && pFunc != NULL && (order == 1 || order == 0))
    {
        do
        {
            i = 0;
            auxNode = getNode(this,i);//hago un nodo auxiliar con el indice de i(0).
            flagSwap = 0;//lo inisializo
            for(i=0;i<ll_len(this)-1;i++)//recorro toda la lista
            {
                if(i!= 0)
                {
                    auxNode = auxNode->pNextNode;
                }
                if((order == 0 && auxNode->pElement != NULL && auxNode->pNextNode->pElement != NULL && (*pFunc)(auxNode->pElement,auxNode->pNextNode->pElement)== -1)|| //pregunta si el orden es decendente y el primer elemento y el segundo son distintos de Null y, (si la funcion criterio devuelve -1 significa que el primer elemento es mas chico que el segundo)
                   (order == 1 && auxNode->pElement != NULL && auxNode->pNextNode->pElement != NULL && (*pFunc)(auxNode->pElement,auxNode->pNextNode->pElement)== 1))   //pregunta si el orden es acendente y el primer elemento y el segundo son distintos de Null y, (si la funcion criterio devuelve 1 significa que el primer elemento es mas grande que el segundo)
                {
                   flagSwap = 1;//es para saber si se itero en esa vuelta
                   ll_swapElement(this,auxNode);//hace el swap
                }

            }
        }
        while(flagSwap == 1);
        returnAux = 0;
    }
    return returnAux;
}

/** \brief Intercambia los elementos de dos nodos consecutivos
 * \param pList LinkedList* Puntero a la lista
 * \param pNodeAnterior Es el primer nodo que se va a intercambiar, el segundo lo obtenemos de su pNextNode
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o alguno de los nodos es NULLL
                                ( 0) Si ok
 */

int ll_swapElement(LinkedList* this, Node* pNodeAnterior)
{
    int returnAux = -1;
    Node* pNodeSiguiente = pNodeAnterior->pNextNode;
    void* auxElement = NULL;
    if(this != NULL && pNodeAnterior != NULL && pNodeSiguiente != NULL)
    {
        auxElement = pNodeAnterior->pElement;
        pNodeAnterior->pElement = pNodeSiguiente->pElement;
        pNodeSiguiente->pElement = auxElement;
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
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void* pElement))
{
    void* auxElement = NULL;
    LinkedList* returnAux = NULL;
    int i;
    if(this != NULL && ll_len(this) > 0 && pFunc != NULL)
    {
        returnAux = ll_newLinkedList();
        ll_startIterator(this);
        for(i=0; i<ll_len(this); i++)
        {
            auxElement = ll_getNext(this);
            if((*pFunc)(auxElement) == 1)
            {
                ll_add(returnAux, auxElement);
            }
        }
    }
    return returnAux;
}

int ll_map(LinkedList* this, int (*pFunc)(void*))
{
    int returnAux = -1;
    int i;
    void* auxElement = NULL;

    if(this != NULL && ll_len(this) > 0 && pFunc != NULL)
    {
        ll_startIterator(this);
        for(i=0; i<ll_len(this); i++)
        {
            auxElement = ll_getNext(this);
            if((*pFunc)(auxElement) == 0)
            {
                returnAux = 0;
            }
            else
            {
                break;
            }
        }
    }


    return returnAux;
}
