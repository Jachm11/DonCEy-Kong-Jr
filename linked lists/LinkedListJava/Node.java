package linkedList;

/**
 * Clase Nodo ligada a la clase LinkedList que guarda una referencia al nodo siguiente y el dato que guarda
 * @author Jose and Natalia
 */
public class Node<T> {
    private T data;
    private Node<T> next;

    /**
     * Constructor de la clase.
     */
    public Node(T data) {
        this.next = null;
        this.data = data;
    }

    //         ____________________
    //________/Getters and Setters
    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public Node<T> getNext() {
        return this.next;
    }

    public void setNext(Node<T> next) {
        this.next = next;
    }
    
}
