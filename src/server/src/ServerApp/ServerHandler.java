package ServerApp;

import java.net.*;
import java.io.*;
import Game.*;

/**
* Clase para controlar a los clientes del servidor según el puerto
*/
public class ServerHandler extends Thread {
    
    public Juego miJuego;
    public Boolean player;
    public Integer count;
    public Integer port;
    
     /**
    * Constructor de ServerHandler
    * @param port puerto del cliente
    * @param niJuego juego del cliente
    */
    public ServerHandler(Integer port, Juego miJuego) {
        this.port = port;
        this.miJuego = miJuego;
        this.player = false;
        count = 1;
    }
    /**
    * Inicialización del socket
    */
    public void run(){

        try (ServerSocket serverSocket = new ServerSocket(port)) {
 
            System.out.println("Server is listening on port " + port);
 
            while (count <= 3) {
                Socket socket = serverSocket.accept();
                System.out.println("New client connected to port "+port);
                count = count + 1 ;
                System.out.println(count);
                ServerThread thread = new ServerThread(socket,this);
                thread.start();

            }
 
        } catch (IOException ex) {
            this.run();
        }
    }

}
