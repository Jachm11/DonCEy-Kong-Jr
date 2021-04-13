package linkedList;
/**
 * Clase que contiene lo necesario para la implementacion de una lista enlazada.
 * @author Jose and Natalia
 * @param <T> Tipo de dato
 */
public class LinkedList<T> {
    private Node<T> head;
    private Node<T> tail;
    private int size;

    public LinkedList(){
        this.head = null;
        this.tail = null;
        this.size = 0;
    }
    //         __________________
    //________/Getters n' Setters
    
    /**
     * devuelve la cabeza EL NODO
     * @return cabeza
     */
    public Node<T> getHead() {
        return head;
    }
    /**
     * cambia el nodo cabeza de la lista(debe ingresar un nodo)
     * @param head es la cabeza
     */
    public void setHead(Node<T> head) {
        this.head = head;
    }
    /**
     * retorna la colita de la lista ES UN NODO
     * @return tail
     */
    public Node<T> getColita() {
        return tail;
    }
    /**
     * cambia el nodo de la colita (DEBE SER UN NODO)
     * @param tail la colita de la lista
     */
    public void setColita(Node<T> tail) {
        this.tail = tail;
    }
    /**
     * funcion que retorna la amplitud de la lista
     * @return size
     */
    public int getSize() {
        return size;
    }
    
    /**
     * Metodo que se encarga de insertar un nodo con un dato al inicio de la lista enlazada.
     *
     * @param data Dato tipo Object que se desea que el nuevo nodo contenga.
     */

    public void insertFirst(T data){
        Node newNode = new Node<>(data);
        newNode.setNext(this.head);
        this.head = newNode;
        if (size == 0){
            this.tail = newNode;
        }
        this.size++;
    }
    
    public boolean isEmpty(){
        if (size == 0){
            return true;
        }else{
            return false;
        }
    }

    /**
     * Funci�n qe crea un nodo a partir de los datos que se ingresen y lo pone al inicio de la lista
     * @param data Dato tipo Object que se desea que el nuevo nodo contenga.
     */

    public void insertLast(T data){
        if (head==null){
            head = new Node<T>(data);
            tail = new Node<T>(data);
        }
        else{
            Node current = head;
            Node newNode = new Node<T>(data);
            while (current.getNext()!= null){
                current= current.getNext();
            }
            current.setNext(newNode);
            this.tail = newNode;
        }
        this.size++;

    }

    /**
     * Metodo que se encarga de eliminar el nodo al inicio de la lista enlazada.
     */
    public void deleteFirst(){
        if (this.head != null){
            this.head = this.head.getNext();
            this.size--;
        }
    }
    /**
     * M�todo para eliminar un elemento de una lista seg�n el �dice que se le digite
     * @param index 
     */
        public void deleteByIndex(int index){
        if (index==0){
            head = head.getNext();
        }
        else{
            int counter = 0;
            Node current = head;
             while(counter<index-1){
                 current = current.getNext();
                 counter++;
             }
             current.setNext(current.getNext().getNext());
        }
        size--;
    }
    /**
     * Funci�n que permite buscar un nodo de la lista por el �dice en el que se encuentra
     * @param index Indice de la lista que se quiere buscar
     * @return El nodo que se encuetra en ese �ndice. Null si la lista est� vac�a.
     */
    public Node<T> searchByIndex(int index) {
        if (head != null) {
            Node current = this.head;
            for (int x = 0; x < index; x++) {
                current = current.getNext();
            }
            return current;
        }
        return null;
    }

    /**
     * Metodo que se encarga de cambiar el dato del nodo en una posicion X de la lista enlazada.
     *
     * @param index Indice de la lista donde se quiere insetar el dato. (Empezando en 0).
     * @param data Dato tipo Object que se desea que el nuevo nodo contenga.
     */
    public void setDataByIndex(int index,T data){
        Node current = this.head;
        for (int x = 0; x < index ; x++ ){
            current = current.getNext();
        }
        current.setData(data);

    }
    
    

    /**
     * Metodo que se encarga de eliminar el nodo con un dato especifico en la primer posicion en que lo encuentre en lista enlazada.
     *
     * @param data Dato tipo Object que se desea eliminar en una posicion desconocida.
     */
    public void deleteByData(T data){
        //Primero valida para por si es una lista de 2 nodos
        if (head != null){
            if (size>1) {
                if (head.getData() == data) {
                    deleteFirst();
                } else {
                    if (head.getNext().getNext() != null){
                        Node current = this.head;
                        while (current.getNext().getNext() != null) {
                            if (current.getNext().getData() == data) {
                                current.setNext(current.getNext().getNext());
                                size--;
                                break;
                            }
                            current = current.getNext();
                        }
                        if (current.getNext().getData() == data) {
                            current.setNext(current.getNext().getNext());
                            size--;
                        }
                    }else{
                        if (head.getNext().getData() == data){
                            head.setNext(null);
                            size = 1;
                        }
                    }
                }
            }else{
                if (head.getData() == data){
                    head = null;
                    size = 0;
                }
            }
        }
    }
    /**
     * M�todo para imprimir en consola una lista
     * 
     */
    public void printList() { 
        if (head==null){
            System.out.println("null");
        }
        Node current = head; 
        
        System.out.print("LinkedList: "); 
        while (current != null) { 
            System.out.print(current.getData() + " "); 
   
            current = current.getNext(); 
        } 
    }
    /**
     * Funci�n para vaciar una lista
     */
    public void clearList(){
        this.head = null;
        this.size = 0;
    }   

    public void mergeLinkedList(LinkedList<T> toMerge) {
            if (this.head == null){
                this.head = toMerge.head;
            }else{
            Node<T> current = this.head;
            while (current.getNext() != null){
                current = current.getNext();
            }
            System.out.println(this.size);
            current.setNext(toMerge.head);
            }
            this.size += toMerge.size;
            System.out.println(toMerge.size);
            System.out.println(this.size);
        }

    public void deleteReapeatedData() {
        if (this.head != null){
            Node<T> current = this.head;
            for(int i=0;i<this.size;i++){
                T currentData = current.getData();
                for(int j=i+1;j<this.size;j++){
                    if(currentData == this.searchByIndex(j).getData())
                        this.deleteByIndex(j);
                    System.out.println("repetition deleted");
                    
                }
                current= this.searchByIndex(i);
            }
        }
    }
    
}
