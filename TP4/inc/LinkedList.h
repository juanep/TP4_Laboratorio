/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __LINKEDLIST
#define __LINKEDLIST
struct Node
{
    void* pElement;
    struct Node* pNextNode;
}typedef Node;

struct LinkedList
{
    Node* actualNode;
    Node* pFirstNode;
    int size;
}typedef LinkedList;
#endif



//Publicas
LinkedList* ll_newLinkedList(void);
int ll_len(LinkedList* lista);
Node* test_getNode(LinkedList* lista, int nodeIndex);
int test_addNode(LinkedList* lista, int nodeIndex,void* pElement);
int ll_add(LinkedList* lista, void* pElement);
void* ll_get(LinkedList* lista, int index);
int ll_set(LinkedList* lista, int index,void* pElement);
int ll_remove(LinkedList* lista,int index);
int ll_clear(LinkedList* lista);
int ll_deleteLinkedList(LinkedList* lista);
int ll_indexOf(LinkedList* lista, void* pElement);
int ll_isEmpty(LinkedList* lista);
int ll_push(LinkedList* lista, int index, void* pElement);
void* ll_pop(LinkedList* lista,int index);
int ll_contains(LinkedList* lista, void* pElement);
int ll_containsAll(LinkedList* lista,LinkedList* this2);
LinkedList* ll_subList(LinkedList* lista,int from,int to);
LinkedList* ll_clone(LinkedList* lista);
int ll_sort(LinkedList* lista, int (*pFunc)(void* ,void*), int order);
int ll_swapElement(LinkedList* lista, Node* pNodeAnterior);
LinkedList* ll_filter(LinkedList* lista,int(*pFunc)(void* pElement));
void ll_startIterator(LinkedList* lista);
int ll_map(LinkedList* lista, int (*pFunc)(void*));
