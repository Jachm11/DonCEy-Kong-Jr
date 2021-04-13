#pragma once
#include <iostream>
///
/// \brief Clase Nodo ligada a la clase LinkedList que guarda una referencia al nodo siguiente y el dato que guarda
/// @author Jose y Natalia
///
template<class T>
class Node
{
private:

    T data;
    Node<T> *next;

public:

    Node(T Data);
    T* getData();
    void setData(T Data);
    Node<T>* getNext();
    void setNext(Node<T> *Next);

};
