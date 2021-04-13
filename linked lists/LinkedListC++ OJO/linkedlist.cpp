#include "linkedlist.h"

template<class T>
LinkedList<T> :: LinkedList()
{
    head = NULL;
    tail = NULL;
    size = 0;
}
//       __________________
//_____/Getters n' Setters

template<class T>
Node<T>* LinkedList<T> :: getHead() {
    return head;
}

template<class T>
void LinkedList<T> :: setHead(Node<T> head) {
    this->head = &head;
}
   
template<class T>     
Node<T>* LinkedList<T> :: getTail() {
    return tail;
}

template<class T>
void LinkedList<T> :: setTail(Node<T> tail) {
    this->tail = &tail;
}
  
template<class T>     
int LinkedList<T> :: getSize() {
    return size;
} 

//   _____________________
//__/Funciones de la lista

template<class T>
bool LinkedList<T> :: isEmpty(){
    if (size == 0){
        return true;
    }else{
        return false;
    }
}

template<class T>
void LinkedList<T> :: insertFirst(T data){
    Node<T> *newNode = new Node<T>(data);
    newNode->setNext(head);
    if (head==NULL){
        tail = newNode;
    }
    head = newNode;
    size++;
}

template<class T>
void LinkedList<T> :: insertLast(T data){
    Node<T> *newNode = new Node<T>(data);
    if (head==NULL){
        Node<T> *newNode = new Node<T>(data);
        head = newNode;
        tail = newNode;
    }else{
        Node<T> *current = head;

        while (current->getNext()!= NULL){
            current = current->getNext();
        }
        current->setNext(newNode);
        tail = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T> :: deleteFirst(){
    if (head != NULL){
        head = head->getNext();
        size--;
    }
}

template<class T>
void LinkedList<T> :: deleteLast(){
    if (tail != NULL){
        Node<T> *current = head;
        int counter = 1;

        while(counter<size-1){
            current = current->getNext();
            counter++;
        }
        current->setNext(NULL);
        tail = current;
        size--;
    }
}

template<class T>
void LinkedList<T> :: deleteByIndex(int index){
    if (0<=index and index<size){
        if (index==0){
            head = head->getNext();
        }else{
            int counter = 0;
            Node<T> *current = head;

            while(counter<index-1){
                current = current->getNext();
                counter++;
            }
            current->setNext(current->getNext()->getNext());
        }
        size--;
    }
}

template<class T>
Node<T>* LinkedList<T> :: searchByIndex(int index) {
    if (0<=index and index<size){
        if (head != NULL) {
            Node<T> *current = head;

            for (int x = 0; x < index; x++) {
                current = current->getNext();
            }
            return current;
        }
    }
    return NULL;
}

template<class T>
void LinkedList<T> :: deleteByData(T data){
    //Primero valida para por si es una lista de 2 nodos
    if (head != NULL){
        if (size>1){
            if (head->getData() == data) {
                deleteFirst();
            }else{
                if (head->getNext()->getNext() != NULL){
                    Node<T> *current = head;

                    while (current->getNext()->getNext() != NULL) {
                        if (current->getNext()->getData() == data) {
                            current->setNext(current->getNext()->getNext());
                            size--;
                            break;
                        }
                        current = current->getNext();
                    }
                    if (current->getNext()->getData() == data) {
                        current->setNext(current->getNext()->getNext());
                        size--;
                    }
                }else{
                    if (head->getNext()->getData() == data){
                        head->setNext(NULL);
                        size = 1;
                    }
                }
            }
        }else{
            if (head->getData() == data){
                clearList();
            }
        }
    }
}

template<class T>
void LinkedList<T> :: printList() {
    if (head==NULL){
        std::cout <<"null list";
    }else{
        Node<T> *current = head;
        std::cout <<"LinkedList: ";

        while (current != NULL) {
            std::cout<< current->getData()<<" ";
            current = current->getNext();
        }
        std::cout<<"\n";
    }
}

template<class T>
void LinkedList<T> :: mergeLinkedList(LinkedList<T> toMerge) {
    if (head == NULL){
        head = toMerge.head;
    }else{
        tail->setNext(toMerge.getHead());
        tail = toMerge.getTail();
    }
    size += toMerge.size;
}

template<class T>
void LinkedList<T> :: deleteReapeatedData() {
    if (head != NULL){
        Node<T> *current = head;

        for(int i=0;i<size;i++){
            T currentData = current->getData();

            for(int j=i+1;j<size;j++){
                if(currentData == searchByIndex(j)->getData()){
                        deleteByIndex(j);
                }
            }
            current = searchByIndex(i);
        }
    }
}

template<class T>
void LinkedList<T> :: clearList(){
    head = NULL;
    size = 0;
}
