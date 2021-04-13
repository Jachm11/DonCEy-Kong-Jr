#pragma once
#include "node.cpp"

///
/// \brief Clase Lista enlazada implementada en C++
/// @author Jose y Natalia
///
template<class T>
class LinkedList
{

private:

    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    LinkedList();       
//    __________________
//__/Getters n' Setters
    /**
    * \brief devuelve la cabeza EL NODO
    * @return cabeza
    */
    Node<T>* getHead();

    /**
    * \brief cambia el nodo cabeza de la lista(debe ingresar un nodo)
    * @param head es la cabeza
    */
    void setHead(Node<T> head);

    /**
    * \brief retorna la cola de la lista ES UN NODO
    * @return tail
    */
    Node<T>* getTail();

    /**
    * \brief cambia el nodo de la cola (DEBE SER UN NODO)
    * @param tail la colita de la lista
    */
    void setTail(Node<T> tail);

    /**
    * \brief funcion que retorna la amplitud de la lista
    * @return size
    */
    int getSize();

//   _____________________
//__/Funciones de la lista

    ///
    /// \brief isEmpty Funcion que responde a: "is it empty?"
    /// \return True si esta vacia, false de lo contrario
    ///
    bool isEmpty();

    /**
    * \brief Metodo que se encarga de insertar un nodo con un dato al inicio de la lista enlazada.
    * @param data Dato tipo Object que se desea que el nuevo nodo contenga.
    */
    void insertFirst(T data);

    /**
    * \brief Funcion qe crea un nodo a partir de los datos que se ingresen y lo pone al inicio de la lista
    * @param data Dato tipo Object que se desea que el nuevo nodo contenga.
    */
    void insertLast(T data);

    /**
    * \brief Metodo que se encarga de eliminar el nodo al inicio de la lista enlazada.
    */
    void deleteFirst();

    /**
    * \brief Metodo que se encarga de eliminar el nodo al final de la lista enlazada.
    */
    void deleteLast();

    /**
    * \brief Metodo para eliminar un elemento de una lista segun el indice que se le digite
    * @param index
    */
    void deleteByIndex(int index);

    /**
    * \brief Funcion que permite buscar un nodo de la lista por el indice en el que se encuentra
    * @param index Indice de la lista que se quiere buscar
    * @return El nodo que se encuetra en ese indice. Null si la lista esta vacia.
    */
    Node<T>* searchByIndex(int index);

    /**
    * Metodo que se encarga de eliminar el nodo con un dato especifico en la primer posicion en que lo encuentre en lista enlazada.
    *
    * @param data Dato tipo Object que se desea eliminar en una posicion desconocida.
    */
    void deleteByData(T data);

    /**
    * Metodo para imprimir en consola una lista
    *
    */
    void printList();

    ///
    /// \brief mergeLinkedList Une dos listas enlazadas
    /// \param toMerge es la lista que tomara posicion justo despues del ultimo elemento de la lista donde se aplica el metodo
    ///
    void mergeLinkedList(LinkedList<T> toMerge);

    ///
    /// \brief deleteReapeatedData Elimina todos los datos iguales/repetidos de la lista enlazada, conserva la primer repeticion
    ///
    void deleteReapeatedData();

    /**
    * \brief Funcion para vaciar una lista
    */
    void clearList();

};
