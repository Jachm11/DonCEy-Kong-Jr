package ServerApp;

import java.net.*;
import java.io.*;

public class ServerHandler extends Thread {
    
    public Juego miJuego;
    public Boolean player;
    public Integer count;

    private Integer port;
    

    public ServerHandler(Integer port, Juego miJuego) {
        this.port = port;
        this.miJuego = miJuego;
        this.player = false;
        count = 1;
    }

    public void run(){

        try (ServerSocket serverSocket = new ServerSocket(port)) {
 
            System.out.println("Server is listening on port " + port);
 
            while (count <= 3) {
                Socket socket = serverSocket.accept();
                System.out.println("New client connected to port "+port);
                count = count + 1 ;
                ServerThread thread = new ServerThread(socket,this);
                thread.start();

            }
 
        } catch (IOException ex) {
            this.run();
        }
    }

}
