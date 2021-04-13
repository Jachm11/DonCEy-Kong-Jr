/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package linkedList;
/**
 * Esta clase es una cola
 * @author Brian
 * @param <T> tipo de las variables que van en la cola
 */
public class Queue<T>{
    private Node<T> colita;
    private Node<T> start;
    /**
     * constructor de la clase
     */
    public Queue(){
        this.colita = null;
        this.start = null;
    }
    
    /**
     * Esta funcion devuelve un booleano dependiendo si "Queue" esta vacia o no
     * @return booleano, true si esta vacia, false caso contrario
     */
    public boolean isEmpty(){
        if(start == null){
            return true;
        }else{
            return false;
        }
    }
    
    /**
     * Esta función agrega un elemento a la cola.
     * @param elemento a agregar
     */
    public void add(T elemento){
        Node<T> nodoGenerico = new Node<T>(elemento);
        if (start == null){
            this.start = nodoGenerico;
            this.colita = nodoGenerico;
        }else{
            this.colita.setNext(nodoGenerico);
            this.colita = nodoGenerico;
        }
    }
    
    /**
     * devuelve el primer elemento borrandolo de la cola
     * @return valor del primer dato en cola
     */
    public T poll(){
        if(this.start != null){
            T startValue = this.start.getData();
            if(this.start == this.colita){
                start = null;
                colita = null;
            }else{
                start = start.getNext();
            }
            return startValue;
        }else{
            return null;
        }
    }
    
    /**
     * esta funcion solo mira el dato en el inicio de la cola, pero no elimina
     * @return dato del primero en cola
     */
    public T peek(){
        return this.start.getData();
    }
    /**
     * funcion que remueve el primer nodo
     */
    public void remove(){
        if(start == colita){
            start = null;
            colita = null;
        }else{
            start = start.getNext();
        }
    }
     /**
      * esta funcion elimina un elemento en cualquier punto de la cola
      * @param toErase elemento a buscar para eliminarlo como 
      * terminator con John Connor
      */
    public void remove(T toErase){
        if(start==null){
            
        }else if(start == colita && start.getData()== toErase){
            start = null;
            colita = null;
        }else{
            if(start.getData() == toErase){
                start = start.getNext();
            }else{
                Node<T> head = start;
                while (head != null){
                    if (head.getNext().getData() == toErase){
                        head.setNext(head.getNext().getNext());
                        return;
                    }else{
                        head = head.getNext();
                    }
                }
            }
        }
    }
}
