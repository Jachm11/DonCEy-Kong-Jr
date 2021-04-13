#include "node.h"
#include <iostream>

template<class T>
Node<T> :: Node(T Data){
    data = Data;
    next = NULL;
}

template<class T>
T* Node<T> :: getData(){
    return &data;
}

template<class T>
void Node<T> :: setData(T Data) {
    data = Data;
}

template<class T>
Node<T>* Node<T> :: getNext() {
    return next;
}

template<class T>
void Node<T> :: setNext(Node<T> *Next) {
    next = Next;
}
